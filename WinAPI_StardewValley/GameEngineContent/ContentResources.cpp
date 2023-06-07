#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentResources.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

ContentResources::ContentResources()
{

}

ContentResources::~ContentResources()
{

}

void ContentResources::Init(const std::string& _FileName)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Resources\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
	}
	Renderer = CreateRenderer(_FileName, RenderOrder::BackGround);
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	Collision = CreateCollision(CollisionOrder::Resources);
	Collision->SetCollisionScale(TILESIZE * RENDERRATIO);
}
