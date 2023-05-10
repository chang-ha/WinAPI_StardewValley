#include "TitleScreen.h"
#include "BackGround.h"
#include "Player.h"
#include "TitleBird.h"

TitleScreen::TitleScreen()
{

}

TitleScreen::~TitleScreen()
{

}

void TitleScreen::Start()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->Init("Title_background.bmp");
	TitleBird* Bird1 = CreateActor<TitleBird>();
	TitleBird* Bird2 = CreateActor<TitleBird>();
	Bird1->SetPos({ 1100, 600 });
	Bird2->SetPos({1150,650});
	Player* Farmer = CreateActor<Player>();
}
void TitleScreen::Update(float _Delta)
{

}
void TitleScreen::Render()
{

}
void TitleScreen::Release()
{

}