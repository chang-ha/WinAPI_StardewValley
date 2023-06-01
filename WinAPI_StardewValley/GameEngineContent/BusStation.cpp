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

BusStation::BusStation()
{

}

BusStation::~BusStation()
{

}


void BusStation::LevelStart(GameEngineLevel* _PrevLevel)
{
	Farmer = Player::MainPlayer;
	Farmer->SetPlayLevel(this);
	if (nullptr == Farmer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}
	Farmer->SetCollisionTexture("Collision_BusStation.bmp");

	// _PrevLevel == Farm
	if (nullptr != dynamic_cast<Farm*>(_PrevLevel))
	{
		Farmer->SetPos({ 50, Back->GetRenderScale().Y * 0.78f});
		Farmer->SetDir(PlayerDir::Right);
		GetMainCamera()->SetPos({ 0, Back->GetRenderScale().Y - WinScale.Y});
	}

	if (nullptr != dynamic_cast<PelicanTown*>(_PrevLevel))
	{
		// BGMPlayer = GameEngineSound::SoundPlay("Farm.mp3");
		Farmer->SetPos({ Back->GetRenderScale().X - 50, Back->GetRenderScale().Y * 0.78f });
		Farmer->SetDir(PlayerDir::Left);
		GetMainCamera()->SetPos({ Back->GetRenderScale().X - WinScale.X, Back->GetRenderScale().Y - WinScale.Y });
	}
	ContentLevel::LevelStart(_PrevLevel);
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
	if (false == ResourcesManager::GetInst().IsLoadTexture("BusStation.bmp"))
	{
		Back = CreateActor<BackGround>(0);
		Back->Init("BusStation.bmp", "Collision_BusStation.bmp");
		Back->Renderer->SetTexture("BusStation.bmp");
		Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetPos(GetRenderScale().Half());

		Back->CollisionRenderer->SetTexture("Collision_BusStation.bmp");
		Back->CollisionRenderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	}
}

void BusStation::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
	if (true == GameEngineInput::IsDown('1'))
	{
		GameEngineCore::ChangeLevel("Farm");
	}
	if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("PelicanTown");
	}

	if (true == GameEngineInput::IsDown('P'))
	{
		Back->SwitchRender();
	}
}