CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2 -std=c11

#LIBS = 
SOURCE_DIR = src
BUILD_DIR = build

EXECUTABLE = HuTaoNom.exe

SOURCES = $(shell find $(SOURCE_DIR) -name "*.c")
OBJECTS = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

all: $(BUILD_DIR)/$(EXECUTABLE)
	cp -r $(SOURCE_DIR)/assets $(BUILD_DIR)/assets

$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(dir $@)

	$(CC) $(CFLAGS) -c $^ -o $@ $(LIBS)

clean:
	rm -rf $(BUILD_DIR)