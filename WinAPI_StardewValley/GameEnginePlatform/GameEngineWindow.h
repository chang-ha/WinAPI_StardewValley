#pragma once
#include <Windows.h>
#include <string>

class GameEngineWindow
{
public:
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

protected:

private:
	static HINSTANCE Instance;
	std::string Title = "";
	HWND hWnd = nullptr;
	HDC Hdc = nullptr;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitInstance();
	void MyRegisterClass();
};

