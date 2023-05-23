﻿#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCore.h>
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
	// Farmer = Player::MainPlayer;
	Farmer->SetPlayLevel(this);
	if (nullptr == Farmer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}
	Farmer->SetCollisionTexture("Collision_Town.bmp");
	Farmer->SetPos({ GameEngineWindow::MainWindow.GetScale().Half().X - Back->GetRenderScale().Half().X + 50, 400});
	GetMainCamera()->SetPos({GameEngineWindow::MainWindow.GetScale().Half().X - Back->GetRenderScale().Half().X, 0});
}

void PelicanTown::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void PelicanTown::Start()
{
	Back = CreateActor<BackGround>(0);
	Back->Init("Town.bmp", "Collision_Town.bmp");
	Back->Renderer->SetTexture("Town.bmp");
	Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
	Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	Back->SetRenderScale(Back->GetScale() * RENDERRATIO);
	
	Back->CollisionRenderer->SetTexture("Collision_Town.bmp");
	Back->CollisionRenderer->SetRenderScale(Back->GetScale() * RENDERRATIO);

	Farmer = CreateActor<Player>(1);
}
void PelicanTown::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('1'))
	{
		GameEngineCore::ChangeLevel("BusStation");
	}
	else if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("Beach");
	}


	if (true == GameEngineInput::IsDown('P'))
	{
		Back->SwitchRender();
	}
}
void PelicanTown::Render()
{

}
void PelicanTown::Release()
{

}