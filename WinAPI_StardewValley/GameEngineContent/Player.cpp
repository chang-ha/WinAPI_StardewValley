#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>

Player::Player()
{

}

Player::~Player()
{

}

void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Title_background.bmp"))
	{
		//C:\Project\WinAPI_StardewValley\WinAPI_StardewValley\Resources\Title\\Title_background.bmp
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Title\\Title_background.bmp");

		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}
	SetPos({ 200, 200 });
	SetScale({ 100, 100 });

}
void Player::Update(float _Delta)
{
	AddPos({ 100.0f * _Delta, 0.0f });
}
void Player::Render()
{
	HDC WindowDC = GameEngineWindow::MainWindow.GetHDC();
	GameEngineTexture* FindTexture = ResourcesManager::GetInst().FindTexture("Title_background.bmp");
	HDC ImageDC = FindTexture->GetImageDC();

	BitBlt(WindowDC, 0, 0, 1920, 1200, ImageDC, 0, 0, SRCCOPY);
}
void Player::Release()
{

}