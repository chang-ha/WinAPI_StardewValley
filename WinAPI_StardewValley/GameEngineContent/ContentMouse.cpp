#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>

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
	Renderer = CreateRenderer(RenderOrder::UI);
	MouseCollision = CreateCollision(CollisionOrder::UI);
}

void ContentMouse::Init(const std::string& _FileName)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\UI\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
	}
	Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	Scale = Texture->GetScale();
	MouseCollision->SetCollisionScale(Scale*3);
}

void ContentMouse::Update(float _Delta)
{
}
