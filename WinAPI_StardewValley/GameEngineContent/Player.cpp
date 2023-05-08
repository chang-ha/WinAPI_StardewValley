#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
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
	if (false == ResourcesManager::GetInst().IsLoadTexture("Player_body_115.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Player\\Player_body\\Player_body_115.bmp");

		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}
	SetPos({ 300, 500 });
	// SetScale({ 16, 32 });
}
void Player::Update(float _Delta)
{
	AddPos({ 10.0f * _Delta, 0.0f });
}
void Player::Render()
{
	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture("Player_body_115.bmp");
	BackBuffer->BitCopy(FindTexture, GetPos());
}
void Player::Release()
{

}