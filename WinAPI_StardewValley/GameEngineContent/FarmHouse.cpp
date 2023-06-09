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
#include "ContentInventory.h"
#include "ContentsEnum.h"

FarmHouse::FarmHouse()
{

}

FarmHouse::~FarmHouse()
{

}

void FarmHouse::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	Player::MainPlayer->SetCollisionTexture("Collision_farmhouse.bmp");
	Player::MainPlayer->SetPos({ GetRenderScale().X * 0.595f, GetRenderScale().Y * 0.65f});
	Player::MainPlayer->SetDir(PlayerDir::Right);

	// _PrevLevel == TitleScreen
	if (nullptr != dynamic_cast<TitleScreen*>(_PrevLevel))
	{
		BGMPlayer = GameEngineSound::SoundPlay("Farm.mp3", 10000);
	}

	// _PrevLevel == Farm
	if (nullptr != dynamic_cast<Farm*>(_PrevLevel))
	{
		Player::MainPlayer->SetPos({ GetRenderScale().X * 0.410f, GetRenderScale().Y * 0.74f });
		Player::MainPlayer->SetDir(PlayerDir::Up);
	}
}

void FarmHouse::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	// _NexxtLevel == TitleScreen
	if (nullptr != dynamic_cast<TitleScreen*>(_NextLevel))
	{
		BGMPlayer.Stop();
		Player::MainPlayer->OverOff();
		ContentInventory::MainInventory->OverOff();
	}

	// _NextLevel == Farm
	if (nullptr != dynamic_cast<Farm*>(_NextLevel))
	{
		Farm* NextLevel = dynamic_cast<Farm*>(_NextLevel);
		NextLevel->BGMPlayer = this->BGMPlayer;
		Player::MainPlayer->OverOn();
		ContentInventory::MainInventory->OverOn();
	}
}

void FarmHouse::Start()
{
	PrevLevel = "TitleScreen";
	NextLevel = "Farm";

	// Texture
	if (nullptr == Back)
	{
		// BackGround
		Back = CreateActor<BackGround>(UpdateOrder::Map);														  
		Back->Init("farmhouse.bmp", "Collision_farmhouse.bmp");
		Back->Renderer->SetTexture("farmhouse.bmp");
		Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetPos(GetRenderScale().Half());

		// BackGround Collision
		Back->CollisionRenderer->SetTexture("Collision_farmhouse.bmp");
		Back->CollisionRenderer->SetRenderScale(Back->GetScale() * RENDERRATIO);

		// Player
		Player::MainPlayer = CreateActor<Player>(UpdateOrder::Player);
		ContentInventory::MainInventory = CreateActor<ContentInventory>(UpdateOrder::Inventory);

		// Detail
		PlayOver* Over = CreateActor<PlayOver>(UpdateOrder::Map);
		Over->Init("farmhouse_bed.bmp");
		Over->Renderer->SetTexture("farmhouse_bed.bmp");
		Over->Renderer->SetRenderScale(Over->GetScale() * RENDERRATIO);
		Over->SetRenderScale(Over->GetScale() * RENDERRATIO);
		Over->SetPos({ GetRenderScale().X * 0.607f, GetRenderScale().Y * 0.66f });
	}

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
	ContentLevel::Update(_Delta);

	if (true == GameEngineInput::IsDown('P'))
	{
		Back->SwitchRender();
	}
}