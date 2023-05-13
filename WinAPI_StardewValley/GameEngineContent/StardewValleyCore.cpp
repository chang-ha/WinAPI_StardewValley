#include <GameEnginePlatform/GameEngineWindow.h>

#include "StardewValleyCore.h"
#include "TitleScreen.h"
#include "FarmHouse.h"
#include "Farm.h"
#include "BusStation.h"
StardewValleyCore::StardewValleyCore()
{

}

StardewValleyCore::~StardewValleyCore()
{
}

void StardewValleyCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 0, 0 }, { 1600, 900 });

	GameEngineCore::CreateLevel<TitleScreen>("TitleScreen");
	GameEngineCore::CreateLevel<FarmHouse>("FarmHouse");
	GameEngineCore::CreateLevel<Farm>("Farm");
	GameEngineCore::CreateLevel<BusStation>("BusStation");
	GameEngineCore::ChangeLevel("BusStation");
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