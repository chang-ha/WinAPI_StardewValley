#pragma once
#include <Windows.h>
#include <string>

#include <GameEngineBase/GameEngineMath.h>

class GameEngineWindowTexture
{
public:
	// constructer destructer
	GameEngineWindowTexture();
	~GameEngineWindowTexture();

	// delete function
	GameEngineWindowTexture(const GameEngineWindowTexture& _Ohter) = delete;
	GameEngineWindowTexture(GameEngineWindowTexture&& _Ohter) noexcept = delete;
	GameEngineWindowTexture& operator=(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture& operator=(GameEngineWindowTexture&& _Other) noexcept = delete;

	void ResLoad(const std::string& _Path);

	HDC GetImageDC()
	{
		return ImageDC;
	}

	void ResCreate(HDC _ImageDC)
	{
		ImageDC = _ImageDC;
		ScaleCheck();
	}

	void ResCreate(const float4& _Scale);

	float4 GetScale();

	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos);
	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale);
	void TransCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, int _TransColor = RGB(255, 255, 255));
	void PlgCopy(GameEngineWindowTexture* _CopyTexture, GameEngineWindowTexture* _MaskTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, float _Angle);
	void AlphaCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, unsigned char _Alpha);

	unsigned int GetColor(unsigned int _DefaultColor, float4 _Pos);

	void FillTexture(unsigned int _Color);
protected:

private:
	HBITMAP BitMap = nullptr;
	HBITMAP OldBitMap = nullptr;
	HDC ImageDC = nullptr;	
	BITMAP Info = {};
	void ScaleCheck();
};

