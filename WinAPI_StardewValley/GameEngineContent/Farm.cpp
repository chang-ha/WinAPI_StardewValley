#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "Farm.h"
#include "BackGround.h"
#include "Player.h"
#include "FarmHouse.h"
#include "BusStation.h"
#include "ContentsEnum.h"

#include <GameEngineCore/TileMap.h>

Farm::Farm()
{

}

Farm::~Farm()
{

}

void Farm::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

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

	// Load Sound
	if (nullptr == GameEngineSound::FindSound("hoeHit.wav"))
	{
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Effect\\hoeHit.wav"));
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
		FarmTileMap->CreateTileMap("hoeDirt.bmp", 80, 65, {16*RENDERRATIO, 16*RENDERRATIO}, static_cast<int>(RenderOrder::PlayBelow));
	}
}
void Farm::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
	if (true == GameEngineInput::IsDown('1'))
	{
		GameEngineCore::ChangeLevel("FarmHouse");
	}
	if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("BusStation");
	}

	if (true == GameEngineInput::IsDown('P'))
	{
		Back->SwitchRender();
	}

	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		FarmTileMap->SetTile(MainMouse->GetPos(), 0);
		//EffectPlayer = GameEngineSound::SoundPlay("hoeHit.wav");
		//EffectPlayer.SetVolume(0.5f);
	}
}