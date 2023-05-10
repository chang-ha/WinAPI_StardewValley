#pragma once
#include <Windows.h>
#include <string>
#include "GameEngineWindowTexture.h"

class GameEngineWindow
{
public:
	// MainWindow (Singleton Pattern)
	static GameEngineWindow MainWindow;

	// constructer destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete function
	GameEngineWindow(const GameEngineWindow& _Ohter) = delete;
	GameEngineWindow(GameEngineWindow&& _Ohter) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

	void Open(const std::string& _Title, HINSTANCE _hInstance);

	static void MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)());

	HDC GetHDC()
	{
		return Hdc;
	}

	float4 GetScale()
	{
		return Scale;
	}

	static void WindowUpdateOff()
	{
		IsWindowUpdate = false;
	}

	GameEngineWindowTexture* GetWindowBuffer()
	{
		return WindowBuffer;
	}

	GameEngineWindowTexture* GetBackBuffer()
	{
		return BackBuffer;
	}

	void SetPosAndScale(const float4& _Pos, const float4& _Scale);

	void ClearBackBuffer();
	void DoubleBuffering();
protected:

private:
	static HINSTANCE Instance;
	static bool IsWindowUpdate;
	std::string Title = "";
	HWND hWnd = nullptr;
	HDC Hdc = nullptr;
	
	GameEngineWindowTexture* WindowBuffer = nullptr;
	GameEngineWindowTexture* BackBuffer = nullptr;
	float4 Scale;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitInstance();
	void MyRegisterClass();
};

