#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Farm.h"
#include "BackGround.h"
#include "Player.h"
Farm::Farm()
{

}

Farm::~Farm()
{

}

void Farm::LevelStart(GameEngineLevel* _PrevLevel)
{
	// Farmer = Player::MainPlayer;
	Farmer->SetPlayLevel(this);
	if (nullptr == Farmer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}
	Farmer->SetPos({ 2465, -700 });
	Farmer->SetDir(PlayerDir::Down);
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	GetMainCamera()->SetPos(Farmer->GetPos() - WinScale.Half());
}

void Farm::LevelEnd(GameEngineLevel* _NextLevel)
{

}


void Farm::Start()
{
	Back = CreateActor<BackGround>(0);
	Back->Init("Farm.bmp");
	Back->Renderer->SetTexture("Farm.bmp");
	Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
	Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	Back->SetRenderScale(Back->GetScale() * RENDERRATIO);
	Farmer = CreateActor<Player>(1);
}
void Farm::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('1'))
	{
		GameEngineCore::ChangeLevel("FarmHouse");
	}
	if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("BusStation");
	}
}