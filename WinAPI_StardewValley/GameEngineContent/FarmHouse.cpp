#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCore.h>

#include "FarmHouse.h"
#include "BackGround.h"
#include "Player.h"
#include "PlayOver.h"

FarmHouse::FarmHouse()
{

}

FarmHouse::~FarmHouse()
{

}

void FarmHouse::LevelStart(GameEngineLevel* _PrevLevel)
{
	Farmer = Player::MainPlayer;
	Farmer->SetContentLevel(this);
	if (nullptr == Farmer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}

	Farmer->SetPos({ 1040,630 });
	// float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	// GetMainCamera()->SetPos({});
}

void FarmHouse::LevelEnd(GameEngineLevel* _NextLevel)
{
}

void FarmHouse::Start()
{
	if (nullptr == Back)
	{
		Back = CreateActor<BackGround>();
		Back->Init("farmhouse.bmp");
		Back->Renderer->SetTexture("farmhouse.bmp");
		Back->SetRenderScale(Back->GetScale());
		Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
		
		CreateActor<Player>();

		PlayOver* Over = CreateActor<PlayOver>();
		Over->Init("farmhouse_bed.bmp");
		Over->Renderer->SetTexture("farmhouse_bed.bmp");
		Over->SetPos({ 1056.5,678 });
	}
}
void FarmHouse::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('1'))
	{
		GameEngineCore::ChangeLevel("TitleScreen");
	}
	if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("Farm");
	}
}
void FarmHouse::Render()
{

}
void FarmHouse::Release()
{

}