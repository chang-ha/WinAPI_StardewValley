#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>

#include "GeneralStore.h"
#include "Player.h"
#include "PelicanTown.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "Counter.h"
#include "ContentNpc.h"
#include "PlayOver.h"

GeneralStore::GeneralStore()
{

}

GeneralStore::~GeneralStore()
{

}

void GeneralStore::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	GetMainCamera()->SetYSort(RenderOrder::Play, true);

	Player::MainPlayer->SetCollisionTexture("Collision_GeneralStore.bmp");

	// _PrevLevel == PelicanTown
	if (nullptr != dynamic_cast<PelicanTown*>(_PrevLevel))
	{
		Player::MainPlayer->SetPos({Back->GetRenderScale().X * 0.155f, Back->GetRenderScale().Y * 0.885f});
		GetMainCamera()->SetPos({0, Back->GetRenderScale().Y - GlobalValue::WinScale.Y});
		Player::MainPlayer->SetDir(PlayerDir::Up);
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
		Back->Init("GeneralStore.bmp", "Collision_GeneralStore.bmp", RENDERRATIO);
		Back->SetPos(GetRenderScale().Half());
	}

	Counter* _Counter = CreateActor<Counter>();
	_Counter->SetPos({ Back->GetRenderScale().X * 0.143f, Back->GetRenderScale().Y * 0.544f });

	ContentNpc* _Npc = CreateActor<ContentNpc>();
	_Npc->SetPos({ Back->GetRenderScale().X * 0.1f, Back->GetRenderScale().Y * 0.52f });

	// Detail
	PlayOver* Over = CreateActor<PlayOver>(UpdateOrder::Map);
	Over->Init("Detail_GeneralStore.bmp");
	Over->SetPos(GetRenderScale().Half());
}
void GeneralStore::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}