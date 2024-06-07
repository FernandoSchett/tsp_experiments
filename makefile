# compiler
GXX := g++

# compiler flags
GXXFLAGS :=

# target executable
TARGET := TSP

# header files
INCLUDES := -I src/include

# source files
SOURCES := src/lib/io_inst.cpp src/lib/double_sided_nn_heur.cpp \
	src/lib/get_sys_time.cpp src/lib/nn_heur.cpp \
	src/lib/dists.cpp src/lib/tour_solution.cpp \
	src/lib/semi_greedy_schemes.cpp src/lib/choice_method.cpp \
	src/lib/parameters.cpp src/lib/multi_start.cpp \
	src/lib/local_search.cpp src/lib/grasp.cpp \
	src/lib/path_relinking.cpp src/lib/stop_criterion.cpp
 
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

build/nn_heur.o: src/lib/nn_heur.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/nn_heur.cpp -o $@

build/dists.o: src/lib/dists.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/dists.cpp -o $@

build/tour_solution.o: src/lib/tour_solution.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/tour_solution.cpp -o $@

build/semi_greedy_schemes.o: src/lib/semi_greedy_schemes.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/semi_greedy_schemes.cpp -o $@

build/choice_method.o: src/lib/choice_method.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/choice_method.cpp -o $@

build/parameters.o: src/lib/parameters.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/parameters.cpp -o $@

build/local_search.o: src/lib/local_search.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/local_search.cpp -o $@

build/path_relinking.o: src/lib/path_relinking.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/path_relinking.cpp -o $@

build/multi_start.o: src/lib/multi_start.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/multi_start.cpp -o $@

build/grasp.o: src/lib/grasp.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/grasp.cpp -o $@

build/stop_criterion.o: src/lib/stop_criterion.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/stop_criterion.cpp -o $@

clean:
	$(RM) -r build
	$(RM) $(TARGET)