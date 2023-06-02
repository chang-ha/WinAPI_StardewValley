#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>

#include "Player.h"
#include "PelicanTown.h"
#include "BackGround.h"
#include "BusStation.h"
#include "Beach.h"
#include "ContentInventory.h"

PelicanTown::PelicanTown()
{

}

PelicanTown::~PelicanTown()
{

}

void PelicanTown::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
	Farmer->SetCollisionTexture("Collision_Town.bmp");

	// _PrevLevel == BusStation
	if (nullptr != dynamic_cast<BusStation*>(_PrevLevel))
	{
		Farmer->SetPos({ 50, Back->GetRenderScale().Y * 0.5f });
		GetMainCamera()->SetPos({ 0, Back->GetRenderScale().Y * 0.5f - WinScale.Half().Y});
		Farmer->SetDir(PlayerDir::Right);
	}

	// _PrevLevel == Beach
	if (nullptr != dynamic_cast<Beach*>(_PrevLevel))
	{
		Farmer->SetPos({ Back->GetRenderScale().X * 0.455f, Back->GetRenderScale().Y - 50});
		GetMainCamera()->SetPos({ Farmer->GetPos().X - WinScale.Half().X , Back->GetRenderScale().Y - WinScale.Y});
		Farmer->SetDir(PlayerDir::Up);
		BGMPlayer = GameEngineSound::SoundPlay("Town.mp3", 10000);
	}
}

void PelicanTown::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

	// _NextLevel == BusStation
	if (nullptr != dynamic_cast<BusStation*>(_NextLevel))
	{
		BusStation* NextLevel = dynamic_cast<BusStation*>(_NextLevel);
		NextLevel->BGMPlayer = this->BGMPlayer;
	}

	// _NextLevel == Beach
	if (nullptr != dynamic_cast<Beach*>(_NextLevel))
	{
		BGMPlayer.Stop();
	}
}

void PelicanTown::Start()
{
	PrevLevel = "BusStation";
	NextLevel = "Beach";
	if (false == ResourcesManager::GetInst().IsLoadTexture("Town.bmp"))
	{
		Back = CreateActor<BackGround>(0);
		Back->Init("Town.bmp", "Collision_Town.bmp");
		Back->Renderer->SetTexture("Town.bmp");
		Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetPos(GetRenderScale().Half());

		Back->CollisionRenderer->SetTexture("Collision_Town.bmp");
		Back->CollisionRenderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	}

	if (nullptr == GameEngineSound::FindSound("Town.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\BGM");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Town.mp3"));
	}
}
void PelicanTown::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	if (true == GameEngineInput::IsDown('P'))
	{
		Back->SwitchRender();
	}
}