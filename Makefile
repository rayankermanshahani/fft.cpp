# compiler 
CXX = g++

# compiler flags
CXXFLAGS = -std=c++17 -O3 -g -Wall -Wextra -pedantic -march=native

# libraries
LIBS = -lm

# source file
SRC = fft.cpp

# build directory
BUILD_DIR = build

# target executable
TARGET = fft_benchmark

# target executable full path
TARGET_EXEC = $(BUILD_DIR)/$(TARGET)

# defualt target: build the executable
all: $(TARGET_EXEC)

# rule to link executable
$(TARGET_EXEC): $(SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@ $(LIBS)
	@echo "Build successful: $(TARGET_EXEC)"

# rule to create build directory
$(BUILD_DIR): 
	mkdir -p $@
	@echo "Created directory: $(BUILD_DIR)"

# phony target for cleaning build artifacts
.PHONY: clean
clean: 
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR)

# phony target for default 'all' rule
.PHONY: all

