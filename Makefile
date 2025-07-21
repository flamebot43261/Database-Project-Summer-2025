# Makefile for the Vinyl Record E-Commerce CLI

# Compiler
CXX = g++

# Compiler flags: -g for debugging, -Wall, -std=c++11, and include paths
# We combine all flags here for consistency.
CXXFLAGS = -g -Wall -std=c++11 -I./include -I/usr/include/cppconn

# Linker flags and libraries
# IMPORTANT: Replace with the actual path to your MySQL Connector/C++ library directory if different
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lmysqlcppconn

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Executable name
EXECUTABLE = $(BINDIR)/vinyl_store

# Default target
all: $(EXECUTABLE)

# Rule to link the executable
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Build complete. Executable is at $(EXECUTABLE)"

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJDIR) $(BINDIR)

# Phony targets
.PHONY: all clean