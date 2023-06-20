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
#include "SleepLevel.h"

ContentLevel::ContentLevel()
{
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
	if (nullptr != dynamic_cast<TitleScreen*>(this) || nullptr != dynamic_cast<SleepLevel*>(this))
	{
		ContentUIManager::MainUI->BasicUIOff();
		ContentUIManager::MainUI->ResetCurTextMoney();
	}
	else
	{
		ContentUIManager::MainUI->BasicUIOn();


		if (nullptr == Player::MainPlayer)
		{
			MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
		}
		Player::MainPlayer->SetPlayLevel(this);

		if (nullptr == UITileMap)
		{
			UITileMap = CreateActor<TileMap>();
			UITileMap->CreateTileMap("Select_Tile.bmp", Back->GetScale().iX() / TILESIZE.iX(), Back->GetScale().iY() / TILESIZE.iY(), TILESIZE * RENDERRATIO, static_cast<int>(RenderOrder::PlayBelow));
		}
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Select_Tile.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\TileMap\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Select_Tile.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Select_Tile.bmp", 1, 1);
	}
}

void ContentLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	Back->ResetBackGroundRender();
}

void ContentLevel::Start()
{
	if (nullptr == ContentUIManager::MainUI)
	{
		ContentUIManager::MainUI = CreateActor<ContentUIManager>(0);
		ContentUIManager::MainUI->OverOn();
	}

	if (nullptr == ContentMouse::MainMouse)
	{
		ContentMouse::MainMouse = CreateActor<ContentMouse>(0);
		ContentMouse::MainMouse->OverOn();
	}
}

void ContentLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_F1))
	{
		CollisionDebugRenderSwitch();
	}

	if (true == GameEngineInput::IsDown(VK_F2))
	{
		Back->SwitchBackGroundRender();
	}

	if (true == GameEngineInput::IsDown(VK_F3) && "" != PrevLevel)
	{
		GameEngineCore::ChangeLevel(PrevLevel);
	}

	if (true == GameEngineInput::IsDown(VK_F4) && "" != NextLevel)
	{
		GameEngineCore::ChangeLevel(NextLevel);
	}

	if (nullptr != UITileMap)
	{
		CurIndex = Player::MainPlayer->TileLimit();
		UITileMap->SetTile(UITileMap->IndexToPos(CurIndex.iX(), CurIndex.iY()), 0);

		GameEngineRenderer* PrevTile = UITileMap->GetTile(PrevIndex.iX(), PrevIndex.iY());
		GameEngineRenderer* CurTile = UITileMap->GetTile(CurIndex.iX(), CurIndex.iY());

		if (nullptr != PrevTile && PrevTile != CurTile)
		{
			UITileMap->DeathTile(PrevIndex.iX(), PrevIndex.iY());
		}

		//if (nullptr != PrevTile && PrevTile != CurTile)
		//{
		//	PrevTile->Off();
		//}
		PrevIndex = CurIndex;

		if (nullptr != CurTile)
		{
			CurTile->On();
		}
	}
}
