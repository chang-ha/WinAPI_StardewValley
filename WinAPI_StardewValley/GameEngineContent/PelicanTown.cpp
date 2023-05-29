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
#include "Beach.h"

PelicanTown::PelicanTown()
{

}

PelicanTown::~PelicanTown()
{

}

void PelicanTown::LevelStart(GameEngineLevel* _PrevLevel)
{
	// Farmer = Player::MainPlayer;
	Farmer->SetPlayLevel(this);
	if (nullptr == Farmer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}
	Farmer->SetCollisionTexture("Collision_Town.bmp");
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	// _PrevLevel == BusStation
	if (nullptr != dynamic_cast<BusStation*>(_PrevLevel))
	{
		Farmer->SetPos({ WinScale.Half().X - Back->GetRenderScale().Half().X + 50, 400 });
		GetMainCamera()->SetPos({ WinScale.Half().X - Back->GetRenderScale().Half().X, 0 });
		Farmer->SetDir(PlayerDir::Right);
	}

	// _PrevLevel == Beach
	if (nullptr != dynamic_cast<Beach*>(_PrevLevel))
	{
		Farmer->SetPos({ 450, Back->GetRenderScale().Half().Y + WinScale.Half().Y - 50});
		GetMainCamera()->SetPos({-WinScale.Half().X * 0.5f + 75 , Back->GetRenderScale().Half().Y - WinScale.Half().Y});
		Farmer->SetDir(PlayerDir::Up);
		BGMPlayer = GameEngineSound::SoundPlay("Farm.mp3");
	}
}

void PelicanTown::LevelEnd(GameEngineLevel* _NextLevel)
{
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
	if (false == ResourcesManager::GetInst().IsLoadTexture("Town.bmp"))
	{
		Back = CreateActor<BackGround>(0);
		Back->Init("Town.bmp", "Collision_Town.bmp");
		Back->Renderer->SetTexture("Town.bmp");
		Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
		Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetRenderScale(Back->GetScale() * RENDERRATIO);

		Back->CollisionRenderer->SetTexture("Collision_Town.bmp");
		Back->CollisionRenderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	}
	Farmer = CreateActor<Player>(1);


}
void PelicanTown::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('1'))
	{
		GameEngineCore::ChangeLevel("BusStation");
	}
	else if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("Beach");
	}


	if (true == GameEngineInput::IsDown('P'))
	{
		Back->SwitchRender();
	}
}