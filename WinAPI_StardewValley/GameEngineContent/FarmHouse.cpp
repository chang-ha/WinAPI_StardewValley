#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCore.h>

#include "FarmHouse.h"
#include "BackGround.h"
#include "Player.h"
#include "PlayOver.h"
#include "ContentUIManager.h"
#include "TitleScreen.h"
#include "Farm.h"

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

	// _PrevLevel == TitleScreen
	if (nullptr != dynamic_cast<TitleScreen*>(_PrevLevel))
	{
		BGMPlayer = GameEngineSound::SoundPlay("Farm.mp3");
		BGMPlayer.SetVolume(0.5f);
	}

	// _PrevLevel == Farm
	if (nullptr != dynamic_cast<Farm*>(_PrevLevel))
	{
		Farmer->SetPos({ 610,740 });
		Farmer->SetDir(PlayerDir::Up);
	}
}

void FarmHouse::LevelEnd(GameEngineLevel* _NextLevel)
{
	// _NexxtLevel == TitleScreen
	if (nullptr != dynamic_cast<TitleScreen*>(_NextLevel))
	{
		BGMPlayer.Stop();
	}

	// _NextLevel == Farm
	if (nullptr != dynamic_cast<Farm*>(_NextLevel))
	{
		Farm* NextLevel = dynamic_cast<Farm*>(_NextLevel);
		NextLevel->BGMPlayer = this->BGMPlayer;
	}
}

void FarmHouse::Start()
{
	// Texture
	if (nullptr == Back)
	{
		// BackGround
		Back = CreateActor<BackGround>(0);														  
		Back->Init("farmhouse.bmp", "Collision_farmhouse.bmp");
		Back->Renderer->SetTexture("farmhouse.bmp");
		Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
		Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetRenderScale(Back->GetScale() * RENDERRATIO);

		// BackGround Collision
		Back->CollisionRenderer->SetTexture("Collision_farmhouse.bmp");
		Back->CollisionRenderer->SetRenderScale(Back->GetScale() * RENDERRATIO);

		// Player
		Farmer = CreateActor<Player>(1);

		// Detail
		PlayOver* Over = CreateActor<PlayOver>();
		Over->Init("farmhouse_bed.bmp");
		Over->Renderer->SetTexture("farmhouse_bed.bmp");
		Over->Renderer->SetRenderScale(Over->GetScale() * RENDERRATIO);
		Over->SetRenderScale(Over->GetScale() * RENDERRATIO);
		Over->SetPos({ 1024,650 });
	}
	//UI
	CreateActor<ContentUIManager>(0);

	// Sound
	if (nullptr == GameEngineSound::FindSound("Farm.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\BGM");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Farm.mp3"));
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

	if (true == GameEngineInput::IsDown('P'))
	{
		Back->SwitchRender();
	}
}