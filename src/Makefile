# # Compiler settings - Can change to g++ if required
# CXX=clang++

# # Compiler flags
# CXXFLAGS=-Wall -std=c++14 -fopenmp

# # Name of the executable
# TARGET=tradingSim

# # All cpp files to be compiled
# SRCS=main.cpp order.cpp orderBook.cpp

# # Default rule to make all
# all: $(TARGET)

# # Rule for linking the final executable
# # Depends on the object files (which will be compiled due to implicit rules)
# $(TARGET): $(SRCS:.cpp=.o)
# 	$(CXX) $(CXXFLAGS) -o $@ $^

# # Rule for compiling the source files to object files
# # Uses default implicit rule for compiling .cpp files to .o files

# # Clean rule
# clean:
# 	rm -f $(SRCS:.cpp=.o) $(TARGET)

# # Rule for running the program
# run: $(TARGET)
# 	./$(TARGET)

# Makefile for compiling a C++ project with multiple source files

# Compiler settings - Can change to clang++ if desired
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Linker flags
LDFLAGS =

# Add header file directories here
INCLUDES = -I.

# Source files to compile
SOURCES = main.cpp trader.cpp stock.cpp dataLoader.cpp portfolio.cpp portfolioUtils.cpp orderUtils.cpp orderBook.cpp order.cpp

# Object files to create
OBJECTS = $(SOURCES:.cpp=.o)

# Name of the executable to create
EXECUTABLE = trading_simulator

# Default target
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

# Rule for compiling source files to object files
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean target for removing compiled files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Additional dependencies for object files can be added below
