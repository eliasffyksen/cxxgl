
DEBUG?=1

BUILD_PATH=./build
LIBS=glfw GL GLEW

INCLUDE_FILES:=$(wildcard src/*.hpp)
INCLUDE_FILES:=$(INCLUDE_FILES:src/%=$(BUILD_PATH)/include/%)

SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:%.cpp=$(BUILD_PATH)/%.o)

EXAMPLE_SRC=$(wildcard example/*.cpp)
EXAMPLE_OBJS=$(EXAMPLE_SRC:%.cpp=$(BUILD_PATH)/%.o)

CXX=clang++
AR=ar
CFLAGS?=-I$(BUILD_PATH)/include
CFLAGS+=-Wall -std=c++17

ifeq ($(DEBUG), 1)
	CFLAGS+=-O1 -ggdb -DDEBUG=1
else
	CFLAGS+=-O2
endif

.PHONY: all run build clean oglib main oglib_include

all: build

run: main
	./$(BUILD_PATH)/main

oglib: $(BUILD_PATH)/oglib.a
main: oglib oglib_include $(BUILD_PATH)/main
oglib_include: $(INCLUDE_FILES)

clean:
	rm -r $(BUILD_PATH)/*

$(BUILD_PATH)/include/%: src/%
	mkdir -p $(dir $@)
	cp $< $@

$(BUILD_PATH)/oglib.a: $(OBJS)
	mkdir -p $(dir $@)
	$(AR) rcs $@ $^

$(BUILD_PATH)/main: $(EXAMPLE_OBJS)
	mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) $(LIBS:%=-l%) -o $@ $^ $(BUILD_PATH)/oglib.a

$(BUILD_PATH)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -c -o $@ $<
