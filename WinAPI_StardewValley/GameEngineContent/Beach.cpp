#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Player.h"
#include "Beach.h"
#include "BackGround.h"
#include "ContentLevel.h"

Beach::Beach()
{

}

Beach::~Beach()
{

}


void Beach::LevelStart(GameEngineLevel* _PrevLevel)
{
	Farmer = Player::MainPlayer;
	Farmer->SetPlayLevel(this);
	if (nullptr == Farmer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}
	Farmer->SetPos({ 0, -900 });
	Farmer->SetDir(PlayerDir::Down);
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	GetMainCamera()->SetPos({-WinScale.Half().X, WinScale.Half().Y - Back->GetRenderScale().Half().Y});
}

void Beach::LevelEnd(GameEngineLevel* _NextLevel)
{

}


void Beach::Start()
{
	Back = CreateActor<BackGround>(0);
	Back->Init("Beach.bmp");
	Back->Renderer->SetTexture("Beach.bmp");
	Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
	Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	Back->SetRenderScale(Back->GetScale() * RENDERRATIO);

	Farmer = CreateActor<Player>(1);
}
void Beach::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('1'))
	{
		GameEngineCore::ChangeLevel("PelicanTown");
	}
}