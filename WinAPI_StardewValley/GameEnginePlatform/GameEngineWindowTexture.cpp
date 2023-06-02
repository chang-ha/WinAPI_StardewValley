#include <GameEngineBase/GameEngineDebug.h>

#include "GameEngineWindowTexture.h"
#include "GameEngineWindow.h"

#pragma comment(lib, "msimg32.lib")

GameEngineWindowTexture::GameEngineWindowTexture()
{

}

GameEngineWindowTexture::~GameEngineWindowTexture()
{
}

float4 GameEngineWindowTexture::GetScale()
{
	return { static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
}

void GameEngineWindowTexture::ScaleCheck()
{
	GetObject(BitMap, sizeof(BITMAP), &Info);
	// BITMAP OldInfo;
	// GetObject(OldBitMap, sizeof(BITMAP), &OldInfo);
}

void GameEngineWindowTexture::ResLoad(const std::string& _Path)
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
	ScaleCheck();
}

void GameEngineWindowTexture::ResCreate(const float4& _Scale)
{
	HANDLE ImageHandle = CreateCompatibleBitmap(GameEngineWindow::MainWindow.GetHDC(), _Scale.iX(), _Scale.iY());
	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("BackBuffer 생성에 실패하였습니다.");
		return;
	}
	BitMap = static_cast<HBITMAP>(ImageHandle);
	ImageDC = CreateCompatibleDC(nullptr);
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));
	ScaleCheck();
}

void GameEngineWindowTexture::BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos)
{
	BitCopy(_CopyTexture, _Pos, _CopyTexture->GetScale());
}

void GameEngineWindowTexture::BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale)
{
	HDC CopyImageDC = _CopyTexture->GetImageDC();
	BitBlt(ImageDC, 
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(), 
		_Scale.iY(), 
		CopyImageDC, 0, 0, SRCCOPY);
}

void GameEngineWindowTexture::TransCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, int _TransColor)
{
	HDC CopyImageDC = _CopyTexture->GetImageDC();
	TransparentBlt(ImageDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(),
		_Scale.iY(),
		CopyImageDC,
		_OtherPos.iX(), 
		_OtherPos.iY(), 
		_OtherScale.iX(),
		_OtherScale.iY(),
		_TransColor
	);
}

unsigned int GameEngineWindowTexture::GetColor(unsigned int _DefaultColor, float4 _Pos)
{
	if (0 > _Pos.iX())
	{
		return _DefaultColor;
	}

	if (0 > _Pos.iY())
	{
		return _DefaultColor;
	}

	if (GetScale().iX() <= _Pos.iX())
	{
		return _DefaultColor;
	}

	if (GetScale().iX() <= _Pos.iY())
	{
		return _DefaultColor;
	}

	return GetPixel(ImageDC, _Pos.iX(), _Pos.iY());
}

void GameEngineWindowTexture::FillTexture(unsigned int _Color)
{
	RECT Rc;
	Rc.left = 0;
	Rc.top = 0;
	Rc.right = GetScale().iX();
	Rc.bottom = GetScale().iY();

	HBRUSH brh = CreateSolidBrush(_Color);
	FillRect(ImageDC, &Rc, brh);
	DeleteObject(brh);
}