﻿#include <GameEngineBase/GameEngineDebug.h>

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
#include "ContentInventory.h"
#include "PlayOver.h"
#include "ShippingBin.h"
// Resources
#include "Tree.h"
#include "Rock.h"
#include "SmallTree.h"
#include "Weed.h"
// Crops
#include "ContentCrops.h"
#include "Parsnip.h"
#include "ContentItem.h"
#include "Cauliflower.h"
#include "Garlic.h"
#include "Potato.h"
#include "Rhubarb.h"
#include "Kale.h"
#include "WildCrops.h"
#include "Tulip.h"
// Building
#include "ContentBuilding.h"


Farm::Farm()
{

}

Farm::~Farm()
{

}

void Farm::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	GetMainCamera()->SetYSort(RenderOrder::Play, true);

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
		Back->Init("Farm.bmp", "Collision_Farm.bmp", RENDERRATIO);
		Back->SetPos(GetRenderScale().Half());
	}

	if (nullptr == GameEngineSound::FindSound("hoeHit.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("hoeHit.wav"));
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

	// Detail
	PlayOver* Over = CreateActor<PlayOver>(UpdateOrder::Map);
	Over->Init("Detail_Farm.bmp");
	Over->SetPos(GetRenderScale().Half());

	// CreateActor
	{
		ContentBuilding* Building = CreateActor<ContentBuilding>();
		Building->Init("House.bmp");
		Building->SetPos({ Back->GetRenderScale().X * 0.7945f, Back->GetRenderScale().Y * 0.195f });

		Building = CreateActor<ContentBuilding>();
		Building->Init("MailBox.bmp");
		Building->SetPos({ Back->GetRenderScale().X * 0.858f, Back->GetRenderScale().Y * 0.246f });

		// Tree
		Tree* FarmTree = CreateActor<Tree>(UpdateOrder::Player);
		FarmTree->Init("Tree2.bmp");
		FarmTree->SetPos(FarmTileMap->IndexToPos(57, 20));

		FarmTree = CreateActor<Tree>(UpdateOrder::Player);
		FarmTree->Init("Tree3.bmp");
		FarmTree->SetPos(FarmTileMap->IndexToPos(55, 23));

		FarmTree = CreateActor<Tree>(UpdateOrder::Player);
		FarmTree->Init("Tree3.bmp");
		FarmTree->SetPos(FarmTileMap->IndexToPos(65, 26));

		FarmTree = CreateActor<Tree>(UpdateOrder::Player);
		FarmTree->Init("Tree3.bmp");
		FarmTree->SetPos(FarmTileMap->IndexToPos(55, 30));

		FarmTree = CreateActor<Tree>(UpdateOrder::Player);
		FarmTree->Init("Tree.bmp");
		FarmTree->SetPos(FarmTileMap->IndexToPos(70, 22));
		 
		FarmTree = CreateActor<Tree>(UpdateOrder::Player);
		FarmTree->Init("Tree2.bmp");
		FarmTree->SetPos(FarmTileMap->IndexToPos(60, 25));

		FarmTree = CreateActor<Tree>(UpdateOrder::Player);
		FarmTree->Init("Tree2.bmp");
		FarmTree->SetPos(FarmTileMap->IndexToPos(50, 15));

		FarmTree = CreateActor<Tree>(UpdateOrder::Player);
		FarmTree->Init("Tree.bmp");
		FarmTree->SetPos(FarmTileMap->IndexToPos(51, 21));

		FarmTree = CreateActor<Tree>(UpdateOrder::Player);
		FarmTree->Init("Tree2.bmp");
		FarmTree->SetPos(FarmTileMap->IndexToPos(48, 25));

		FarmTree = CreateActor<Tree>(UpdateOrder::Player);
		FarmTree->Init("Tree.bmp");
		FarmTree->SetPos(FarmTileMap->IndexToPos(73, 26));

		// Small Tree
		SmallTree* FarmSmallTree = CreateActor<SmallTree>(UpdateOrder::Player);
		FarmSmallTree->SetPos(FarmTileMap->IndexToPos(63, 21));

		FarmSmallTree = CreateActor<SmallTree>(UpdateOrder::Player);
		FarmSmallTree->SetPos(FarmTileMap->IndexToPos(58, 20));

		FarmSmallTree = CreateActor<SmallTree>(UpdateOrder::Player);
		FarmSmallTree->SetPos(FarmTileMap->IndexToPos(53, 19));

		FarmSmallTree = CreateActor<SmallTree>(UpdateOrder::Player);
		FarmSmallTree->SetPos(FarmTileMap->IndexToPos(51, 22));

		FarmSmallTree = CreateActor<SmallTree>(UpdateOrder::Player);
		FarmSmallTree->SetPos(FarmTileMap->IndexToPos(53, 24));

		FarmSmallTree = CreateActor<SmallTree>(UpdateOrder::Player);
		FarmSmallTree->SetPos(FarmTileMap->IndexToPos(51, 25));

		FarmSmallTree = CreateActor<SmallTree>(UpdateOrder::Player);
		FarmSmallTree->SetPos(FarmTileMap->IndexToPos(56, 24));

		FarmSmallTree = CreateActor<SmallTree>(UpdateOrder::Player);
		FarmSmallTree->SetPos(FarmTileMap->IndexToPos(64, 30));

		FarmSmallTree = CreateActor<SmallTree>(UpdateOrder::Player);
		FarmSmallTree->SetPos(FarmTileMap->IndexToPos(62, 29));

		FarmSmallTree = CreateActor<SmallTree>(UpdateOrder::Player);
		FarmSmallTree->SetPos(FarmTileMap->IndexToPos(70, 25));

		FarmSmallTree = CreateActor<SmallTree>(UpdateOrder::Player);
		FarmSmallTree->SetPos(FarmTileMap->IndexToPos(69, 27));

		FarmSmallTree = CreateActor<SmallTree>(UpdateOrder::Player);
		FarmSmallTree->SetPos(FarmTileMap->IndexToPos(52, 17));

		// Rock
		Rock* FarmRock = CreateActor<Rock>(UpdateOrder::Player);
		FarmRock->SetPos(FarmTileMap->IndexToPos(66, 20));

		FarmRock = CreateActor<Rock>(UpdateOrder::Player);
		FarmRock->SetPos(FarmTileMap->IndexToPos(53, 15));

		FarmRock = CreateActor<Rock>(UpdateOrder::Player);
		FarmRock->SetPos(FarmTileMap->IndexToPos(52, 13));

		FarmRock = CreateActor<Rock>(UpdateOrder::Player);
		FarmRock->SetPos(FarmTileMap->IndexToPos(58, 23));

		FarmRock = CreateActor<Rock>(UpdateOrder::Player);
		FarmRock->SetPos(FarmTileMap->IndexToPos(67, 23));

		FarmRock = CreateActor<Rock>(UpdateOrder::Player);
		FarmRock->SetPos(FarmTileMap->IndexToPos(59, 27));

		FarmRock = CreateActor<Rock>(UpdateOrder::Player);
		FarmRock->SetPos(FarmTileMap->IndexToPos(52, 29));

		FarmRock = CreateActor<Rock>(UpdateOrder::Player);
		FarmRock->SetPos(FarmTileMap->IndexToPos(61, 28));

		FarmRock = CreateActor<Rock>(UpdateOrder::Player);
		FarmRock->SetPos(FarmTileMap->IndexToPos(56, 27));

		Weed* FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(67, 20));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(68, 20));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(74, 20));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(73, 20));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(74, 21));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(60, 18));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(60, 19));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(55, 15));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(55, 16));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(55, 17));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(56, 15));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(56, 16));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(51, 27));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(53, 27));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(62, 28));

		FarmWeed = CreateActor<Weed>(UpdateOrder::Player);
		FarmWeed->SetPos(FarmTileMap->IndexToPos(64, 27));
	}
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
		_Crops->Death();
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
		ContentCrops* Crops = nullptr;
		if (_SeedItem->GetItemName() == "Seed_Parsnip.bmp")
		{
			Crops = CreateActor<Parsnip>();
		}
		else if (_SeedItem->GetItemName() == "Seed_Cauliflower.bmp")
		{
			Crops = CreateActor<Cauliflower>();
		}
		else if (_SeedItem->GetItemName() == "Seed_Garlic.bmp")
		{
			Crops = CreateActor<Garlic>();
		}
		else if (_SeedItem->GetItemName() == "Seed_Potato.bmp")
		{
			Crops = CreateActor<Potato>();
		}
		else if (_SeedItem->GetItemName() == "Seed_Rhubarb.bmp")
		{
			Crops = CreateActor<Rhubarb>();
		}
		else if (_SeedItem->GetItemName() == "Seed_Kale.bmp")
		{
			Crops = CreateActor<Kale>();
		}
		else if (_SeedItem->GetItemName() == "Seed_Wild.bmp")
		{
			Crops = CreateActor<WildCrops>();
		}
		else if (_SeedItem->GetItemName() == "Seed_Tulip.bmp")
		{
			Crops = CreateActor<Tulip>();
		}

		if (nullptr == Crops)
		{
			MsgBoxAssert("씨앗이 아닌 아이템을 땅에 심을수 없습니다.");
		}

		Crops->SetPos(FarmTileMap->IndexToPos(Index_X, Index_Y));
		ContentInventory::MainInventory->UseItem(_SeedItem);
		AllCrops.push_back(Crops);
	}
}