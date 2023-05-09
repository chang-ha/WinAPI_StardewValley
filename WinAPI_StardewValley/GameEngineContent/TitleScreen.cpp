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
	//CreateActor<TitleBird>();
	//CreateActor<Player>();
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