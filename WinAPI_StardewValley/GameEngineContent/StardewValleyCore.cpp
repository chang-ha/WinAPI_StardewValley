#include <GameEnginePlatform/GameEngineWindow.h>

#include "StardewValleyCore.h"
#include "TitleScreen.h"
StardewValleyCore::StardewValleyCore()
{

}

StardewValleyCore::~StardewValleyCore()
{

}

void StardewValleyCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 0, 0 }, { 1280, 720 });

	GameEngineCore::CreateLevel<TitleScreen>("TitleScreen");
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