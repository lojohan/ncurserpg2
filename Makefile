CFLAGS=-Wall -Wno-error=unused-variable -std=c++0x
LDLIBS=-lncursesw -lboost_regex
BIN=output/RPG
BUILD_DIR=build
DEPS_DIR=$(BUILD_DIR)

CPP_FILES:=$(shell find * -iname '*.cpp')
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
	g++ -c $(CFLAGS) -o $@ $<
	@echo -------------------------------------------------------------------------------- 


print:
	@echo "Src files:"
	@for f in $(CPP_FILES); do echo "  $$f"; done
	@echo "Depend file:"
	@for f in $(DEPS); do echo "  $$f"; done
	@echo "Object files:"
	@for f in $(OBJS); do echo "  $$f"; done

clean:
	@rm -vf $(DEPS) $(OBJS)

