#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "FadeObject.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

FadeObject::FadeObject()
{

}

FadeObject::~FadeObject()
{

}


void FadeObject::Start()
{
	Renderer = CreateUIRenderer(RenderOrder::FadeObject);
	Renderer->SetRenderScale(GlobalValue::WinScale);
	Renderer->SetRenderPos(GlobalValue::WinScale.Half());
	Renderer->Off();
}

void FadeObject::BlackInit(const float _FadeUpSpeed)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Fade_Dark.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\UI\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Fade_Dark.bmp"));
	}
	Renderer->SetTexture("Fade_Dark.bmp");
	FadeUpSpeed = _FadeUpSpeed;
}

void FadeObject::WhiteInit(const float _FadeUpSpeed)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Fade_White.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\UI\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Fade_White.bmp"));
	}
	Renderer->SetTexture("Fade_White.bmp");
	FadeUpSpeed = _FadeUpSpeed;
}

void FadeObject::Update(float _Delta)
{
	FadeIn(_Delta);
	FadeOut(_Delta);

	if (true == FadeDeathValue)
	{
		if (0.0f >= DeathTime)
		{
			Death();
		}
		DeathTime -= _Delta;
	}
}


void FadeObject::FadeIn(float _Delta)
{
	if (false == FadeInValue || true == FadeEnd)
	{
		return;
	}
	FadeSpeed += FadeUpSpeed *_Delta;
	Renderer->On();
	CurAlpha -= static_cast<int>(FadeSpeed * _Delta);
	
	if (0 >= CurAlpha)
	{
		CurAlpha = 0;
		FadeEnd = true;
	}

	Renderer->SetAlpha(CurAlpha);
}

void FadeObject::FadeOut(float _Delta)
{
	if (false == FadeOutValue || true == FadeEnd)
	{
		return;
	}
	FadeSpeed += FadeUpSpeed * _Delta;
	Renderer->On();
	CurAlpha += static_cast<int>(FadeSpeed * _Delta);

	if (255 <= CurAlpha)
	{
		CurAlpha = 255;
		FadeEnd = true;
	}

	Renderer->SetAlpha(CurAlpha);
}

void FadeObject::FadeDeath()
{
	FadeDeathValue = true;
}
