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

void BackGround::Render()
{
}

void BackGround::Release()
{

}

void BackGround::Init(const std::string& _FileName)
{
	FileName = _FileName;
	if (false == ResourcesManager::GetInst().IsLoadTexture(FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\BackGround\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(FileName));
		// CollisionTexture = ResourcesManager::GetInst().TextureLoad("Collision_" + FileName);
	}
	Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	// CollisionTexture = ResourcesManager::GetInst().FindTexture("Collision_" + FileName);
	Scale = Texture->GetScale();
}

void BackGround::SwitchRender()
{
	BackGroundTexture = !BackGroundTexture;

	if (BackGroundTexture)
	{
		Renderer->On();
		CollisionRenderer->Off();
	}
	else 
	{
		Renderer->Off();
		CollisionRenderer->On();
	}
}
