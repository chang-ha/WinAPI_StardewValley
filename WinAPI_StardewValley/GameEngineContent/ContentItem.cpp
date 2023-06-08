#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentItem.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "Player.h"
#include "ContentInventory.h"

ContentItem::ContentItem()
{

}

ContentItem::~ContentItem()
{

}

void ContentItem::Init(const std::string& _FileName, ItemType _Type)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Item\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Inventory_" +_FileName));
	}
	Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	Collision->SetCollisionScale(Texture->GetScale() * RENDERRATIO * 3);
	ItemName = _FileName;
	Type = _Type;
}

void ContentItem::Start()
{
	Renderer = CreateRenderer(RenderOrder::PlayOver);
	Collision = CreateCollision(CollisionOrder::Item);
	if (nullptr == GameEngineSound::FindSound("coin.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("coin.wav"));
	}
}

void ContentItem::Update(float _Delta)
{
	if (GetLiveTime() >= 1.0f && false == ContentInventory::MainInventory->IsFull(this))
	{
		float4 Dir = Player::MainPlayer->GetPos() - GetPos();
		if (true == Collision->CollisionCheck(Player::MainPlayer->GetBodyCollision(), CollisionType::Rect, CollisionType::Rect))
		{
			Dir.Normalize();
			AddPos(Dir * _Delta * 200.0f);
		}

		if (abs(GetPos().iX() - Player::MainPlayer->GetPos().iX()) < 2 * RENDERRATIO && abs(GetPos().iY() - Player::MainPlayer->GetPos().iY()) < 2 * RENDERRATIO)
		{
			ContentInventory::MainInventory->PushItem(this);
			EffectPlayer = GameEngineSound::SoundPlay("coin.wav");
			EffectPlayer.SetVolume(0.2f);
		}
	}
}
void ContentItem::LevelStart()
{
}
void ContentItem::LevelEnd()
{
}