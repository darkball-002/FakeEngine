#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <RCJson.h>


std::vector<std::pair<std::wstring, std::wstring>> Config;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (uMsg == WM_CREATE) {

    }
    else if (uMsg == WM_PAINT) {
    }
    else if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"GameWindowClass";
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    // 設定視窗默認值
    std::wstring windowTitle = L" ";
    int windowHeight = 0;
    int windowWidth = 0;

    readJSON(L"config/Default.json", Config);

    for (const auto& item : Config) {
        // 這裡可以使用 item.first 和 item.second
        if (item.first == L"title") { windowTitle = item.second; }
        if (item.first == L"width") { windowWidth = std::stoi(item.second); }
        if (item.first == L"height") { windowHeight = std::stoi(item.second); }
    }

    HWND hwnd = CreateWindowExW(
        0, CLASS_NAME, windowTitle.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // 消息循環
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
