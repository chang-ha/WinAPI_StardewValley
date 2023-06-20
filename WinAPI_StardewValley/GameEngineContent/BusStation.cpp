#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "Player.h"
#include "BusStation.h"
#include "BackGround.h"
#include "Farm.h"
#include "PelicanTown.h"
#include "ContentsEnum.h"
#include "PlayOver.h"

BusStation::BusStation()
{

}

BusStation::~BusStation()
{

}


void BusStation::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
	Player::MainPlayer->SetCollisionTexture("Collision_BusStation.bmp");

	// _PrevLevel == Farm
	if (nullptr != dynamic_cast<Farm*>(_PrevLevel))
	{
		Player::MainPlayer->SetPos({ 50, Back->GetRenderScale().Y * 0.78f});
		Player::MainPlayer->SetDir(PlayerDir::Right);
		GetMainCamera()->SetPos({ 0, Back->GetRenderScale().Y - GlobalValue::WinScale.Y});
	}

	if (nullptr != dynamic_cast<PelicanTown*>(_PrevLevel))
	{
		// BGMPlayer = GameEngineSound::SoundPlay("Farm.mp3");
		Player::MainPlayer->SetPos({ Back->GetRenderScale().X - 50, Back->GetRenderScale().Y * 0.78f });
		Player::MainPlayer->SetDir(PlayerDir::Left);
		GetMainCamera()->SetPos({ Back->GetRenderScale().X - GlobalValue::WinScale.X, Back->GetRenderScale().Y - GlobalValue::WinScale.Y });
	}
}

void BusStation::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	// _NextLevel == Farm
	if (nullptr != dynamic_cast<Farm*>(_NextLevel))
	{
		Farm* NextLevel = dynamic_cast<Farm*>(_NextLevel);
		NextLevel->BGMPlayer = this->BGMPlayer;
	}

	// _NextLevel == PelicanTown
	if (nullptr != dynamic_cast<PelicanTown*>(_NextLevel))
	{
		PelicanTown* NextLevel = dynamic_cast<PelicanTown*>(_NextLevel);
		NextLevel->BGMPlayer = this->BGMPlayer;
	}
}

void BusStation::Start()
{
	PrevLevel = "Farm";
	NextLevel = "PelicanTown";
	if (false == ResourcesManager::GetInst().IsLoadTexture("BusStation.bmp"))
	{
		Back = CreateActor<BackGround>(UpdateOrder::Map);
		Back->Init("BusStation.bmp", "Collision_BusStation.bmp");
		Back->Renderer->SetTexture("BusStation.bmp");
		Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetPos(GetRenderScale().Half());

		Back->CollisionRenderer->SetTexture("Collision_BusStation.bmp");
		Back->CollisionRenderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	}
	// Detail
	PlayOver* Over = CreateActor<PlayOver>(UpdateOrder::Map);
	Over->Init("Detail_BusStation.bmp");
	Over->SetPos(GetRenderScale().Half());
}

void BusStation::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}