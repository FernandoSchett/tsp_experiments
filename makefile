# compiler
GXX := g++

# compiler flags
GXXFLAGS :=

# target executable
TARGET := TSP

# header files
INCLUDES := -I src/include

# source files
SOURCES := src/lib/io_inst.cpp src/lib/double_sided_nn_heur.cpp src/lib/get_sys_time.cpp src/lib/saving_heurist.cpp

# object files
# src/lib/ -> build/
OBJECTS := $(patsubst src/lib/%,build/%,$(SOURCES))
# .cpp -> .o
OBJECTS := $(patsubst %.cpp,%.o,$(OBJECTS))

all: $(TARGET)

$(TARGET): src/tsp.cpp $(OBJECTS) src/include/
	$(GXX) $(GXXFLAGS) $(INCLUDES) src/tsp.cpp -o $@ $(OBJECTS)

build/io_inst.o: src/lib/io_inst.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/io_inst.cpp -o $@

build/double_sided_nn_heur.o: src/lib/double_sided_nn_heur.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/double_sided_nn_heur.cpp -o $@

build/get_sys_time.o: src/lib/get_sys_time.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/get_sys_time.cpp -o $@

build/saving_heurist.o: src/lib/saving_heurist.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/saving_heurist.cpp -o $@

clean:
	$(RM) -r build
	$(RM) $(TARGET)