#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Farm.h"
#include "BackGround.h"
#include "Player.h"
#include "FarmHouse.h"
#include "BusStation.h"
#include "ContentsEnum.h"
#include "ShippingBin.h"
#include "ContentInventory.h"
#include "Tree.h"
#include "Rock.h"

Farm::Farm()
{

}

Farm::~Farm()
{

}

void Farm::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	Farmer->SetCollisionTexture("Collision_Farm.bmp");

	// _PrevLevel == FarmHouse
	if (nullptr != dynamic_cast<FarmHouse*>(_PrevLevel))
	{
		Farmer->SetPos({ Back->GetRenderScale().X * 0.8055f, Back->GetRenderScale().Y * 0.225f });
		Farmer->SetDir(PlayerDir::Down);
		GetMainCamera()->SetPos(Farmer->GetPos() - GlobalValue::WinScale.Half());
	}

	// _PrveLevel == BusStation
	if (nullptr != dynamic_cast<BusStation*>(_PrevLevel))
	{
		Farmer->SetDir(PlayerDir::Left);
		GetMainCamera()->SetPos({ Back->GetRenderScale().X - GlobalValue::WinScale.X, Back->GetRenderScale().Y * 0.36f - GlobalValue::WinScale.Y });
		Farmer->SetPos({ Back->GetRenderScale().X - 100 , Back->GetRenderScale().Y * 0.25f });
	}

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
	NextLevel = "BusStation";
	Building = "FarmHouse";
	GameEnginePath FilePath;

	// Load Texture
	if (false == ResourcesManager::GetInst().IsLoadTexture("Farm.bmp"))
	{
		Back = CreateActor<BackGround>(UpdateOrder::Map);
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
		ResourcesManager::GetInst().CreateSpriteSheet("hoeDirt.bmp", 8, 4);
		FarmTileMap = CreateActor<TileMap>(UpdateOrder::Player);
		FarmTileMap->CreateTileMap("hoeDirt.bmp", Back->GetScale().iX() / TILESIZE.iX(), Back->GetScale().iY() / TILESIZE.iY(), TILESIZE * RENDERRATIO, static_cast<int>(RenderOrder::BackGround));
	}
	ShippingBin* ship = CreateActor<ShippingBin>(UpdateOrder::Map);
	ship->SetPos({ Back->GetRenderScale().X * 0.901f, Back->GetRenderScale().Y * 0.2150f });

	Tree* FarmTree = CreateActor<Tree>(UpdateOrder::Player);
	FarmTree->Init("Tree.bmp");
	FarmTree->SetPos(FarmTileMap->IndexToPos(60, 20) + TILESIZE.Half() * RENDERRATIO);

	Rock* FarmRock = CreateActor<Rock>(UpdateOrder::Player);
	FarmRock->Init("Rock_Small01.bmp");
	FarmRock->SetPos(FarmTileMap->IndexToPos(65, 20) + TILESIZE.Half() * RENDERRATIO);

	FarmRock = CreateActor<Rock>(UpdateOrder::Player);
	FarmRock->Init("Rock_Small02.bmp");
	FarmRock->SetPos(FarmTileMap->IndexToPos(66, 20) + TILESIZE.Half() * RENDERRATIO);
}

void Farm::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	if (true == GameEngineInput::IsDown('P'))
	{
		Back->SwitchRender();
	}
}

void Farm::TileSetting(int _X, int _Y, bool IsWatering)
{
	GameEngineRenderer* CurTile = FarmTileMap->GetTile(_X, _Y);
	if (nullptr == CurTile)
	{
		return;
	}

	int TileImage[2][2][2][2] = { 0, 25, 27, 26, 8, 1, 3, 2, 24, 17, 19, 18, 16, 9, 11, 10 };
	int W = nullptr == FarmTileMap->GetTile(_X, _Y - 1) ? 0 : 1;
	int X = nullptr == FarmTileMap->GetTile(_X, _Y + 1) ? 0 : 1;
	int Y = nullptr == FarmTileMap->GetTile(_X - 1, _Y) ? 0 : 1;
	int Z = nullptr == FarmTileMap->GetTile(_X + 1, _Y) ? 0 : 1;
	int Plus = false == IsWatering ? 0 : 4;

	FarmTileMap->SetTile(_X, _Y, TileImage[W][X][Y][Z] + Plus);
}
