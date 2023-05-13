#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/ResourcesManager.h>
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
		float4 Scale = { 16,32 };
		Ptr->SetRenderScale(Scale*3.7f);
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("Player_arm_01.bmp", RenderOrder::Play);
		//Ptr->SetRenderScale();
		Ptr->SetTexture("Player_arm_01.bmp");
		float4 Scale = { 16,32 };
		Ptr->SetRenderScale(Scale * 3.7f);
	}
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	SetPos(WinScale.Half());
}
void Player::Update(float _Delta)
{
	float Speed = 1000.0f;

	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A'))
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		MovePos = { 0.0f, Speed * _Delta };
	}
	// MousePos
	// float4 Pos = GameEngineWindow::MainWindow.GetMousePos();
	AddPos(MovePos);
	GetLevel()->GetMainCamera()->AddPos(MovePos);
}
void Player::Render()
{
}
void Player::Release()
{

}