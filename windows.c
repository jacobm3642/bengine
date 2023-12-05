#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int main() {
    // Register the window class
    const char CLASS_NAME[] = "EmptyWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                    // Optional window styles
        CLASS_NAME,           // Window class
        "Empty Window",       // Window text
        WS_OVERLAPPEDWINDOW,  // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,

        NULL,      // Parent window
        NULL,      // Menu
        GetModuleHandle(NULL), // Instance handle
        NULL       // Additional application data
    );

    if (hwnd == NULL) {
        return 1;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);

    // Main message loop
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}