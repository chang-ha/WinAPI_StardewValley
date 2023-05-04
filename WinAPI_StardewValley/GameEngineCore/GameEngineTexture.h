#pragma once
#include <Windows.h>
#include <string>

class GameEngineTexture
{
public:
	// constructer destructer
	GameEngineTexture();
	~GameEngineTexture();

	// delete function
	GameEngineTexture(const GameEngineTexture& _Ohter) = delete;
	GameEngineTexture(GameEngineTexture&& _Ohter) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

	void ResLoad(const std::string& _Path);
	HDC GetImageDC()
	{
		return ImageDC;
	}
protected:

private:
	HBITMAP BitMap = nullptr;
	HBITMAP OldBitMap = nullptr;
	HDC ImageDC = nullptr;
};

