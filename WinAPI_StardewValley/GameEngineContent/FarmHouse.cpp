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
#include "ContentUIManager.h"

FarmHouse::FarmHouse()
{

}

FarmHouse::~FarmHouse()
{

}

void FarmHouse::LevelStart(GameEngineLevel* _PrevLevel)
{
	// Farmer = Player::MainPlayer;
	Farmer->SetPlayLevel(this);
	if (nullptr == Farmer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}
	Farmer->SetCollisionTexture("Collision_farmhouse.bmp");
	Farmer->SetPos({ 1010,630 });
	Farmer->SetDir(PlayerDir::Right);
}

void FarmHouse::LevelEnd(GameEngineLevel* _NextLevel)
{
}

void FarmHouse::Start()
{
	if (nullptr == Back)
	{
		Back = CreateActor<BackGround>(0);														  
		Back->Init("farmhouse.bmp", "Collision_farmhouse.bmp");
		Back->Renderer->SetTexture("farmhouse.bmp");
		Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
		Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetRenderScale(Back->GetScale() * RENDERRATIO);


		Back->CollisionRenderer->SetTexture("Collision_farmhouse.bmp");
		Back->CollisionRenderer->SetRenderScale(Back->GetScale() * RENDERRATIO);

		Farmer = CreateActor<Player>(1);

		PlayOver* Over = CreateActor<PlayOver>();
		Over->Init("farmhouse_bed.bmp");
		Over->Renderer->SetTexture("farmhouse_bed.bmp");
		Over->Renderer->SetRenderScale(Over->GetScale() * RENDERRATIO);
		Over->SetRenderScale(Over->GetScale() * RENDERRATIO);
		Over->SetPos({ 1024,650 });
	}
	CreateActor<ContentUIManager>(0);
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

	if (true == GameEngineInput::IsDown('P'))
	{
		Back->SwitchRender();
	}
}