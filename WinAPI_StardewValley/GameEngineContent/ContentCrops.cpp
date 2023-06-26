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
#include "Player.h"

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
	CropsCollision->SetCollisionScale(TILESIZE);
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
	// Cheat Code
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
		this->Off();
		CropsCollision->Off();
	}

	CropsRenderer->SetTexture(CropsName);
	CropsRenderer->SetRenderScale(TILESIZE * RENDERRATIO);
	switch (Player::MainPlayer->GetDir())
	{
	case Null:
		break;
	case Up:
		switch (Player::MainPlayer->ArmRenderer->GetCurFrame())
		{
		case 0:
			SetPos(Player::MainPlayer->GetPos() + float4{ 0 - TILESIZE.hX(),5 } * RENDERRATIO);
			break;
		case 1:
			SetPos(Player::MainPlayer->GetPos() + float4{ 0 - TILESIZE.hX(),4 } *RENDERRATIO);
			break;
		case 2:
			SetPos(Player::MainPlayer->GetPos() + float4{ 0 - TILESIZE.hX(),-17 } *RENDERRATIO);
			break;
		case 3:
			SetPos(Player::MainPlayer->GetPos() + float4{ 0 - TILESIZE.hX(),-16 } *RENDERRATIO);
			break;
		default:
			break;
		}
		break;
	case Down:
		switch (Player::MainPlayer->ArmRenderer->GetCurFrame())
		{
		case 0:
			CropsRenderer->SetOrder(static_cast<int>(RenderOrder::PlayOver));
			SetPos(Player::MainPlayer->GetPos() + float4{ 0 - TILESIZE.hX(), 8 } *RENDERRATIO);
			break;
		case 1:
			SetPos(Player::MainPlayer->GetPos() + float4{ 0 - TILESIZE.hX(), 7 } *RENDERRATIO);
			break;
		case 2:
			SetPos(Player::MainPlayer->GetPos() + float4{ 0 - TILESIZE.hX(), -17 } *RENDERRATIO);
			break;
		case 3:
			SetPos(Player::MainPlayer->GetPos() + float4{ 0 - TILESIZE.hX(), -16 } *RENDERRATIO);
			break;
		default:
			break;
		}
		break;
	case Right:
		switch (Player::MainPlayer->ArmRenderer->GetCurFrame())
		{
		case 0:
			CropsRenderer->SetOrder(static_cast<int>(RenderOrder::PlayOver));
			SetPos(Player::MainPlayer->GetPos() + float4{ 7 - TILESIZE.hX(), 1 } *RENDERRATIO);
			break;
		case 1:
			SetPos(Player::MainPlayer->GetPos() + float4{ 5 - TILESIZE.hX(), -4 } *RENDERRATIO);
			break;
		case 2:
			SetPos(Player::MainPlayer->GetPos() + float4{ 0 - TILESIZE.hX(), - 17 } *RENDERRATIO);
			break;
		case 3:
			SetPos(Player::MainPlayer->GetPos() + float4{ 0 - TILESIZE.hX(), -16 } *RENDERRATIO);
			break;
		default:
			break;
		}
		break;
	case Left:
		switch (Player::MainPlayer->ArmRenderer->GetCurFrame())
		{
		case 0:
			CropsRenderer->SetOrder(static_cast<int>(RenderOrder::PlayOver));
			SetPos(Player::MainPlayer->GetPos() + float4{ -7 - TILESIZE.hX(),1 } *RENDERRATIO);
			break;
		case 1:
			SetPos(Player::MainPlayer->GetPos() + float4{ -5 - TILESIZE.hX(),-4 } *RENDERRATIO);
			break;
		case 2:
			SetPos(Player::MainPlayer->GetPos() + float4{ 0 - TILESIZE.hX(), -17 } *RENDERRATIO);
			break;
		case 3:
			SetPos(Player::MainPlayer->GetPos() + float4{ 0 - TILESIZE.hX(), -16 } *RENDERRATIO);
			break;
		default:
			break;
		}
		break;
	default:
		break;
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
		IsHarvest = true;
		return true;
	}
	return false;
}


