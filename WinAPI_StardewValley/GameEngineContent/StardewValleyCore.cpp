#include <GameEnginePlatform/GameEngineWindow.h>

#include "StardewValleyCore.h"
#include "TitleScreen.h"
#include "FarmHouse.h"
#include "Farm.h"
#include "BusStation.h"
#include "Beach.h"
#include "PelicanTown.h"

StardewValleyCore::StardewValleyCore()
{

}

StardewValleyCore::~StardewValleyCore()
{
}

void StardewValleyCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 1600, 900 });

	GameEngineCore::CreateLevel<TitleScreen>("TitleScreen");
	GameEngineCore::CreateLevel<FarmHouse>("FarmHouse");
	GameEngineCore::CreateLevel<Farm>("Farm");
	GameEngineCore::CreateLevel<BusStation>("BusStation");
	GameEngineCore::CreateLevel<PelicanTown>("PelicanTown");
	GameEngineCore::CreateLevel<Beach>("Beach");
	GameEngineCore::ChangeLevel("PelicanTown");
}
void StardewValleyCore::Update(float _Delta)
{

}
void StardewValleyCore::Render()
{

}
void StardewValleyCore::Release()
{

}