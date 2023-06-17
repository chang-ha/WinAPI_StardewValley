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
#include "ContentCrops.h"

Farm::Farm()
{

}

Farm::~Farm()
{

}

void Farm::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	Player::MainPlayer->SetCollisionTexture("Collision_Farm.bmp");

	// _PrevLevel == FarmHouse
	if (nullptr != dynamic_cast<FarmHouse*>(_PrevLevel))
	{
		FarmHouse* _FarmHouse = dynamic_cast<FarmHouse*>(_PrevLevel);
		Player::MainPlayer->SetPos({ Back->GetRenderScale().X * 0.8055f, Back->GetRenderScale().Y * 0.225f });
		Player::MainPlayer->SetDir(PlayerDir::Down);
		GetMainCamera()->SetPos(Player::MainPlayer->GetPos() - GlobalValue::WinScale * 0.55f);

		// Crops Grow
		if (true == _FarmHouse->GetIsSleep())
		{
			for (ContentCrops* _CurCrops : AllCrops)
			{
				float4 Index = FarmWateringTileMap->PosToIndex(_CurCrops->GetPos());
				if (nullptr == FarmWateringTileMap->GetTile(Index.iX(), Index.iY()))
				{
					continue;
				}
				_CurCrops->Grow();
			}

			for (int y = 0; y < Back->GetScale().iY() / TILESIZE.iY(); y++)
			{
				for (int x = 0; x < Back->GetScale().iX() / TILESIZE.iX(); x++)
				{
					FarmWateringTileMap->DeathTile(x, y);
				}
			}
			_FarmHouse->SetIsSleep(false);
		}
	}

	// _PrveLevel == BusStation
	if (nullptr != dynamic_cast<BusStation*>(_PrevLevel))
	{
		Player::MainPlayer->SetDir(PlayerDir::Left);
		GetMainCamera()->SetPos({ Back->GetRenderScale().X - GlobalValue::WinScale.X, Back->GetRenderScale().Y * 0.36f - GlobalValue::WinScale.Y });
		Player::MainPlayer->SetPos({ Back->GetRenderScale().X - 100 , Back->GetRenderScale().Y * 0.25f });
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
	PrevLevel = "FarmHouse";
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

	if (nullptr == GameEngineSound::FindSound("hoeHit.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("hoeHit.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("wateringcan.wav"));
	}

	// Create TileMap
	if (nullptr == FarmTileMap)
	{
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TileMap\\hoeDirt.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TileMap\\waterDirt.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("hoeDirt.bmp", 4, 4);
		ResourcesManager::GetInst().CreateSpriteSheet("waterDirt.bmp", 4, 4);
		FarmTileMap = CreateActor<TileMap>(UpdateOrder::Player);
		FarmTileMap->CreateTileMap("hoeDirt.bmp", Back->GetScale().iX() / TILESIZE.iX(), Back->GetScale().iY() / TILESIZE.iY(), TILESIZE * RENDERRATIO, static_cast<int>(RenderOrder::BackGround));

		FarmWateringTileMap = CreateActor<TileMap>(UpdateOrder::Player);
		FarmWateringTileMap->CreateTileMap("waterDirt.bmp", Back->GetScale().iX() / TILESIZE.iX(), Back->GetScale().iY() / TILESIZE.iY(), TILESIZE * RENDERRATIO, static_cast<int>(RenderOrder::BackGround));
	}

	// Shipping Box
	ShippingBin* ship = CreateActor<ShippingBin>(UpdateOrder::Map);
	ship->SetPos({ Back->GetRenderScale().X * 0.901f, Back->GetRenderScale().Y * 0.2150f });

	// Test Actor
	Tree* FarmTree = CreateActor<Tree>(UpdateOrder::Player);
	FarmTree->Init("Tree.bmp");
	FarmTree->SetPos(FarmTileMap->IndexToPos(60, 20));

	Rock* FarmRock = CreateActor<Rock>(UpdateOrder::Player);
	FarmRock->Init("Rock_Small01.bmp");
	FarmRock->SetPos(FarmTileMap->IndexToPos(65, 20));

	FarmRock = CreateActor<Rock>(UpdateOrder::Player);
	FarmRock->Init("Rock_Small02.bmp");
	FarmRock->SetPos(FarmTileMap->IndexToPos(66, 20));
}

void Farm::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	// Crops Release
	std::list<ContentCrops*>::iterator StartIter = AllCrops.begin();
	std::list<ContentCrops*>::iterator EndIter = AllCrops.end();
	for (; StartIter != EndIter; )
	{
		ContentCrops* _Crops = *StartIter;
		if (true == _Crops->IsUpdate())
		{
			++StartIter;
			continue;
		}
		StartIter = AllCrops.erase(StartIter);
	}
}

