#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

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
	Farmer->SetCollisionTexture("Collision_Beach.bmp");
	Farmer->SetPos({ 0, -900 });
	Farmer->SetDir(PlayerDir::Down);
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	GetMainCamera()->SetPos({-WinScale.Half().X, WinScale.Half().Y - Back->GetRenderScale().Half().Y});

	BGMPlayer = GameEngineSound::SoundPlay("ocean.wav");
	BGMPlayer.SetVolume(0.5f);
}

void Beach::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}


void Beach::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Beach.bmp"))
	{
		Back = CreateActor<BackGround>(0);
		Back->Init("Beach.bmp", "Collision_Beach.bmp");
		Back->Renderer->SetTexture("Beach.bmp");
		Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
		Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetRenderScale(Back->GetScale() * RENDERRATIO);

		Back->CollisionRenderer->SetTexture("Collision_Beach.bmp");
		Back->CollisionRenderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	}

	Farmer = CreateActor<Player>(1);
	if (nullptr == GameEngineSound::FindSound("ocean.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\BGM");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("ocean.wav"));
	}
}
void Beach::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('1'))
	{
		GameEngineCore::ChangeLevel("PelicanTown");
	}

	if (true == GameEngineInput::IsDown('P'))
	{
		Back->SwitchRender();
	}
}