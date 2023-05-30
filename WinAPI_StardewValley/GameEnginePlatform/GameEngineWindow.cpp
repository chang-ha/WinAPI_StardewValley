#include <GameEngineBase/GameEngineDebug.h>

#include "GameEngineWindow.h"

HINSTANCE GameEngineWindow::Instance = nullptr;
GameEngineWindow GameEngineWindow::MainWindow;
bool GameEngineWindow::IsWindowUpdate = true;
bool GameEngineWindow::IsFocusValue = false;

GameEngineWindow::GameEngineWindow()
{

}

GameEngineWindow::~GameEngineWindow()
{
    if (nullptr != BackBuffer)
    {
        delete BackBuffer;
        BackBuffer = nullptr;
    }

    if (nullptr != WindowBuffer)
    {
        delete WindowBuffer;
        WindowBuffer = nullptr;
    }
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

    Hdc = GetDC(hWnd);

    WindowBuffer = new GameEngineWindowTexture();
    WindowBuffer->ResCreate(Hdc);

    BackBuffer = new GameEngineWindowTexture();
    BackBuffer->ResCreate(WindowBuffer->GetScale());

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
}

LRESULT CALLBACK GameEngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SETFOCUS:
    {
        IsFocusValue = true;
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    case WM_KILLFOCUS:
    {
        IsFocusValue = false;
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        IsWindowUpdate = false;
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
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = GameEngineWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = Instance;
    wcex.hIcon = nullptr; 
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "DefaultWindow";
    wcex.hIconSm = nullptr;
    
    if (false == RegisterClassExA(&wcex))
    {
        MsgBoxAssert("윈도우 클래스 등록에 실패하였습니다.");
        return;
    }

    Check = true;
}

void GameEngineWindow::MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)())
{
    if (nullptr != _Start)
    {
        _Start(_Inst);
    }

    MSG msg;
    while (IsWindowUpdate)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (nullptr != _Update)
            {
                _Update();
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        // Dead Time
        if (nullptr != _Update)
        {
            _Update();
        }
    }

    if (nullptr != _End)
    {
        _End();
    }

    return;
}

void GameEngineWindow::SetPosAndScale(const float4& _Pos, const float4& _Scale)
{
    Scale = _Scale;
    if (nullptr != BackBuffer)
    {
        delete BackBuffer;
        BackBuffer = new GameEngineWindowTexture();
        BackBuffer->ResCreate(Scale);
    }
    RECT Rc = { 0, 0, _Scale.iX(), _Scale.iY() };
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);
    SetWindowPos(hWnd, nullptr, _Pos.iX() + Rc.left, _Pos.iY(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}

void GameEngineWindow::DoubleBuffering()
{
    float4 CopyLeftTop = float4::ZERO;
    float4 CopyRightBot = BackBuffer->GetScale();
    
    WindowBuffer->TransCopy(BackBuffer, Scale.Half(), BackBuffer->GetScale() * CopyRatio, CopyLeftTop, CopyRightBot, RGB(255, 0, 255));
    // WindowBuffer->BitCopy(BackBuffer, Scale.Half(), BackBuffer->GetScale());
}

void GameEngineWindow::ClearBackBuffer()
{
    Rectangle(BackBuffer->GetImageDC(), 0, 0, BackBuffer->GetScale().iX(), BackBuffer->GetScale().iY());
}

float4 GameEngineWindow::GetMousePos()
{
    POINT MoniterPoint;
    GetCursorPos(&MoniterPoint);
    ScreenToClient(hWnd, &MoniterPoint);

    return float4{ static_cast<float>(MoniterPoint.x), static_cast<float>(MoniterPoint.y) };
}

void GameEngineWindow::CursorOff()
{
    ShowCursor(FALSE);
}