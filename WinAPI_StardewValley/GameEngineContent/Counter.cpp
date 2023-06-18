#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Counter.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

Counter::Counter()
{

}

Counter::~Counter()
{

}

void Counter::Start()
{
	GameEngineWindowTexture* Texture = nullptr;
	if (false == ResourcesManager::GetInst().IsLoadTexture("Counter.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Over");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Counter.bmp"));
	}
	Texture = ResourcesManager::GetInst().FindTexture("Counter.bmp");
	Renderer = CreateRenderer(RenderOrder::PlayBelow);
	Renderer->SetTexture("Counter.bmp");
	Renderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);

	Collision = CreateCollision(CollisionOrder::Shop);
	Collision->SetCollisionScale(float4{1, 2} * TILESIZE * RENDERRATIO);
	Collision->SetCollisionPos({});
}

void Counter::Update(float _Delta)
{

}