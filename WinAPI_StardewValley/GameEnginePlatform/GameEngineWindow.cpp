#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>

HINSTANCE GameEngineWindow::Instance = nullptr;
GameEngineWindow GameEngineWindow::MainWindow;

GameEngineWindow::GameEngineWindow()
{

}

GameEngineWindow::~GameEngineWindow()
{

}

void GameEngineWindow::Open(const std::string& _Title, HINSTANCE _hInstance)
{
    Instance = _hInstance;
    Title = _Title;
    if (nullptr == Instance)
    {
        MsgBoxAssert("hInstance없이 윈도우를 만들 수 없습니다.");
        return;
    }
    MyRegisterClass();
    InitInstance();
}

void GameEngineWindow::InitInstance()
{
    hWnd = CreateWindowA("DefaultWindow", Title.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, Instance, nullptr);

    if (!hWnd)
    {
        MsgBoxAssert("윈도우 생성에 실패했습니다.");
        return;
    }
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
}


// lpfnWndProc = GameEngineWindow::WndProc을 받는데
// lpfnWndProc를 타고 가보면 함수포인터를 받을 때 앞에 CALLBACK이라고 붙어있음
// CALLBACK = __stdcall (함수호출규약)으로 되어있는데
// 해당 함수를 받는 쪽이 __stdcall을 원하니 함수 선언 및 구현시 맞춰줘야함
LRESULT CALLBACK GameEngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void GameEngineWindow::MyRegisterClass()
{
    static bool Check = false;
    if (true == Check)
    {
        return;
    }
    WNDCLASSEXA wcex;
    // WNDCLASSEXW wcex; << 문자열을 wide byte로 처리 (맨 뒤의 W)
    // WNDCLASSEXA wcex; << 문자열을 multi byte로 처리 (맨 뒤의 A)
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = GameEngineWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = Instance;
    wcex.hIcon = nullptr; // LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWTESTPROJECT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "DefaultWindow";
    wcex.hIconSm = nullptr; // LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    
    // RegisterClassExA의 return은 ATOM == unsigned short & 함수가 실패하면 return값은 0
    if (false == RegisterClassExA(&wcex))
    {
        MsgBoxAssert("윈도우 클래스 등록에 실패하였습니다.");
        return;
    }

    Check = true;
}

void GameEngineWindow::MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)())
{
    // 윈도우가 뜨기 전에 로딩해야할 이미지, 사운드등을 처리하는 단계
    if (nullptr != _Start)
    {
        _Start(_Inst);
    }
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (nullptr != _Update)
        {
            _Update();
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (nullptr != _End)
    {
        _End();
    }

    //(int)msg.wParam;
    return;
}