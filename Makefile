# ===========================================================
# Project Settings
# ===========================================================

PROJECT_NAME := valde

# Project structure
SRC_DIR     := src
INC_DIR     := include
BUILD_DIR   := build/$(CONFIG)

# Auto-discover source files (recursive possible)
SRC := $(wildcard $(SRC_DIR)/*.c)

# Turn .c into .o inside build directory, keeping structure
OBJ := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# ===========================================================
# Configuration Profiles
# ===========================================================

CONFIG ?= Debug
ifeq ($(CONFIG),) # If CONFIG is empty set "Debug" by default.
CONFIG := Debug
endif

ifeq ($(CONFIG), Debug)
    CFLAGS := -Wall -Wextra -g -O0
else ifeq ($(CONFIG), Release)
    CFLAGS := -Wall -Wextra -O2
else
    $(error Unknown CONFIG='$(CONFIG)' (expected Debug or Release))
endif

CPPFLAGS := -I$(INC_DIR)
LDFLAGS  :=
LDLIBS   := -lncurses

CC := gcc

# ===========================================================
# Targets
# ===========================================================

all: $(BUILD_DIR)/$(PROJECT_NAME)

# Link final binary
$(BUILD_DIR)/$(PROJECT_NAME): $(OBJ)
	@echo "Linking: $@"
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

# Compile .c to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling: $<"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Ensure build directory exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# ===========================================================
# Convenience
# ===========================================================

run: all
	./$(BUILD_DIR)/$(PROJECT_NAME)

clean:
	rm -rf build

# Print discovered sources/objects (debugging Makefile)
print:
	@echo "SRC: $(SRC)"
	@echo "OBJ: $(OBJ)"
	@echo "CONFIG: $(CONFIG)"

.PHONY: all clean run print
