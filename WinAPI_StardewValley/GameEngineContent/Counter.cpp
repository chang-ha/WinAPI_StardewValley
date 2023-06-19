#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Counter.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "ContentUIManager.h"

Counter::Counter()
{

}

Counter::~Counter()
{

}

void Counter::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Counter.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Over\\Counter.bmp"));
	}
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("Counter.bmp");
	Renderer = CreateRenderer(RenderOrder::PlayBelow);
	Renderer->SetTexture("Counter.bmp");
	Renderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);

	Collision = CreateCollision(CollisionOrder::Shop);
	Collision->SetCollisionScale(float4{3.0f, 1.5f} * TILESIZE * RENDERRATIO);
	Collision->SetCollisionPos({ -Texture->GetScale().X * 0.7f, Texture->GetScale().Y * 0.8f});
}

void Counter::Update(float _Delta)
{
	std::vector<GameEngineCollision*> _CollisionResult;
	if (true == Collision->Collision(CollisionOrder::PlayerAction, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
	{
		ContentUIManager::MainUI->ShopUIOn();
	}
}