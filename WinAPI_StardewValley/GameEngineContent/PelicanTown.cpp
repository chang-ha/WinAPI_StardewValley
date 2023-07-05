#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>

#include "Player.h"
#include "PelicanTown.h"
#include "BackGround.h"
#include "BusStation.h"
#include "ContentsEnum.h"
#include "Beach.h"
#include "GeneralStore.h"
#include "PlayOver.h"
#include "ContentBuilding.h"

PelicanTown::PelicanTown()
{

}

PelicanTown::~PelicanTown()
{

}

void PelicanTown::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	GetMainCamera()->SetYSort(RenderOrder::Play, true);

	Player::MainPlayer->SetCollisionTexture("Collision_Town.bmp");

	// _PrevLevel == BusStation
	if (nullptr != dynamic_cast<BusStation*>(_PrevLevel))
	{
		Player::MainPlayer->SetPos({ 50, Back->GetRenderScale().Y * 0.5f });
		GetMainCamera()->SetPos({ 0, Back->GetRenderScale().Y * 0.5f - GlobalValue::WinScale.Half().Y});
		Player::MainPlayer->SetDir(PlayerDir::Right);
	}

	// _PrevLevel == Beach
	if (nullptr != dynamic_cast<Beach*>(_PrevLevel))
	{
		Player::MainPlayer->SetPos({ Back->GetRenderScale().X * 0.455f, Back->GetRenderScale().Y - 50});
		GetMainCamera()->SetPos({ Player::MainPlayer->GetPos().X - GlobalValue::WinScale.Half().X , Back->GetRenderScale().Y - GlobalValue::WinScale.Y});
		Player::MainPlayer->SetDir(PlayerDir::Up);
		BGMPlayer = GameEngineSound::SoundPlay("Town.mp3", 10000);
	}

	// _PrevLevel == GeneralStore
	if (nullptr != dynamic_cast<GeneralStore*>(_PrevLevel))
	{
		Player::MainPlayer->SetPos({Back->GetRenderScale().X * 0.362f, Back->GetRenderScale().X * 0.475f });
		GetMainCamera()->SetPos(Player::MainPlayer->GetPos() - GlobalValue::WinScale.Half());
		Player::MainPlayer->SetDir(PlayerDir::Down);
	}
}


void PelicanTown::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

	// _NextLevel == BusStation
	if (nullptr != dynamic_cast<BusStation*>(_NextLevel))
	{
		BusStation* NextLevel = dynamic_cast<BusStation*>(_NextLevel);
		NextLevel->BGMPlayer = this->BGMPlayer;
	}

	// _NextLevel == Beach
	if (nullptr != dynamic_cast<Beach*>(_NextLevel))
	{
		BGMPlayer.Stop();
	}
}

void PelicanTown::Start()
{
	PrevLevel = "BusStation";
	NextLevel = "Beach";
	Building = "GeneralStore";
	if (false == ResourcesManager::GetInst().IsLoadTexture("Town.bmp"))
	{
		Back = CreateActor<BackGround>(UpdateOrder::Map);
		Back->Init("Town.bmp", "Collision_Town.bmp", RENDERRATIO);
		Back->SetPos(GetRenderScale().Half());
	}

	if (nullptr == GameEngineSound::FindSound("Town.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\BGM");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Town.mp3"));
	}

	// Detail
	ContentBuilding* Building = CreateActor<ContentBuilding>();
	Building->Init("GeneralShop.bmp");
	Building->SetPos({ Back->GetRenderScale().X * 0.337f, Back->GetRenderScale().Y * 0.472f });

	PlayOver* Over = CreateActor<PlayOver>();
	Over->Init("Fence.bmp", true);
	Over->SetPos({ Back->GetRenderScale().X * 0.068f, Back->GetRenderScale().Y * 0.5088f });

	Over = CreateActor<PlayOver>();
	Over->Init("Fence2.bmp", true);
	Over->SetPos({ Back->GetRenderScale().X * 0.1346f, Back->GetRenderScale().Y * 0.5088f });

	Over = CreateActor<PlayOver>();
	Over->Init("Tree_Type1.bmp");
	Over->SetPos({ 45, Back->GetRenderScale().Y * 0.531f });

	Over = CreateActor<PlayOver>();
	Over->Init("MiniTree_Type1.bmp", true);
	Over->SetPos({ Back->GetRenderScale().X * 0.105f, Back->GetRenderScale().Y * 0.523f });

	Over = CreateActor<PlayOver>();
	Over->Init("MiniTree_Type1.bmp", true);
	Over->SetPos({ Back->GetRenderScale().X * 0.19f, Back->GetRenderScale().Y * 0.54f });

	Over = CreateActor<PlayOver>();
	Over->Init("Tree_Type1.bmp", true);
	Over->SetPos({ Back->GetRenderScale().X * 0.058f, Back->GetRenderScale().Y * 0.558f });
	Over->GetRenderer()->SetYPivot(64);

	Over = CreateActor<PlayOver>();
	Over->Init("StreetLamp.bmp", true);
	Over->SetPos({ Back->GetRenderScale().X * 0.2042f, Back->GetRenderScale().Y * 0.4722f });
	Over->GetRenderer()->SetYPivot(32);

	Over = CreateActor<PlayOver>();
	Over->Init("Tree_Type1.bmp", true);
	Over->SetPos({ Back->GetRenderScale().X * 0.258f, Back->GetRenderScale().Y * 0.476f });
	Over->GetRenderer()->SetYPivot(64);

	Over = CreateActor<PlayOver>();
	Over->Init("StreetLamp.bmp", true);
	Over->SetPos({ Back->GetRenderScale().X * 0.2042f, Back->GetRenderScale().Y * 0.545f });
	Over->GetRenderer()->SetYPivot(32);

	Over = CreateActor<PlayOver>();
	Over->Init("StreetLamp.bmp", true);
	Over->SetPos({ Back->GetRenderScale().X * 0.4375f, Back->GetRenderScale().Y * 0.9088f });
	Over->GetRenderer()->SetYPivot(32);

	Over = CreateActor<PlayOver>();
	Over->Init("StreetLamp.bmp", true);
	Over->SetPos({ Back->GetRenderScale().X * 0.4708f, Back->GetRenderScale().Y * 0.9088f });
	Over->GetRenderer()->SetYPivot(32);
}

void PelicanTown::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}