TARGET := concatenate
SRC_DIR := src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)

SRCS := concatenate.cpp options.cpp
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

CXX := g++
CXXFLAGS := -Wall -Werror -pedantic -Weffc++ -Wconversion --std=c++20
CPPFLAGS :=
LDFLAGS :=

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)