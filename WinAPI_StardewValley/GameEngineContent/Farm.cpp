#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "Farm.h"
#include "BackGround.h"
#include "Player.h"
#include "FarmHouse.h"
#include "BusStation.h"

Farm::Farm()
{

}

Farm::~Farm()
{

}

void Farm::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
	Farmer = Player::MainPlayer;
	Farmer->SetPlayLevel(this);
	if (nullptr == Farmer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}
	Farmer->SetCollisionTexture("Collision_Farm.bmp");
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	// _PrevLevel == FarmHouse
	if (nullptr != dynamic_cast<FarmHouse*>(_PrevLevel))
	{
		Farmer->SetPos({ 2365, -700 });
		Farmer->SetDir(PlayerDir::Down);
		GetMainCamera()->SetPos(Farmer->GetPos() - WinScale.Half());
	}

	// _PrveLevel == BusStation
	if (nullptr != dynamic_cast<BusStation*>(_PrevLevel))
	{
		Farmer->SetPos({ 3325, -575 });
		Farmer->SetDir(PlayerDir::Left);
		GetMainCamera()->SetPos({Back->GetRenderScale().Half().X - WinScale.Half().X, -1100});
	}

}

void Farm::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	// _NextLevel == FarmHouse
	if (nullptr != dynamic_cast<FarmHouse*>(_NextLevel))
	{
		FarmHouse* NextLevel = dynamic_cast<FarmHouse*>(_NextLevel);
		NextLevel->BGMPlayer = this->BGMPlayer;
	}

	// _NextLevel == BusStation
	if (nullptr != dynamic_cast<BusStation*>(_NextLevel))
	{
		BusStation* NextLevel = dynamic_cast<BusStation*>(_NextLevel);
		NextLevel->BGMPlayer = this->BGMPlayer;
	}
	Farmer->EffectPlayer.Stop();
}


void Farm::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Farm.bmp"))
	{
		Back = CreateActor<BackGround>(0);
		Back->Init("Farm.bmp", "Collision_Farm.bmp");
		Back->Renderer->SetTexture("Farm.bmp");
		Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
		Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetRenderScale(Back->GetScale() * RENDERRATIO);

		Back->CollisionRenderer->SetTexture("Collision_Farm.bmp");
		Back->CollisionRenderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	}
}
void Farm::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
	if (true == GameEngineInput::IsDown('1'))
	{
		GameEngineCore::ChangeLevel("FarmHouse");
	}
	if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("BusStation");
	}

	if (true == GameEngineInput::IsDown('P'))
	{
		Back->SwitchRender();
	}
}