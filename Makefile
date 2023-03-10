# constants
CC = i686-w64-mingw32-gcc
AS = nasm

CFLAGS = -Wall -Wextra -Werror -O2 -std=c11
LIBS = -pthread -lwinmm

SOURCE_DIR = src
BUILD_DIR = build

EXECUTABLE = HuTaoNom.exe

SOURCES = $(shell find $(SOURCE_DIR) -name "*.c")
OBJECTS = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

# targets
all: $(BUILD_DIR)/$(EXECUTABLE) $(BUILD_DIR)/bootloader.bin
	cp -r $(SOURCE_DIR)/assets $(BUILD_DIR)/assets

$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD_DIR)/bootloader.bin: $(SOURCE_DIR)/bootloader/main.asm
	mkdir -p $(dir $@)
	$(AS) -f bin $^ -o $@

# rules
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@ $(LIBS)

# other stuff
clean:
	rm -rf $(BUILD_DIR)