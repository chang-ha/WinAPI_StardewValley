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

void Farm::LevelEnd(GameEngineLevel* _NextLevel)
{

}


void Farm::Start()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->Init("Farm.bmp");
	Back->Renderer->SetTexture("Farm.bmp");
	Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
	Back->Renderer->SetRenderScale({5032, 4144});
	Farmer = CreateActor<Player>();
	Farmer->SetPos({2350, -550});
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
void Farm::Render()
{

}
void Farm::Release()
{

}