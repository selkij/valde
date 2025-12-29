# ===========================================================
# Configuration Profiles
# ===========================================================

CONFIG ?= Debug
ifeq ($(CONFIG),)
CONFIG := Debug
endif

ifeq ($(CONFIG), Debug)
    CFLAGS := -Wall -Wextra -g -O0
else ifeq ($(CONFIG), Release)
    CFLAGS := -Wall -Wextra -O2
else
    $(error Unknown CONFIG='$(CONFIG)' (expected Debug or Release))
endif

CPPFLAGS := -Iinclude
LDFLAGS  :=
LDLIBS   := -lncurses

CC := gcc

# ===========================================================
# Project Settings
# ===========================================================

PROJECT_NAME := valde

SRC_DIR     := src
INC_DIR     := include
BUILD_DIR   := build/$(CONFIG)

SRC := $(shell find $(SRC_DIR) -type f -name '*.c')

OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

# ===========================================================
# Targets
# ===========================================================

all: $(BUILD_DIR)/$(PROJECT_NAME)

$(BUILD_DIR)/$(PROJECT_NAME): $(OBJ)
	@echo "Linking: $@"
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling: $<"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

run: all
	./$(BUILD_DIR)/$(PROJECT_NAME)

clean:
	rm -rf build

print:
	@echo "SRC: $(SRC)"
	@echo "OBJ: $(OBJ)"
	@echo "CONFIG: $(CONFIG)"

.PHONY: all clean run print
