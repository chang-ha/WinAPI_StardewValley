#include <GameEnginePlatform/GameEngineWindow.h>

#include "StardewValleyCore.h"
#include "TitleScreen.h"
#include "FarmHouse.h"
#include "Farm.h"
#include "BusStation.h"
#include "Beach.h"
#include "PelicanTown.h"
#include "GeneralStore.h"
#include "GlobalValue.h"

StardewValleyCore::StardewValleyCore()
{

}

StardewValleyCore::~StardewValleyCore()
{
}

void StardewValleyCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 0, 0 }, { 1600, 900 });
	GlobalValue::Init();

	GameEngineCore::CreateLevel<TitleScreen>("TitleScreen");
	GameEngineCore::CreateLevel<FarmHouse>("FarmHouse");
	GameEngineCore::CreateLevel<Farm>("Farm");
	GameEngineCore::CreateLevel<BusStation>("BusStation");
	GameEngineCore::CreateLevel<PelicanTown>("PelicanTown");
	GameEngineCore::CreateLevel<GeneralStore>("GeneralStore");
	GameEngineCore::CreateLevel<Beach>("Beach");
	GameEngineCore::ChangeLevel("TitleScreen");
}
void StardewValleyCore::Update(float _Delta)
{

}
void StardewValleyCore::Render(float _Delta)
{

}
void StardewValleyCore::Release()
{

}