void Farm::TileSetting(int _X, int _Y, bool IsWatering)
{
	int TileImage[2][2][2][2] = { 0, 13, 15, 14, 4, 1, 3, 2, 12, 9, 11, 10, 8, 5, 7, 6 };

	switch (IsWatering)
	{
	case false:
	{
		GameEngineRenderer* CurTile = FarmTileMap->GetTile(_X, _Y);
		if (nullptr == CurTile)
		{
			return;
		}

		int W = nullptr == FarmTileMap->GetTile(_X, _Y - 1) ? 0 : 1;
		int X = nullptr == FarmTileMap->GetTile(_X, _Y + 1) ? 0 : 1;
		int Y = nullptr == FarmTileMap->GetTile(_X - 1, _Y) ? 0 : 1;
		int Z = nullptr == FarmTileMap->GetTile(_X + 1, _Y) ? 0 : 1;
		FarmTileMap->SetTile(_X, _Y, TileImage[W][X][Y][Z]);
	}
	break;
	case true:
	{
		GameEngineRenderer* CurTile = FarmWateringTileMap->GetTile(_X, _Y);
		if (nullptr == CurTile)
		{
			return;
		}
		int W = nullptr == FarmWateringTileMap->GetTile(_X, _Y - 1) ? 0 : 1;
		int X = nullptr == FarmWateringTileMap->GetTile(_X, _Y + 1) ? 0 : 1;
		int Y = nullptr == FarmWateringTileMap->GetTile(_X - 1, _Y) ? 0 : 1;
		int Z = nullptr == FarmWateringTileMap->GetTile(_X + 1, _Y) ? 0 : 1;
		FarmWateringTileMap->SetTile(_X, _Y, TileImage[W][X][Y][Z]);
	}
	break;
	}
}

void Farm::GroundHoe()
{
	int Index_X = Player::MainPlayer->TileLimit().iX();
	int Index_Y = Player::MainPlayer->TileLimit().iY();
	if (nullptr != FarmTileMap->GetTile(Index_X, Index_Y))
	{
		return;
	}

	float4 CheckPos = FarmTileMap->IndexToPos(Index_X, Index_Y);
	if (Tile::Sand != Player::MainPlayer->GetTileColor(RGB(0, 0, 0), CheckPos - Player::MainPlayer->GetPos()))
	{
		return;
	}

	std::vector<GameEngineCollision*> _CollisionResult;
	if (false == Player::MainPlayer->ToolCollision->Collision(CollisionOrder::Resources, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
	{
		FarmTileMap->SetTile(Index_X, Index_Y, 0);
		TileSetting(Index_X, Index_Y);
		TileSetting(Index_X, Index_Y - 1);
		TileSetting(Index_X, Index_Y + 1);
		TileSetting(Index_X - 1, Index_Y);
		TileSetting(Index_X + 1, Index_Y);
		EffectPlayer = GameEngineSound::SoundPlay("hoeHit.wav");
	}
}

void Farm::GroundWatering()
{
	int Index_X = Player::MainPlayer->TileLimit().iX();
	int Index_Y = Player::MainPlayer->TileLimit().iY();
	if (nullptr != FarmTileMap->GetTile(Index_X, Index_Y))
	{
		FarmWateringTileMap->SetTile(Index_X, Index_Y, 0);
		TileSetting(Index_X, Index_Y, true);
		TileSetting(Index_X, Index_Y - 1, true);
		TileSetting(Index_X, Index_Y + 1, true);
		TileSetting(Index_X - 1, Index_Y, true);
		TileSetting(Index_X + 1, Index_Y, true);
		EffectPlayer = GameEngineSound::SoundPlay("wateringcan.wav");
	}
}

void Farm::GroundSeeding(ContentItem* _SeedItem)
{
	std::vector<GameEngineCollision*> _CollisionResult;
	if (true == Player::MainPlayer->ToolCollision->Collision(CollisionOrder::Crops, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
	{
		return;
	}

	int Index_X = Player::MainPlayer->TileLimit().iX();
	int Index_Y = Player::MainPlayer->TileLimit().iY();
	if (nullptr != FarmTileMap->GetTile(Index_X, Index_Y))
	{
		ContentCrops* Crops = CreateActor<ContentCrops>();
		Crops->SetPos(FarmTileMap->IndexToPos(Index_X, Index_Y));
		ContentInventory::MainInventory->UseItem(_SeedItem);
		AllCrops.push_back(Crops);
	}
}