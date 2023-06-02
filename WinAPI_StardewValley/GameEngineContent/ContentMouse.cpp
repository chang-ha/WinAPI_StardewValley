#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentsEnum.h"
#include "ContentMouse.h"

ContentMouse::ContentMouse()
{
}

ContentMouse::~ContentMouse()
{

}

void ContentMouse::Start()
{
	MouseRenderer = CreateRenderer(RenderOrder::UIMouse);
	MouseCollision = CreateCollision(CollisionOrder::UI);
	if (false == ResourcesManager::GetInst().IsLoadTexture("Cursor01.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\UI\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Cursor01.bmp"));
	}
	Texture = ResourcesManager::GetInst().FindTexture("Cursor01.bmp");
	MouseRenderer->SetTexture("Cursor01.bmp");
	MouseRenderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	MouseRenderer->SetRenderPos(Texture->GetScale().Half() * RENDERRATIO);
	MouseCollision->SetCollisionScale(Texture->GetScale() * RENDERRATIO);
}

void ContentMouse::Update(float _Delta)
{
}
