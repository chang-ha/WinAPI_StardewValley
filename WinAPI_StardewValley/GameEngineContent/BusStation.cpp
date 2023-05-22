#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Player.h"
#include "BusStation.h"
#include "BackGround.h"

BusStation::BusStation()
{

}

BusStation::~BusStation()
{

}


void BusStation::LevelStart(GameEngineLevel* _PrevLevel)
{
	// Farmer = Player::MainPlayer;
	Farmer->SetPlayLevel(this);
	if (nullptr == Farmer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}
	Farmer->SetPos({ -200, 1030 });
	GetMainCamera()->SetPos({ GameEngineWindow::MainWindow.GetScale().Half().X - Back->GetRenderScale().Half().X, 500 });
}

void BusStation::LevelEnd(GameEngineLevel* _NextLevel)
{

}


void BusStation::Start()
{
	Back = CreateActor<BackGround>();
	Back->Init("BusStation.bmp");
	Back->Renderer->SetTexture("BusStation.bmp");
	Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
	Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	Back->SetRenderScale(Back->GetScale() * RENDERRATIO);
	Farmer = CreateActor<Player>();
}
void BusStation::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('1'))
	{
		GameEngineCore::ChangeLevel("Farm");
	}
	if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("PelicanTown");
	}
}
void BusStation::Render()
{

}
void BusStation::Release()
{

}