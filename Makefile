# Makefile for rpi4-bmos


# Cross Compiler
CROSS_COMPILE=aarch64-none-elf-
AS		= $(CROSS_COMPILE)as
CC		= $(CROSS_COMPILE)gcc
LD		= $(CROSS_COMPILE)ld
OBJCOPY	= $(CROSS_COMPILE)objcopy
OBJDUMP	= $(CROSS_COMPILE)objdump


# Directories
BUILD_DIR	= build
INCLUDE_DIR	= include
SRC_DIRS	= kernel drivers arch lib


# Output file
TARGET		= kernel8


# Compile options
CFLAGS += -Wall -Werror -ffreestanding -nostdlib -mgeneral-regs-only -I. -I$(INCLUDE_DIR)

BUILD_TYPE	?= release
ifeq ($(BUILD_TYPE),debug)
	CFLAGS	+= -g -O0
	LDFLAGS	+= -g
else
	CFLAGS	+= -O2
endif

# Linker options
LDFLAGS		+= -T linker.ld


# Source files
C_SOURCES	:= $(shell find $(SRC_DIRS) -name "*.c")
S_SOURCES	:= $(shell find $(SRC_DIRS) -name "*.S")

# Convert source files to object files
C_OBJECTS	:= $(patsubst %.c, $(BUILD_DIR)/%.o, $(C_SOURCES))
S_OBJECTS	:= $(patsubst %.S, $(BUILD_DIR)/%.o, $(S_SOURCES))

# Dependency files
DEPENDS		:= $(C_OBJECTS:.o=d)

# Object files
OBJECTS		= $(C_OBJECTS) $(S_OBJECTS)


# Default target
all: $(BUILD_DIR)/$(TARGET).img

# Debug build target
debug:
	$(MAKE) BUILD_TYPE=debug all


# Rule to build the final image
$(BUILD_DIR)/$(TARGET).img: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Rule to build the final ELF
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

# Rules to compile C and Assembly sources
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	mkdir -p $(dir $@)
	$(AS) -c $< -o $@

# Include dependency files if exist
-include $(DEPENDS)


# Clean build
clean:
	rm -rf $(BUILD_DIR)

dump:
	$(OBJDUMP) -D $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).dump

.PHONY: all clean debug dump
