#include "TitleScreen.h"
#include "Title.h"
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
	CreateActor<Title>();
	CreateActor<TitleBird>();
	CreateActor<Player>();
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