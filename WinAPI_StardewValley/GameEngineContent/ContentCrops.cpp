#include <GameEngineBase/GameEngineRandom.h>

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentCrops.h"
#include "GlobalValue.h"
#include "ContentsEnum.h"
#include "ContentInventory.h"
#include "ContentItem.h"
#include "Farm.h"

ContentCrops::ContentCrops()
{

}

ContentCrops::~ContentCrops()
{

}

void ContentCrops::Start()
{
	GrowStep = GameEngineRandom::MainRandom.RandomInt(0, 1);

	CropsRenderer = CreateRenderer(RenderOrder::PlayBelow);
	CropsRenderer->SetRenderPos({TILESIZE.hX() * RENDERRATIO, 0});
	CropsRenderer->SetRenderScale({TILESIZE.X * RENDERRATIO, TILESIZE.Y * 2 * RENDERRATIO});

	CropsCollision = CreateCollision(CollisionOrder::Crops);
	CropsCollision->SetCollisionScale(TILESIZE * RENDERRATIO);
	CropsCollision->SetCollisionPos(TILESIZE.Half() * RENDERRATIO);

	if (nullptr == GameEngineSound::FindSound("harvest.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("harvest.wav"));
	}
} 

void ContentCrops::Update(float _Delta)
{
}

void ContentCrops::Grow()
{
	if (MaxGrowStep <= GrowStep)
	{
		return;
	}

	if (2 > GrowStep)
	{
		GrowStep = 2;
	}
	else
	{
		++GrowStep;
	}

	CropsRenderer->SetSprite("Crops_" + CropsName, GrowStep);
}

bool ContentCrops::IsGrownUp()
{
	if (GrowStep < MaxGrowStep)
	{
		return false;
	}
	return true;
}

bool ContentCrops::Harvest()
{
	if (false == IsGrownUp())
	{
		return false;
	}

	ContentItem* Crops = GetLevel()->CreateActor<ContentItem>();
	Crops->Init(CropsName, ItemType::Crops);

	if (true == ContentInventory::MainInventory->IsFull(Crops))
	{
		Crops->Death();
	}
	else if (false == ContentInventory::MainInventory->IsFull(Crops))
	{
		ContentInventory::MainInventory->PushItem(Crops);
		EffectPlayer = GameEngineSound::SoundPlay("harvest.wav");
		this->Off();
		return true;
	}
	return false;
}


