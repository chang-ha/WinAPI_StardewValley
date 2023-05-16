#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Player.h"
#include "Beach.h"
#include "BackGround.h"

Beach::Beach()
{

}

Beach::~Beach()
{

}


void Beach::LevelStart(GameEngineLevel* _PrevLevel)
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

void Beach::LevelEnd(GameEngineLevel* _NextLevel)
{

}


void Beach::Start()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->Init("Beach.bmp");
	Back->Renderer->SetTexture("Beach.bmp");
	Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
	Back->Renderer->SetRenderScale({ 4500, 2841.5 }); // *3.7
	Farmer = CreateActor<Player>();
	Farmer->SetPos({ 900, -850 });
}
void Beach::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('1'))
	{
		GameEngineCore::ChangeLevel("BusStation");
	}
}
void Beach::Render()
{

}
void Beach::Release()
{

}