﻿#define TUTORIALSPEED 20.0f

#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/TileMap.h>

#include "FarmHouse.h"
#include "BackGround.h"
#include "TitleScreen.h"
#include "Player.h"
#include "PlayOver.h"
#include "ContentUIManager.h"
#include "Farm.h"
#include "ContentInventory.h"
#include "ContentsEnum.h"
#include "SleepLevel.h"
#include "GiftBox.h"

FarmHouse::FarmHouse()
{

}

FarmHouse::~FarmHouse()
{

}

void FarmHouse::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	GetMainCamera()->SetYSort(RenderOrder::Play, true);

	Player::MainPlayer->SetCollisionTexture("Collision_farmhouse.bmp");
	Player::MainPlayer->SetPos({ GetRenderScale().X * 0.595f, GetRenderScale().Y * 0.648f});
	Player::MainPlayer->SetDir(PlayerDir::Right);

	ContentInventory::MainInventory->On();
	Player::MainPlayer->SetIsUpdate(true);
	 
	// _PrevLevel == TitleScreen
	if (nullptr != dynamic_cast<TitleScreen*>(_PrevLevel))
	{
		BGMPlayer = GameEngineSound::SoundPlay("Farm.mp3", 10000);

		GiftBox* _GiftBox = CreateActor<GiftBox>();
		_GiftBox->SetPos(UITileMap->IndexToPos(14,11));
		_GiftBox->SetPlayLevel(this);
	}

	// _PrevLevel == Farm
	if (nullptr != dynamic_cast<Farm*>(_PrevLevel))
	{
		Player::MainPlayer->SetPos({ GetRenderScale().X * 0.410f, GetRenderScale().Y * 0.74f });
		Player::MainPlayer->SetDir(PlayerDir::Up);
	}

	// _PrevLevel == SleepLevel
	if (nullptr != dynamic_cast<SleepLevel*>(_PrevLevel))
	{
		BGMPlayer = GameEngineSound::SoundPlay("Farm.mp3", 10000);
		IsSleepValue = true;
	}
}

void FarmHouse::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	if (nullptr != TutorialRenderer)
	{
		TutorialRenderer->Death();
		TutorialRenderer = nullptr;
	}

	// _NexxtLevel == TitleScreen
	if (nullptr != dynamic_cast<TitleScreen*>(_NextLevel))
	{
		BGMPlayer.Stop();
		Player::MainPlayer->OverOff();
		ContentInventory::MainInventory->OverOff();
	}

	// _NextLevel == Farm
	if (nullptr != dynamic_cast<Farm*>(_NextLevel))
	{
		Farm* NextLevel = dynamic_cast<Farm*>(_NextLevel);
		NextLevel->BGMPlayer = this->BGMPlayer;
		Player::MainPlayer->OverOn();
		ContentInventory::MainInventory->OverOn();
	}

	if (nullptr != dynamic_cast<SleepLevel*>(_NextLevel))
	{
		BGMPlayer.Stop();
	}
}

void FarmHouse::Start()
{
	PrevLevel = "TitleScreen";
	NextLevel = "Farm";
	
	// Texture
	if (nullptr == Back)
	{
		// BackGround
		Back = CreateActor<BackGround>(UpdateOrder::Map);														  
		Back->Init("farmhouse.bmp", "Collision_farmhouse.bmp", RENDERRATIO);
		Back->SetPos(GetRenderScale().Half());

		// Player
		Player::MainPlayer = CreateActor<Player>(UpdateOrder::Player);
		ContentInventory::MainInventory = CreateActor<ContentInventory>(UpdateOrder::Inventory);

		// Detail
		PlayOver* Over = CreateActor<PlayOver>(UpdateOrder::Map);
		Over->Init("Detail_Bed.bmp");
		Over->SetPos({ GetRenderScale().X * 0.607f, GetRenderScale().Y * 0.66f });

		Over = CreateActor<PlayOver>(UpdateOrder::Map);
		Over->Init("Detail_farmhouse.bmp");
		Over->SetPos(GlobalValue::WinScale.Half());

		BedDie = CreateActor<PlayOver>(UpdateOrder::Map);
		BedDie->Init("Detail_BedDie.bmp", true);
		BedDie->SetPos({ GetRenderScale().X * 0.607f, GetRenderScale().Y * 0.60f });

		TutorialRenderer = CreateActor<PlayOver>(UpdateOrder::Map);
		TutorialRenderer->Init("Tutorial.bmp");
		TutorialRenderer->SetPos({ -42 * RENDERRATIO, GlobalValue::WinScale.hY()});
	}

	// Sound Load
	if (nullptr == GameEngineSound::FindSound("Farm.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\BGM");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Farm.mp3"));
	}
}

void FarmHouse::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	if (nullptr != TutorialRenderer)
	{
		if (42 * RENDERRATIO == TutorialRenderer->GetPos().X)
		{
			return;
		}

		TutorialRenderer->AddPos(float4::RIGHT * RENDERRATIO * TUTORIALSPEED * _Delta);
		if (42 * RENDERRATIO <= TutorialRenderer->GetPos().X)
		{
			TutorialRenderer->SetPos({ 42 * RENDERRATIO, GlobalValue::WinScale.hY() });
		}
	}
}