#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "BackGround.h"
#include "ContentsEnum.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
	Renderer = CreateRenderer(RenderOrder::BackGround);
	CollisionRenderer = CreateRenderer(RenderOrder::BackGround);
	Renderer->On();
	CollisionRenderer->Off();
}

void BackGround::Update(float _Delta)
{
}

void BackGround::Init(const std::string& _FileName, float _RenderScaleRatio)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\BackGround\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
	}
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Texture->GetScale() * _RenderScaleRatio);
	Scale = Texture->GetScale();
	RenderScale = Texture->GetScale() * _RenderScaleRatio;
}

void BackGround::Init(const std::string& _FileName, const std::string& _CollisionFileName, float _RenderScaleRatio)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\BackGround\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_CollisionFileName));
	}
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Texture->GetScale() * _RenderScaleRatio);
	Scale = Texture->GetScale() * _RenderScaleRatio;
	RenderScale = Texture->GetScale() * _RenderScaleRatio;

	CollisionTexture = ResourcesManager::GetInst().FindTexture(_CollisionFileName);
	CollisionRenderer->SetTexture(_CollisionFileName);
	CollisionRenderer->SetRenderScale(Texture->GetScale() * _RenderScaleRatio);

}

void BackGround::SwitchBackGroundRender()
{
	BackGroundTexture = !BackGroundTexture;

	if (true == BackGroundTexture && nullptr != CollisionTexture)
	{
		Renderer->On();
		CollisionRenderer->Off();
	}
	else  if(false == BackGroundTexture && nullptr != CollisionTexture)
	{
		Renderer->Off();
		CollisionRenderer->On();
	}
}

void BackGround::ResetBackGroundRender()
{
	if (false == BackGroundTexture && nullptr != CollisionTexture)
	{
		BackGroundTexture = !BackGroundTexture;
		Renderer->On();
		CollisionRenderer->Off();
	}
}
