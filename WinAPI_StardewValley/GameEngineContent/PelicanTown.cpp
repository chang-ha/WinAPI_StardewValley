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

PelicanTown::PelicanTown()
{

}

PelicanTown::~PelicanTown()
{

}

void PelicanTown::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
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
		Back->Init("Town.bmp", "Collision_Town.bmp");
		Back->Renderer->SetTexture("Town.bmp");
		Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetPos(GetRenderScale().Half());

		Back->CollisionRenderer->SetTexture("Collision_Town.bmp");
		Back->CollisionRenderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	}

	if (nullptr == GameEngineSound::FindSound("Town.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\BGM");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Town.mp3"));
	}
}
void PelicanTown::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}