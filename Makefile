
BUILD_PATH=./build
LIBS=glfw GL

SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:%.cpp=$(BUILD_PATH)/%.o)

CXX=clang++

.PHONY: all run build clean

all: build

run: build
	./$(BUILD_PATH)/main

build: $(BUILD_PATH)/main

clean:
	rm -r $(BUILD_PATH)/*

$(BUILD_PATH)/main: $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) $(LIBS:%=-l%) -o $@ $^

$(BUILD_PATH)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) -c -o $@ $<
