#include <GameEnginePlatform/GameEngineWindow.h>

#include "StardewValleyCore.h"
#include "TitleScreen.h"
#include "FarmHouse.h"
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
	GameEngineCore::ChangeLevel("TitleScreen");
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