# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -I/usr/local/include # Specify C++17 standard and yaml-cpp include directory

# Libraries
LDFLAGS = -lyaml-cpp # Link with yaml-cpp library

# Executable name
EXEC = yaml_parser

# Source files
SOURCES = main.cpp YamlParser.cpp

# Object files (automatically generated from source files)
OBJECTS = $(SOURCES:.cpp=.o)

# Target to build the executable
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

# Compile each source file into an object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJECTS) $(EXEC)

# Run the executable
run: $(EXEC)
	./$(EXEC)
