#include <windows.h>
#include <stdio.h>

int value = 0;

int main() {
    printf("Enter a value: ");
    scanf("%d", &value);

    DWORD pid = GetCurrentProcessId();
    printf("Process PID: %lu\n", pid);
    printf("Address of variable 'value': %p\n", &value);

    while (1) {
        Sleep(1000);
    }

    return 0;
}
