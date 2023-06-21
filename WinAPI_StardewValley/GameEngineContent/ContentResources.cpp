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

void ContentResources::Start()
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
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Shadow_" + _FileName));
	}
	// Resources Renderer
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	Renderer = CreateRenderer(_FileName, RenderOrder::BackGround);
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderPos(TILESIZE.Half() * RENDERRATIO);
	Renderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);

	// ShadowRenderer
	ShadowRenderer = CreateRenderer("Shadow_" + _FileName, RenderOrder::PlayBelow);
	ShadowRenderer->SetAlpha(120);
	ShadowRenderer->SetRenderPos(TILESIZE.Half() * RENDERRATIO);
	ShadowRenderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	// ShadowRenderer->SetRenderPos(float4{ 0, 14 } *RENDERRATIO);

	// Resources Collision
	Collision = CreateCollision(CollisionOrder::Resources);
	Collision->SetCollisionPos(TILESIZE.Half() * RENDERRATIO);
	Collision->SetCollisionScale(TILESIZE * RENDERRATIO);
}

void ContentResources::Hitten()
{
	if (true == IsHitten)
	{
		switch (HittenStep)
		{
		case 0:
			++HittenStep;
			AddPos({-2, -2});
			break;
		case 1:
			++HittenStep;
			AddPos({ +2, -2 });
			break;
		case 2:
			++HittenStep;
			AddPos({ +2, +2 });
			break;
		case 3:
			AddPos({ -2, +2 });
			HittenStep = 0;
			IsHitten = false;
			break;
		default:
			break;
		}
	}
}

