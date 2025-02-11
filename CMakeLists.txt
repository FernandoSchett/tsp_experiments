cmake_minimum_required(VERSION 3.18)
project(TSPProject LANGUAGES CXX CUDA)

# ============================
# Opções de Configuração
# ============================
option(USE_MPI "Habilita MPI" ON)
option(USE_CUDA "Habilita CUDA" ON)
option(USE_OPENMP "Habilita OpenMP" ON)

if(NOT DEFINED PROCS)
  set(PROCS 1)
endif()

# ============================
# Padrões de Compilação
# ============================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(USE_CUDA)
  set(CMAKE_CUDA_STANDARD 14)
  set(CMAKE_CUDA_STANDARD_REQUIRED ON)
endif()

# ============================
# Flags individuais
# ============================
set(BASE_FLAGS_LIST -O2 -D_GLIBCXX_USE_CXX11_ABI=0)

# Diretório de includes do projeto
include_directories(src/include)

# ============================
# Configurações do OpenMP
# ============================
if(USE_OPENMP)
  find_package(OpenMP REQUIRED)
  if(OpenMP_CXX_FOUND)
    set(OMP_FLAGS ${OpenMP_CXX_FLAGS})
  endif()
  if(USE_CUDA)
    # Para CUDA, passamos as flags do OpenMP via -Xcompiler
    set(CUDA_OMP_FLAGS ${OpenMP_CXX_FLAGS})
  endif()
endif()

# ============================
# Configurações do MPI
# ============================
if(USE_MPI)
  find_package(MPI REQUIRED)
  include_directories(${MPI_CXX_INCLUDE_PATH})
  add_compile_definitions(USE_MPI)
  add_compile_definitions(N_PROCESSES=${PROCS})
endif()

# ============================
# Configurações do CUDA
# ============================
if(USE_CUDA)
  # Alterado para requerer a versão 11.5, que é a instalada no seu sistema
  find_package(CUDAToolkit 11.5 REQUIRED)
  add_compile_definitions(USE_CUDA)
  # Define o compilador host para CUDA, se necessário
  set(CMAKE_CUDA_HOST_COMPILER gcc)
  # Defina a arquitetura CUDA desejada para a sua GPU MX570 (compute capability 7.5)
  set(CMAKE_CUDA_ARCHITECTURES 75)
endif()

# Adiciona as flags base individualmente (evita a concatenação indesejada)
foreach(flag ${BASE_FLAGS_LIST})
  add_compile_options(${flag})
endforeach()

# Adiciona flags do OpenMP aos compiladores
if(USE_OPENMP)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OMP_FLAGS}")
  if(USE_CUDA)
    set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -Xcompiler \"${CUDA_OMP_FLAGS} -fpermissive\"")
  endif()
endif()

# ============================
# Inclui diretórios de MPI via mpicxx (opcional)
# ============================
if(USE_MPI)
  execute_process(COMMAND ${MPI_CXX_COMPILER} --showme:incdirs
    OUTPUT_VARIABLE MPI_INC_RAW
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  string(REGEX REPLACE " " ";" MPI_INC_LIST "${MPI_INC_RAW}")
  foreach(dir ${MPI_INC_LIST})
    include_directories("-I${dir}")
  endforeach()
endif()

# ============================
# Fontes do Projeto
# ============================
file(GLOB LIB_SOURCES "src/lib/*.cpp")
file(GLOB CUDA_SOURCES "src/lib/pso_cuda.cu")
set(SOURCES src/tsp.cpp ${LIB_SOURCES})

# ============================
# Executável "tsp" (Serial/Multithread)
# ============================
add_executable(tsp ${SOURCES})
if(USE_CUDA)
  target_sources(tsp PRIVATE ${CUDA_SOURCES})
  # Inclui os diretórios do CUDA (se necessário)
  target_include_directories(tsp PRIVATE ${CUDAToolkit_INCLUDE_DIRS})
endif()
target_include_directories(tsp PRIVATE src/include)
if(USE_MPI)
  target_link_libraries(tsp PRIVATE MPI::MPI_CXX)
endif()
if(USE_CUDA)
  target_link_libraries(tsp PRIVATE CUDA::cudart)
endif()
if(USE_OPENMP)
  target_link_libraries(tsp PRIVATE OpenMP::OpenMP_CXX)
endif()

# ============================
# Executável "tsp_mpi" (MPI + OpenMP)
# ============================
add_executable(tsp_mpi ${SOURCES})
if(USE_CUDA)
  target_sources(tsp_mpi PRIVATE ${CUDA_SOURCES})
  target_include_directories(tsp_mpi PRIVATE ${CUDAToolkit_INCLUDE_DIRS})
endif()
target_include_directories(tsp_mpi PRIVATE src/include)
if(USE_MPI)
  target_compile_definitions(tsp_mpi PRIVATE USE_MPI)
  target_link_libraries(tsp_mpi PRIVATE MPI::MPI_CXX)
endif()
if(USE_CUDA)
  target_compile_definitions(tsp_mpi PRIVATE USE_CUDA)
  target_link_libraries(tsp_mpi PRIVATE CUDA::cudart)
endif()
if(USE_OPENMP)
  target_link_libraries(tsp_mpi PRIVATE OpenMP::OpenMP_CXX)
endif()

# ============================
# Executável "tsp_cuda" (Experimentos com CUDA)
# ============================
add_executable(tsp_cuda ${SOURCES})
if(USE_CUDA)
  target_sources(tsp_cuda PRIVATE ${CUDA_SOURCES})
  target_include_directories(tsp_cuda PRIVATE ${CUDAToolkit_INCLUDE_DIRS})
endif()
target_include_directories(tsp_cuda PRIVATE src/include)
target_compile_definitions(tsp_cuda PRIVATE USE_CUDA)
if(USE_MPI)
  target_compile_definitions(tsp_cuda PRIVATE USE_MPI)
  target_link_libraries(tsp_cuda PRIVATE MPI::MPI_CXX)
endif()
if(USE_CUDA)
  target_link_libraries(tsp_cuda PRIVATE CUDA::cudart)
endif()
if(USE_OPENMP)
  target_link_libraries(tsp_cuda PRIVATE OpenMP::OpenMP_CXX)
endif()
set_target_properties(tsp_cuda PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
# Força o padrão C++14 no target tsp_cuda para compilar o código host dos arquivos CUDA
set_target_properties(tsp_cuda PROPERTIES CXX_STANDARD 17)
