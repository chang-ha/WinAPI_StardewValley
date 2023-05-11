#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "FarmHouse.h"
#include "BackGround.h"
#include "Player.h"
#include "PlayOver.h"

FarmHouse::FarmHouse()
{

}

FarmHouse::~FarmHouse()
{

}

void FarmHouse::Start()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->Init("farmhouse1.bmp");
	Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
	Player* Farmer = CreateActor<Player>();
	Farmer->SetPos({875,530});
	PlayOver* Over = CreateActor<PlayOver>();
	// C:\Project\WinAPI_StardewValley\WinAPI_StardewValley\Resources\Textures\Title
	Over->Init("farmhouse_bed.bmp");
	Over->Renderer->SetTexture("farmhouse_bed.bmp");
	Over->SetPos({896,589});
}
void FarmHouse::Update(float _Delta)
{

}
void FarmHouse::Render()
{

}
void FarmHouse::Release()
{

}