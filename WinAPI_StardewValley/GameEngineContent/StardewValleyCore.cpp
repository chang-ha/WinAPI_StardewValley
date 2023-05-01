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
	GameEngineCore::CreateLevel<TitleScreen>("TitleScreen");
	GameEngineCore::ChangeLevel("TitleScreen");
}
void StardewValleyCore::Update()
{

}
void StardewValleyCore::Render()
{

}
void StardewValleyCore::Release()
{

}