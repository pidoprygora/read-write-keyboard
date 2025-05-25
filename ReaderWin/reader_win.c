#include <windows.h>
#include <stdio.h>

int main() {
    DWORD pid;
    void* addr;

    printf("Enter the PID of the process: ");
    scanf("%lu", &pid);

    printf("Enter the address of the variable (in hex): ");
    scanf("%p", &addr);

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, pid);
    if (hProcess == NULL) {
        printf("Failed to open process: %lu\n", GetLastError());
        return 1;
    }

    int value;
    int prevValue = -1; 
    SIZE_T bytesRead;

    printf("Monitoring memory...\nPress Ctrl+C to stop.\n");

    while (1) {
        if (ReadProcessMemory(hProcess, addr, &value, sizeof(value), &bytesRead)) {
            if (value != prevValue) {
                printf("New value read: %d\n", value);
                prevValue = value;
            }
        }
        else {
            printf("Memory read error: %lu\n", GetLastError());
            break;
        }
        Sleep(500); 
    }

    CloseHandle(hProcess);
    return 0;
}
