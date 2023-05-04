#include "GameEngineTexture.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>

GameEngineTexture::GameEngineTexture()
{

}

GameEngineTexture::~GameEngineTexture()
{
}

void GameEngineTexture::ResLoad(const std::string& _Path)
{
	HANDLE ImageHandle = LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (nullptr == ImageHandle)
	{
		MsgBoxAssert(_Path + " 이미지 로드에 실패하였습니다.");
		return;
	}

	BitMap = static_cast<HBITMAP>(ImageHandle);
	ImageDC = CreateCompatibleDC(nullptr);
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));
}
