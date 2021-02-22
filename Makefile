
DEBUG?=1

BUILD_PATH=./build
LIBS=glfw GL GLEW

SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:%.cpp=$(BUILD_PATH)/%.o)

CXX=clang++
CFLAGS?=
CFLAGS+=-Wall

ifeq ($(DEBUG), 1)
	CFLAGS+=-O0 -ggdb -DDEBUG=1
else
	CFLAGS+=-O2
endif

.PHONY: all run build clean

all: build

run: build
	./$(BUILD_PATH)/main

build: $(BUILD_PATH)/main

clean:
	rm -r $(BUILD_PATH)/*

$(BUILD_PATH)/main: $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) $(LIBS:%=-l%) -o $@ $^

$(BUILD_PATH)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -c -o $@ $<
