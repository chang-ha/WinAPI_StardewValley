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
	if (nullptr == Farmer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	//LevelPlayer->SetPos(WinScale.Half());
	// 0 0
	// x y
	// GetMainCamera()->SetPos(Farmer->GetPos() - WinScale.Half());
	GetMainCamera()->SetPos(Farmer->GetPos() - WinScale.Half());

}

void BusStation::LevelEnd(GameEngineLevel* _NextLevel)
{

}


void BusStation::Start()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->Init("BusStation.bmp");
	Back->Renderer->SetTexture("BusStation.bmp");
	Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
	Back->Renderer->SetRenderScale({ 2072, 1894.5 }); // *3.7
	Farmer = CreateActor<Player>();
	Farmer->SetPos({ -200, 1030 });
}
void BusStation::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('1'))
	{
		GameEngineCore::ChangeLevel("Farm");
	}
	if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("Beach");
	}
}
void BusStation::Render()
{

}
void BusStation::Release()
{

}