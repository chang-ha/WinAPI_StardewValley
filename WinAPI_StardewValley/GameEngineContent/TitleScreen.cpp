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
	Player* Farmer = CreateActor<Player>();
	TitleBird* Bird1 = CreateActor<TitleBird>();
	TitleBird* Bird2 = CreateActor<TitleBird>();
	Bird1->SetPos({ 1050, 500 });
	Bird2->SetPos({1150,575});
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