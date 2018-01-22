
#include <windows.h> #include <windowsx.h>
#include <d3d11.h> #include <stdio.h>
#pragma comment (lib, "d3d11.lib") IDXGISwapChain *swapchain;
ID3D11Device *dev;
ID3D11DeviceContext *devcon;
void InitD3D(HWND hWnd);
void CleanD3D(void);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND hWnd;     WNDCLASSEX wc;     ZeroMemory(&wc, sizeof(WNDCLASSEX));     wc.cbSize = sizeof(WNDCLASSEX);     wc.style = CS_HREDRAW | CS_VREDRAW;     wc.lpfnWndProc = WindowProc;     wc.hInstance = hInstance;     wc.hCursor = LoadCursor(NULL, IDC_ARROW);     wc.hbrBackground = (HBRUSH)COLOR_WINDOW;     wc.lpszClassName = "WindowClass";     RegisterClassEx(&wc);     RECT wr = { 0, 0, 800, 600 };     AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);     hWnd = CreateWindowEx(NULL,
        "WindowClass",
        "Our First Direct3D Program",
        WS_OVERLAPPEDWINDOW,
        300,
        300,
        wr.right - wr.left,         wr.bottom - wr.top,         NULL,
        NULL,
        hInstance,
        NULL);
    ShowWindow(hWnd, nCmdShow);
    InitD3D(hWnd);
    MSG msg;
    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))         {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                break;         }
        else
        {
                    }
    }
    CleanD3D();     return msg.wParam;
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;     } break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam); }
void InitD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC scd;     ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
    scd.BufferCount = 1;     scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     scd.OutputWindow = hWnd;     scd.SampleDesc.Count = 4;     scd.Windowed = TRUE; 
        D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        NULL,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &scd,
        &swapchain,
        &dev,
        NULL,
        &devcon);
}
void CleanD3D(void)
{
    swapchain->Release();
    dev->Release();
    devcon->Release();
}