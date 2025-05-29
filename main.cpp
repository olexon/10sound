#pragma comment(lib, "winmm.lib")
#include <Windows.h>

constexpr auto STARTUP_SOUND = "C:\\10sound\\startup\\snd.wav";
constexpr auto SUSPEND_SOUND = "C:\\10sound\\suspend\\snd.wav";
constexpr auto SHUTDOWN_SOUND = "C:\\10sound\\shutdown\\snd.wav";

LRESULT CALLBACK WindowProc(HWND hWND, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        PlaySoundA(STARTUP_SOUND, NULL, SND_SYNC);
        break;
    case WM_POWERBROADCAST: //untested
        PlaySoundA(SUSPEND_SOUND, NULL, SND_SYNC);
        break;
    case WM_QUERYENDSESSION: {
        if (!lParam)
            PlaySoundA(SHUTDOWN_SOUND, NULL, SND_SYNC);
        break;
    }
    }

    return DefWindowProcA(hWND, uMsg, wParam, lParam);
}

bool Init(HINSTANCE hInstance) {
    WNDCLASSA wc = {}; //tzw sracz

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "NaszaKlasa";

    RegisterClassA(&wc);

    HWND hWND = CreateWindowExA(
        NULL, 
        wc.lpszClassName, 
        "Dummy",
        NULL,
        CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
        nullptr, nullptr, hInstance, nullptr);

    if (hWND)
        return true;

    return false;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow) {
    if (!Init(hInstance))
        return -1;

    MSG msg;
    while (GetMessageA(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return (int)msg.wParam;
}