#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "GiftBox.h"
#include "ContentsEnum.h"
#include "ContentLevel.h"
#include "Player.h"
#include "ContentItem.h"
#include "ContentInventory.h"

GiftBox::GiftBox()
{

}

GiftBox::~GiftBox()
{

}

void GiftBox::Start()
{
	if (nullptr == ResourcesManager::GetInst().FindSprite("GiftBox.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Objects\\");

		ResourcesManager::GetInst().CreateSpriteSheet("GiftBox", FilePath.PlusFilePath("GiftBox.bmp"), 11, 1);
	}

	if (nullptr == GameEngineSound::FindSound("getnewitem.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("getnewitem.wav"));
	}
	Renderer = CreateRenderer(RenderOrder::PlayBelow);
	Renderer->SetRenderPos(TILESIZE.Half() * RENDERRATIO);
	Renderer->SetRenderScale(float4{16, 19} * RENDERRATIO);

	Renderer->CreateAnimation("GiftBox_Idle", "GiftBox", 0, 0);
	Renderer->CreateAnimation("GiftBox_Use", "GiftBox", 1, 10, 0.12f, false);
	Renderer->ChangeAnimation("GiftBox_Idle");

	Collision = CreateCollision(CollisionOrder::Resources);
	Collision->SetCollisionPos(TILESIZE.Half() * RENDERRATIO);
	Collision->SetCollisionScale((TILESIZE - float4{ 2,2 }) * RENDERRATIO);
}

void GiftBox::Update(float _Delta)
{
	std::vector<GameEngineCollision*> _CollisionResult;
	if (true == Collision->Collision(CollisionOrder::PlayerAction, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
	{
		Renderer->ChangeAnimation("GiftBox_Use");
		Collision->Death();

		ContentItem* Item = PlayLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
		Item->Init("Seed_Parsnip.bmp", ItemType::Seed, 15);
		ContentInventory::MainInventory->PushItem(Item);

		Player::MainPlayer->ChangeState(PlayerState::OpenBox);
		EffectPlayer = GameEngineSound::SoundPlay("getnewitem.wav");
	}

	if (true == Renderer->IsAnimation("GiftBox_Use") && true == Renderer->IsAnimationEnd())
	{
		Death();
	}
}

