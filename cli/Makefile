# Compiler settings
CXX      := clang++
CXXFLAGS := -std=c++23

# Commands mapping (CapitalName:lowercase_filename)
COMMAND_MAP := Base:base Add:add Build:build New:new Start:start

# Output targets
PCM_DIR  := pcm
BIN_DIR  := bin
TARGET   := hermes
PREFIX   := /usr/local/bin

# Generate target files array explicitly
PCMS     := $(foreach pair,$(COMMAND_MAP),$(PCM_DIR)/Commands.$(word 1,$(subst :, ,$(pair))).pcm)
OBJS     := $(foreach pair,$(COMMAND_MAP),$(BIN_DIR)/Commands.$(word 1,$(subst :, ,$(pair))).o) $(BIN_DIR)/main.o

.PHONY: all clean install

# Default target
all: $(TARGET)

# Step 4: Link everything into the final binary
$(TARGET): $(OBJS)
	@echo "4. Linking everything into final binary..."
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Step 3: Compile main application layer
$(BIN_DIR)/main.o: main.cpp $(PCMS) | $(BIN_DIR)
	@echo "3. Compiling main application layer..."
	$(CXX) $(CXXFLAGS) -fprebuilt-module-path=$(PCM_DIR) -c $< -o $@

# Step 2: Generate object files from module pcm maps
$(BIN_DIR)/Commands.%.o: $(PCM_DIR)/Commands.%.pcm | $(BIN_DIR)
	@echo "2. Generating object file for $*..."
	$(CXX) $(CXXFLAGS) -fprebuilt-module-path=$(PCM_DIR) -c $< -o $@

# Hardcoded base dependency constraint
$(PCM_DIR)/Commands.Base.pcm: commands/base.command.cpp | $(PCM_DIR)
	@echo "1. Precompiling Base module interface..."
	$(CXX) $(CXXFLAGS) --precompile -x c++-module $< -o $@

# Step 1 Dynamic Generator: Loops over the map to link the precise file casings
define GENERATE_MODULE_RULE
	CAP_NAME := $$(word 1,$$(subst :, ,$(1)))
	LOW_NAME := $$(word 2,$$(subst :, ,$(1)))

	# Skip base generation because it has an explicit bootstrap rule above
	ifneq ($$(CAP_NAME),Base)
	$$(PCM_DIR)/Commands.$$(CAP_NAME).pcm: commands/$$(LOW_NAME).command.cpp $$(PCM_DIR)/Commands.Base.pcm | $$(PCM_DIR)
		@echo "1. Precompiling $$(CAP_NAME) module interface..."
		$$(CXX) $$(CXXFLAGS) -fprebuilt-module-path=$$(PCM_DIR) --precompile -x c++-module $$< -o $$@
	endif
endef

# Evaluate the macro generator for all pairs in our map
$(foreach pair,$(COMMAND_MAP),$(eval $(call GENERATE_MODULE_RULE,$(pair))))

# Directory templates
$(PCM_DIR) $(BIN_DIR):
	mkdir -p $@

# Step 5: Global installer command
install: all
	@echo "5. Installing $(TARGET) globally to $(PREFIX)..."
	sudo cp $(TARGET) $(PREFIX)/$(TARGET)
	sudo chmod +x $(PREFIX)/$(TARGET)
	@$(MAKE) clean

# Step 6: Artifact wipe routine
clean:
	@echo "6. Cleaning up build artifacts..."
	rm -rf $(PCM_DIR) $(BIN_DIR) $(TARGET)
