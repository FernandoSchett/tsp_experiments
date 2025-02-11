# Definir compilador e flags base
GXX := g++
NVCC := nvcc

# Número de processos MPI (default = 1)
PROCS ?= 1

# Flags base para compilação
BASE_FLAGS := -O2 -std=c++17 -D_GLIBCXX_USE_CXX11_ABI=0 -I src/include
MPI_FLAGS := -fopenmp -DUSE_MPI -DN_PROCESSES=$(PROCS)
CUDA_FLAGS := -std=c++17 -Xcompiler "-fopenmp" -DUSE_CUDA

# Diretórios
BUILD_DIR := build
SRC_DIR := src/lib
INCLUDES := -I src/include

# Definição dos arquivos fonte
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
CUDA_SOURCES := $(SRC_DIR)/pso_cuda.cu
CUDA_OBJECTS := $(patsubst $(SRC_DIR)/%.cu,$(BUILD_DIR)/%.o,$(CUDA_SOURCES))

# Bibliotecas
LIBS := -lpthread
MPI_LIBS := -lmpi
CUDA_LIBS := -lcudart

# Definir regras de compilação modularizadas
.PHONY: all default mpi cuda clean

all: default

# Compilação padrão (sem CUDA e sem MPI)
default: $(BUILD_DIR)/tsp
$(BUILD_DIR)/tsp: src/tsp.cpp $(OBJECTS)
	mkdir -p $(BUILD_DIR)
	$(GXX) $(BASE_FLAGS) $(INCLUDES) src/tsp.cpp -o $@ $(OBJECTS) $(LIBS)

# Compilação para MPI + OpenMP
mpi: $(BUILD_DIR)/tsp-mpi
$(BUILD_DIR)/tsp-mpi: src/tsp.cpp $(OBJECTS)
	mkdir -p $(BUILD_DIR)
	mpicxx $(BASE_FLAGS) $(MPI_FLAGS) $(INCLUDES) src/tsp.cpp -o $@ $(OBJECTS) $(MPI_LIBS)

# Compilação com CUDA
cuda: $(BUILD_DIR)/tsp-cuda
$(BUILD_DIR)/tsp-cuda: src/tsp.cpp $(OBJECTS) $(CUDA_OBJECTS)
	mkdir -p $(BUILD_DIR)
	$(GXX) $(BASE_FLAGS) -DUSE_CUDA $(INCLUDES) src/tsp.cpp -o $@ $(OBJECTS) $(CUDA_OBJECTS) $(CUDA_LIBS)

# Regra para compilar arquivos C++ (.cpp)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(GXX) $(BASE_FLAGS) $(INCLUDES) -c $< -o $@

# Regra para compilar arquivos CUDA (.cu)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cu
	mkdir -p $(dir $@)
	$(NVCC) $(CUDA_FLAGS) $(INCLUDES) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(BUILD_DIR)/tsp $(BUILD_DIR)/tsp-mpi $(BUILD_DIR)/tsp-cuda
