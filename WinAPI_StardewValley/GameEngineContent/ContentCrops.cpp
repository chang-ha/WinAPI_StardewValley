#include <GameEngineBase/GameEngineRandom.h>

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentCrops.h"
#include "GlobalValue.h"
#include "ContentsEnum.h"
#include "ContentInventory.h"
#include "ContentItem.h"

ContentCrops::ContentCrops()
{

}

ContentCrops::~ContentCrops()
{

}

void ContentCrops::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Crops_Parsnip.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Crops\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Crops_Parsnip.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Crops_Parsnip.bmp", 6, 1);
	}
	GrowStep = GameEngineRandom::MainRandom.RandomInt(0, 1);

	CropsRenderer = CreateRenderer(RenderOrder::PlayBelow);
	CropsRenderer->SetSprite("Crops_Parsnip.bmp", GrowStep);
	CropsRenderer->SetRenderPos({TILESIZE.hX() * RENDERRATIO, 0});
	CropsRenderer->SetRenderScale({TILESIZE.X * RENDERRATIO, TILESIZE.Y * 2 * RENDERRATIO});

	CropsCollision = CreateCollision(CollisionOrder::Crops);
	CropsCollision->SetCollisionScale(TILESIZE * RENDERRATIO);
	CropsCollision->SetCollisionPos(TILESIZE.Half() * RENDERRATIO);
} 

void ContentCrops::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('O'))
	{
		Grow();
	}
}

void ContentCrops::Grow()
{
	if (MaxGrowStep <= GrowStep)
	{
		return;
	}

	if (2 > GrowStep)
	{
		GrowStep = 3;
	}
	else
	{
		++GrowStep;
	}

	CropsRenderer->SetSprite("Crops_Parsnip.bmp", GrowStep);
}

bool ContentCrops::IsGrownUp()
{
	if (GrowStep < MaxGrowStep)
	{
		return false;
	}
	return true;
}

void ContentCrops::Harvest()
{
	ContentItem* Crops = GetLevel()->CreateActor<ContentItem>();
	Crops->Init("Parsnip.bmp", ItemType::Crops);

	if (false == IsGrownUp())
	{
		return;
	}

	if (true == ContentInventory::MainInventory->IsFull(Crops))
	{
		Crops->Death();
	}
	else if (false == ContentInventory::MainInventory->IsFull(Crops))
	{
		ContentInventory::MainInventory->PushItem(Crops);
		this->Death();
	}
}


