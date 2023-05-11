#include <GameEnginePlatform/GameEngineWindow.h>

#include "FarmHouse.h"
#include "BackGround.h"
#include "Player.h"
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