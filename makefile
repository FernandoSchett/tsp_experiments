# compiler
GXX := g++

# compiler flags
GXXFLAGS :=

# target executable
TARGET := TSP

# header files
INCLUDES := -I src/include

# source files
SOURCES := src/lib/io_inst.cpp  

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


clean:
	$(RM) -r build
	$(RM) $(TARGET)