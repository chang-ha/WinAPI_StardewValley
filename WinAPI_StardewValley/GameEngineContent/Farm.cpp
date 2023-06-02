﻿#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/TileMap.h>

#include "Farm.h"
#include "BackGround.h"
#include "Player.h"
#include "FarmHouse.h"
#include "BusStation.h"
#include "ContentsEnum.h"
#include "ShippingBin.h"

Farm::Farm()
{

}

Farm::~Farm()
{

}

void Farm::LevelStart(GameEngineLevel* _PrevLevel)
{
	Farmer = Player::MainPlayer;
	Farmer->SetPlayLevel(this);

	if (nullptr == Farmer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}
	Farmer->SetCollisionTexture("Collision_Farm.bmp");

	// _PrevLevel == FarmHouse
	if (nullptr != dynamic_cast<FarmHouse*>(_PrevLevel))
	{
		Farmer->SetPos({ Back->GetRenderScale().X * 0.8055f, Back->GetRenderScale().Y * 0.225f});
		Farmer->SetDir(PlayerDir::Down);
		GetMainCamera()->SetPos(Farmer->GetPos() - WinScale.Half());
	}

	// _PrveLevel == BusStation
	if (nullptr != dynamic_cast<BusStation*>(_PrevLevel))
	{
		Farmer->SetDir(PlayerDir::Left);
		GetMainCamera()->SetPos({Back->GetRenderScale().X - WinScale.X, Back->GetRenderScale().Y * 0.36f - WinScale.Y});
		Farmer->SetPos({ Back->GetRenderScale().X - 100 , Back->GetRenderScale().Y * 0.25f });
	}

	ContentLevel::LevelStart(_PrevLevel);
}

void Farm::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

	// _NextLevel == FarmHouse
	if (nullptr != dynamic_cast<FarmHouse*>(_NextLevel))
	{
		FarmHouse* NextLevel = dynamic_cast<FarmHouse*>(_NextLevel);
		NextLevel->BGMPlayer = this->BGMPlayer;
	}

	// _NextLevel == BusStation
	if (nullptr != dynamic_cast<BusStation*>(_NextLevel))
	{
		BusStation* NextLevel = dynamic_cast<BusStation*>(_NextLevel);
		NextLevel->BGMPlayer = this->BGMPlayer;
	}
}


void Farm::Start()
{
	PrevLevel = "FarmHouse";
	NextLevel = "BusStation";
	GameEnginePath FilePath;

	// Load Texture
	if (false == ResourcesManager::GetInst().IsLoadTexture("Farm.bmp"))
	{
		Back = CreateActor<BackGround>(0);
		Back->Init("Farm.bmp", "Collision_Farm.bmp");
		Back->Renderer->SetTexture("Farm.bmp");
		Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetPos(GetRenderScale().Half());

		Back->CollisionRenderer->SetTexture("Collision_Farm.bmp");
		Back->CollisionRenderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	}

	// Create TileMap
	if (nullptr == FarmTileMap)
	{
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TileMap\\hoeDirt.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("hoeDirt.bmp", 12, 4);
		FarmTileMap = CreateActor<TileMap>();
		FarmTileMap->CreateTileMap("hoeDirt.bmp", Back->GetScale().iX() / TILESIZE.iX(), Back->GetScale().iY() / TILESIZE.iY(), TILESIZE * RENDERRATIO, static_cast<int>(RenderOrder::PlayBelow));
	}
	ShippingBin* ship = CreateActor<ShippingBin>();
	ship->SetPos({Back->GetRenderScale().X * 0.901f, Back->GetRenderScale().Y * 0.2150f});
}

void Farm::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	if (true == GameEngineInput::IsDown('P'))
	{
		Back->SwitchRender();
	}
}