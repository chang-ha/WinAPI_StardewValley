#include "Title.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>

Title::Title()
{

}

Title::~Title()
{

}

void Title::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Title_background.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Title\\Title_background.bmp");
		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

}

void Title::Update(float _Delta)
{

}

void Title::Render()
{
	HDC WindowDC = GameEngineWindow::MainWindow.GetHDC();
	GameEngineTexture* FindTexture = ResourcesManager::GetInst().FindTexture("Title_background.bmp");
	HDC ImageDC = FindTexture->GetImageDC();

	BitBlt(WindowDC,0,0,1920,1200,ImageDC,0,0, SRCCOPY);
}

void Title::Release()
{

}