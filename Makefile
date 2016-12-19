CFLAGS=-Wall -g -Wno-error=unused-variable -std=c++0x
LDLIBS=-lboost_regex -lrt
BIN=output/RPG
BUILD_DIR=build
DEPS_DIR=$(BUILD_DIR)

UI_OPTIONS := sdl ncurses
# default value, override with `make UI=<sdl, ncurses...>' or setting env. variable UI
UI ?= ncurses
UI_SRC_DIR = ui/$(UI)
UI_OPTIONS_TO_SKIP := $(filter-out $(UI), $(UI_OPTIONS))

# UI build specific settings
ifeq ($(UI), sdl)
	LDLIBS += -lSDL
	CFLAGS += -D BUILD_SDL
else
	LDLIBS += -lncursesw
	CFLAGS += -D BUILD_NCURSES
endif

CPP_FILES := $(shell find * -iname '*.cpp')
CPP_FILES := $(filter-out $(patsubst %,ui/%/%,$(UI_OPTIONS_TO_SKIP)), $(CPP_FILES))
OBJS:=$(addprefix $(BUILD_DIR)/, $(CPP_FILES:.cpp=.o))
DEPS:=$(addprefix $(DEPS_DIR)/, $(CPP_FILES:.cpp=.d))

$(BIN): $(OBJS)
	@echo ">>>> Building $@"
	@echo -------------------------------------------------------------------------------- 
	g++ -o $(BIN) $(OBJS) $(LDLIBS) 
	@echo -------------------------------------------------------------------------------- 

all: $(BIN)

-include $(DEPS)

# Make dependency files
$(DEPS_DIR)/%.d: %.cpp
	@mkdir -p $(dir $@)
	@g++ -std=c++0x -MM -MP -MT $(BUILD_DIR)/$(patsubst %.cpp,%.o,$<) -MT $@ -MF $@ $<

# Make object files
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "<<<< Building $@"
	@echo -------------------------------------------------------------------------------- 
	g++ -c $(CFLAGS) -O3 -o $@ $<
	@echo -------------------------------------------------------------------------------- 


print:
	@echo $(UI),$(UI_OPTIONS),$(UI_OPTIONS_TO_SKIP),$(patsubst %,ui/%/%,$(UI_OPTIONS_TO_SKIP)),$(CFLAGS)
	@echo "Src files:"
	@for f in $(CPP_FILES); do echo "  $$f"; done
	@echo "Depend file:"
	@for f in $(DEPS); do echo "  $$f"; done
	@echo "Object files:"
	@for f in $(OBJS); do echo "  $$f"; done

clean:
	@rm -vf $(DEPS) $(OBJS)

