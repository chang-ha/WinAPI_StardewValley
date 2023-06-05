#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/TileMap.h>

#include "ContentLevel.h"
#include "BackGround.h"
#include "Player.h"
#include "TitleScreen.h"
#include "ContentUIManager.h"
#include "ContentMouse.h"
#include "ContentsEnum.h"
#include "ContentInventory.h"

ContentLevel::ContentLevel()
{
	WinScale = GameEngineWindow::MainWindow.GetScale();
}

ContentLevel::~ContentLevel()
{

}

float4 ContentLevel::GetRenderScale()
{
	return Back->GetRenderScale();
}

void ContentLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr != dynamic_cast<TitleScreen*>(this))
	{
		UIManager->Clock->Off();
		UIManager->ClockHand->Off();
		UIManager->Energy->Off();
		UIManager->Inventory->Off();
	}
	else
	{
		UIManager->Clock->On();
		UIManager->ClockHand->On();
		UIManager->Energy->On();
		UIManager->Inventory->On();

		Farmer = Player::MainPlayer;
		FarmerInventory = ContentInventory::MainInventory;
		Farmer->SetPlayLevel(this);
		if (nullptr == Farmer)
		{
			MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
		}
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Select_Tile.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TileMap\\Select_Tile.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Select_Tile.bmp", 1, 1);
	}

	if (nullptr == UITileMap)
	{
		UITileMap = CreateActor<TileMap>();
		UITileMap->CreateTileMap("Select_Tile.bmp", Back->GetScale().iX() / TILESIZE.iX(), Back->GetScale().iY() / TILESIZE.iY(), TILESIZE * RENDERRATIO, static_cast<int>(RenderOrder::PlayBelow));
	}
}

void ContentLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel* NextLevel = dynamic_cast<ContentLevel*>(_NextLevel);
	if (nullptr != NextLevel)
	{
		NextLevel->UIManager = UIManager;
		NextLevel->MainMouse = MainMouse;
	}
}

void ContentLevel::Start()
{
	if (nullptr == UIManager)
	{
		UIManager = CreateActor<ContentUIManager>(0);
		UIManager->OverOn();
		ContentUIManager::MainUI = UIManager;

		MainMouse = CreateActor<ContentMouse>(0);
		MainMouse->OverOn();
	}
}

void ContentLevel::Update(float _Delta)
{
	MainMouse->SetPos(GetMainCamera()->GetPos() + GameEngineWindow::MainWindow.GetMousePos());
	if (nullptr != FarmerInventory)
	{
		FarmerInventory->SetPos(GetMainCamera()->GetPos() + WinScale.Half());
	}

	if (true == GameEngineInput::IsDown(VK_F1))
	{
		CollisionDebugRenderSwitch();
	}

	if (nullptr != Farmer)
	{
		CurIndex = Farmer->TileLimit(UITileMap);
		UITileMap->SetTile(UITileMap->IndexToPos(CurIndex.iX(), CurIndex.iY()), 0);

		GameEngineRenderer* PrevTile = UITileMap->GetTile(PrevIndex.iX(), PrevIndex.iY());
		GameEngineRenderer* CurTile = UITileMap->GetTile(CurIndex.iX(), CurIndex.iY());

		if (nullptr != PrevTile && PrevTile != CurTile)
		{
			PrevTile->Off();
		}
		PrevIndex = CurIndex;
		CurTile->On();
	}

	if (true == GameEngineInput::IsDown('1') && "" != PrevLevel)
	{
		GameEngineCore::ChangeLevel(PrevLevel);
	}

	if (true == GameEngineInput::IsDown('2') && "" != NextLevel)
	{
		GameEngineCore::ChangeLevel(NextLevel);
	}
}
