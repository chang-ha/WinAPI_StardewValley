#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCamera.h>

#include "Player.h"
#include "PelicanTown.h"
#include "BackGround.h"

PelicanTown::PelicanTown()
{

}

PelicanTown::~PelicanTown()
{

}

void PelicanTown::LevelStart(GameEngineLevel* _PrevLevel)
{
	Farmer = Player::MainPlayer;
	Farmer->SetContentLevel(this);
	if (nullptr == Farmer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	Farmer->SetPos({ GameEngineWindow::MainWindow.GetScale().Half().X - Back->GetScale().Half().X * 4 + 50, 400 });
	GetMainCamera()->SetPos({GameEngineWindow::MainWindow.GetScale().Half().X - Back->GetScale().Half().X * 4, 0});
}

void PelicanTown::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void PelicanTown::Start()
{
	Back = CreateActor<BackGround>();
	Back->Init("Town.bmp");
	Back->Renderer->SetTexture("Town.bmp");
	Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
	Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	Back->SetRenderScale(Back->GetScale() * RENDERRATIO);
	CreateActor<Player>();
}
void PelicanTown::Update(float _Delta)
{

}
void PelicanTown::Render()
{

}
void PelicanTown::Release()
{

}