
DEBUG?=1

BUILD_PATH?=./build
INCLUDE_PATH?=$(BUILD_PATH)/include

LIBS=glfw GL GLEW

SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:%.cpp=$(BUILD_PATH)/%.o)

HEADER_FILES:=$(wildcard src/*.hpp)
HEADER_FILES:=$(HEADER_FILES:src/%.hpp=$(INCLUDE_PATH)/%.hpp)

DEMOS:=$(wildcard demo/*.cpp)
DEMOS:=$(DEMOS:demo/%.cpp=%)

CXX?=clang++
CFLAGS?=
CFLAGS+=-Wall

ifeq ($(DEBUG), 1)
	CFLAGS+=-O1 -ggdb -DDEBUG=1
else
	CFLAGS+=-O2
endif

.PHONY: all run build clean headers

all: build

build: headers $(BUILD_PATH)/libcxxgl.a

clean:
	rm -r $(BUILD_PATH)/*

headers: $(HEADER_FILES)

.PHONY: $(DEMOS:%=demo_%)
$(DEMOS:%=demo_%): demo_%: $(BUILD_PATH)/demo/%

.PHONY: $(DEMOS:%=demo_run_%)
$(DEMOS:%=demo_run_%): demo_run_%: $(BUILD_PATH)/demo/%
	./$<

$(INCLUDE_PATH)/%.hpp: src/%.hpp
	mkdir -p $(dir $@)
	cp $< $@

$(BUILD_PATH)/demo/%: demo/%.cpp build
	mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) $(LIBS:%=-l%) -I$(INCLUDE_PATH) -o $@ $< $(BUILD_PATH)/libcxxgl.a

$(BUILD_PATH)/%.a: $(OBJS)
	mkdir -p $(dir $@)
	ar rcs $@ $^

$(BUILD_PATH)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -c -o $@ $<
