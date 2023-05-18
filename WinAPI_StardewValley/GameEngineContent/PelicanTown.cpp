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
	if (nullptr == Farmer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}
	Farmer->SetPos({ -2600, 450 });

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	GetMainCamera()->SetPos(Farmer->GetPos() - WinScale.Half());
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
	Back->Renderer->SetRenderScale(Back->GetScale() * 3.7f); // *3.7
	CreateActor<Player>();
	Farmer = Player::MainPlayer;
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