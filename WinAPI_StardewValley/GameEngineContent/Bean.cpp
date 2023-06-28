#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Bean.h"
#include "ContentItem.h"
#include "ContentInventory.h"
#include "Player.h"

Bean::Bean()
{

}

Bean::~Bean()
{

}

void Bean::Start()
{
	ContentCrops::Start();
	CropsName = "Bean.bmp";
	if (false == ResourcesManager::GetInst().IsLoadTexture("Crops_Bean.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Crops\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Crops_Bean.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Crops_Bean.bmp", 8, 1);
	}
	MaxGrowStep = 6;
	CropsRenderer->SetSprite("Crops_Bean.bmp", GrowStep);
}

void Bean::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_F5))
	{
		Grow();
	}

	if (false == IsHarvest)
	{
		return;
	}

	if (true == Player::MainPlayer->ArmRenderer->IsAnimationEnd())
	{
		//this->Off();
		//CropsCollision->Off();
	}
	Harvesting();
}

bool Bean::Harvest()
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
		IsHarvest = true;
		GrowStep = 7;
		CropsRenderer->SetSprite("Crops_" + CropsName, GrowStep);
		return true;
	}
	return false;
}

void Bean::Grow()
{
	if (7 == GrowStep)
	{
		GrowStep = 5;
	}
	ContentCrops::Grow();
}
