﻿/*
----------------------------------------
Initialize d3d11 COMs(swapchain, dev, devcon) and a window, close the window and clean d3d11 COMs.
The order of init and close is important.
----------------------------------------
*/
// include the basic windows header files and the Direct3D header files
#include <windows.h> // 创建窗口就必须调用windows.h和windowsx.h
#include <windowsx.h>
#include <d3d11.h> // d3d11头文件
#include <stdio.h>
#pragma comment (lib, "d3d11.lib") // 引入一个lib
// global declarations
IDXGISwapChain *swapchain;
ID3D11Device *dev;
ID3D11DeviceContext *devcon;
void InitD3D(HWND hWnd);
void CleanD3D(void);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//handle, prev_handle, cmd, num_cmd_show
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND hWnd; // 要生成的window的handle
    WNDCLASSEX wc; // class
    ZeroMemory(&wc, sizeof(WNDCLASSEX)); // 清理内存, 准备给wc用
    wc.cbSize = sizeof(WNDCLASSEX); //code block size
    wc.style = CS_HREDRAW | CS_VREDRAW; // 横向纵向移动的时候会重新绘制window
    wc.lpfnWndProc = WindowProc; // 回调函数设定
    wc.hInstance = hInstance; // 就是WinMain的第一个参数
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // 默认的鼠标样式
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW; // 背景颜色
    wc.lpszClassName = "WindowClass"; // class的名字
    RegisterClassEx(&wc); // 注册这个class
    RECT wr = { 0, 0, 800, 600 }; // 画一个矩形800x600
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE); // 根据这个content的大小得到一个window size
    hWnd = CreateWindowEx(NULL,
        "WindowClass",
        "Our First Direct3D Program",
        WS_OVERLAPPEDWINDOW,
        300,
        300,
        wr.right - wr.left, // window的宽(大于800)
        wr.bottom - wr.top, // window的长(大于600)
        NULL,
        NULL,
        hInstance,
        NULL);
    ShowWindow(hWnd, nCmdShow);
    InitD3D(hWnd);
    MSG msg;
    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // 非阻塞的循环, 如果没有的话就是False
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                break; // 如果是退出信号, 那么直接break出loop无限循环
        }
        else
        {
            // normal game code
        }
    }
    CleanD3D(); // break出来以后要关掉D3D
    return msg.wParam;
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0; // 此处直接return
    } break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam); // 如果case中没有return, 就会走到这里
}
void InitD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC scd; // swap chain的一些参数
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
    scd.BufferCount = 1; // 除了存储正在显示的数据的buffer外, 只有一个backbuffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 采用32bit color
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // reder target模式来使用buffer
    scd.OutputWindow = hWnd; // d3d11结果输出在hWnd
    scd.SampleDesc.Count = 4; // MSAA level 4
    scd.Windowed = TRUE; // 采用窗口而非全屏

    // create a device, device context and swap chain using the information in the scd struct
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

/*I think it is going to be good*  *  * /Users/cxl/PycharmProjects/DeleteComment/myTest/example.cpp  */
FILE f = fopen("/Users/cxl/PycharmProjects/DeleteComment/myTest/example.cpp")  // is it okay?
f.close()