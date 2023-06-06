#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>

#include "GeneralStore.h"
#include "Player.h"
#include "PelicanTown.h"
#include "BackGround.h"
#include "ContentsEnum.h"

GeneralStore::GeneralStore()
{

}

GeneralStore::~GeneralStore()
{

}

void GeneralStore::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
	Farmer->SetCollisionTexture("Collision_GeneralStore.bmp");

	// _PrevLevel == PelicanTown
	if (nullptr != dynamic_cast<PelicanTown*>(_PrevLevel))
	{
		Farmer->SetPos({Back->GetRenderScale().X * 0.155f, Back->GetRenderScale().Y * 0.885f});
		GetMainCamera()->SetPos({0, Back->GetRenderScale().Y - GlobalValue::WinScale.Y});
		Farmer->SetDir(PlayerDir::Up);
	}
}

void GeneralStore::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

	// _NextLevel == PelicanTown
	if (nullptr != dynamic_cast<PelicanTown*>(_NextLevel))
	{
	}
}

void GeneralStore::Start()
{
	PrevLevel = "PelicanTown";
	if (false == ResourcesManager::GetInst().IsLoadTexture("GeneralStore.bmp"))
	{
		Back = CreateActor<BackGround>(UpdateOrder::Map);
		Back->Init("GeneralStore.bmp", "Collision_GeneralStore.bmp");
		Back->Renderer->SetTexture("GeneralStore.bmp");
		Back->Renderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetRenderScale(Back->GetScale() * RENDERRATIO);
		Back->SetPos(GetRenderScale().Half());

		Back->CollisionRenderer->SetTexture("Collision_GeneralStore.bmp");
		Back->CollisionRenderer->SetRenderScale(Back->GetScale() * RENDERRATIO);
	}
}
void GeneralStore::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	if (true == GameEngineInput::IsDown('P'))
	{
		Back->SwitchRender();
	}
}