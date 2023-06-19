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
	if (nullptr == _CopyTexture)
	{
		MsgBoxAssert("카피할 텍스처가 세팅되지 않았습니다.");
	}

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
	if (nullptr == _CopyTexture)
	{
		MsgBoxAssert("카피할 텍스처가 세팅되지 않았습니다.");
	}

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

void GameEngineWindowTexture::PlgCopy(GameEngineWindowTexture* _CopyTexture
	, GameEngineWindowTexture* _MaskTexture
	, const float4& _Pos
	, const float4& _Scale
	, const float4& _OtherPos
	, const float4& _OtherScale
	, float _Angle)
{
	if (nullptr == _CopyTexture)
	{
		MsgBoxAssert("카피할 텍스처가 세팅되지 않았습니다.");
	}

	if (nullptr == _MaskTexture)
	{
		MsgBoxAssert("마스크 텍스처가 없이 이미지 회전을 시킬수는 없습니다.");
	}

	if (_Angle == 180.0f)
	{
		// 완전히 반전되었을때는 에러가 발생할 수 있으므로 약간 틀어줌
		_Angle = 180.000001f;
	}

	POINT ArrPoint[3];

	GameEngineRect Rect = GameEngineRect(float4::ZERO, _Scale);

	float4 LeftTop = Rect.CenterLeftTop();
	float4 RightTop = Rect.CenterRightTop();
	float4 LeftBot = Rect.CenterLeftBot();

	ArrPoint[0] = (LeftTop.GetRotationToDegZ(_Angle) + _Pos).WindowPOINT();
	ArrPoint[1] = (RightTop.GetRotationToDegZ(_Angle) + _Pos).WindowPOINT();
	ArrPoint[2] = (LeftBot.GetRotationToDegZ(_Angle) + _Pos).WindowPOINT();

	HDC CopyImageDC = _CopyTexture->GetImageDC();

	PlgBlt(ImageDC,
		ArrPoint,
		CopyImageDC,
		_OtherPos.iX(), 
		_OtherPos.iY(), 
		_OtherScale.iX(), 
		_OtherScale.iY(), 
		_MaskTexture->BitMap,
		_OtherPos.iX(), 
		_OtherPos.iY());
}

void GameEngineWindowTexture::AlphaCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, unsigned char _Alpha)
{
	if (nullptr == _CopyTexture)
	{
		MsgBoxAssert("카피할 텍스처가 세팅되지 않았습니다.");
	}

	HDC CopyImageDC = _CopyTexture->GetImageDC();

	BLENDFUNCTION Function;

	Function.BlendOp = AC_SRC_OVER;
	Function.BlendFlags = 0;
	Function.SourceConstantAlpha = _Alpha;
	Function.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(
		ImageDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(),
		_Scale.iY(),
		CopyImageDC,
		_OtherPos.iY(), 
		_OtherPos.iX(), 
		_OtherScale.iX(),
		_OtherScale.iY(),
		Function
	);
}