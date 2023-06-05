#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "Player.h"
#include "Beach.h"
#include "BackGround.h"
#include "ContentLevel.h"
#include "ContentsEnum.h"

Beach::Beach()
{

}

Beach::~Beach()
{

}


void Beach::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	Farmer->SetCollisionTexture("Collision_Beach.bmp");
	Farmer->SetPos({ GetRenderScale().X * 0.37f, 30});
	Farmer->SetDir(PlayerDir::Down);
	GetMainCamera()->SetPos({ Farmer->GetPos().X - WinScale.Half().X, 0});

	BGMPlayer = GameEngineSound::SoundPlay("ocean.wav", 10000);

	BGMPlayer.SetVolume(0.5f);
}

void Beach::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	BGMPlayer.Stop();
}


void Beach::Start()
{
	PrevLevel = "PelicanTown";
	if (false == ResourcesManager::GetInst().IsLoadTexture("Beach.bmp"))
	{
		Back = CreateActor<BackGround>(UpdateOrder::Map);
		Back->Init("Beach.bmp", "Collision_Beach.bmp");
		Back->Renderer->SetTexture("Beach.bmp");
		Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetPos(GetRenderScale().Half());

		Back->CollisionRenderer->SetTexture("Collision_Beach.bmp");
		Back->CollisionRenderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	}

	if (nullptr == GameEngineSound::FindSound("ocean.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\BGM");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("ocean.wav"));
	}
}
void Beach::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	if (true == GameEngineInput::IsDown('P'))
	{
		Back->SwitchRender();
	}
}