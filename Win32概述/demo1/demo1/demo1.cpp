// demo1.cpp : 定义应用程序的入口点。
//

#include "pch.h"
#include "framework.h"
#include "demo1.h"
#include "resource.h"

#define MAX_LOADSTRING 100

/*
1、入口函数wWinMain
2、窗口注册类函数 MyRegisterClass
3、初始化函数 InitInstance
4、消息循环函数 WndProc
*/



// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 通配符
    TCHAR arr[16] = _T("123456");


    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEMO1, szWindowClass, MAX_LOADSTRING);

    // 调用窗口注册类
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 加载快捷资源  一般不用
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEMO1));


    /*
    typedef struct tagMSG {
    HWND        hwnd;   // 窗口句柄
    UINT        message;    // 消息类型
    WPARAM      wParam; // 辅助参数
    LPARAM      lParam; // 辅助参数
    DWORD       time;   // 消息发生时间
    POINT       pt; //消息产生时鼠标位置
    } MSG, *PMSG, NEAR *NPMSG, FAR *LPMSG;
*/
    
    MSG msg;    // 消息结构体

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0)) // 阻塞函数
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        // 消息循环
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW; // 风格
    wcex.lpfnWndProc    = WndProc;  // 函数指针指向函数，回调函数
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;    // 实例句柄
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMO1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);   // 鼠标
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); // 背景颜色
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DEMO1);  // 菜单资源
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // 小图标


    // 系统的注册函数
    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

    // 主窗口句柄
   HWND hWnd = CreateWindowW(szWindowClass,  // 类名
       /*szTitle*/
       L"我的第一个Win32项目",  // 项目名称
       WS_OVERLAPPEDWINDOW | WS_VSCROLL,
       // 相对屏幕的位置
       CW_USEDEFAULT, 0,     // 起始地址 -宏+0 表示默认值
       CW_USEDEFAULT, 0,       // 结束地址
       nullptr,     // 父类窗口句柄
       nullptr,     // 菜单句柄
       hInstance,   // 实例句柄
       nullptr);    // 窗口辅助信息

   if (!hWnd)
   {
      return FALSE;
   }


   // 绘制
   ShowWindow(hWnd, nCmdShow);
   // 更新
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//


