#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Player.h"
#include "ContentsEnum.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Player_body_01.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Player\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_body\\Player_body_01.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_arm\\Player_arm_01.bmp"));
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("Player_body_01.bmp", RenderOrder::Play);
		//Ptr->SetRenderScale();
		Ptr->SetTexture("Player_body_01.bmp");
		Ptr->SetRenderScale({48,96});
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("Player_arm_01.bmp", RenderOrder::Play);
		//Ptr->SetRenderScale();
		Ptr->SetTexture("Player_arm_01.bmp");
		Ptr->SetRenderScale({ 48,96 });
	}
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	SetPos(WinScale.Half());
}
void Player::Update(float _Delta)
{
	float Speed = 200.0f;

	float4 MovePos = float4::ZERO;

	if (0 != GetAsyncKeyState('A'))
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}

	if (0 != GetAsyncKeyState('D'))
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (0 != GetAsyncKeyState('W'))
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}

	if (0 != GetAsyncKeyState('S'))
	{
		MovePos = { 0.0f, Speed * _Delta };
	}

	AddPos(MovePos);
	GetLevel()->GetMainCamera()->AddPos(MovePos);
}
void Player::Render()
{
}
void Player::Release()
{

}