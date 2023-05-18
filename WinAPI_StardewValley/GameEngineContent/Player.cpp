﻿#include <GameEngineBase/GameEngineTime.h>
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
	if (false == ResourcesManager::GetInst().IsLoadTexture("Up_Player_Body.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Player\\");

		// Body Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Body", FilePath.PlusFilePath("Player_body\\Up_Player_Body.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Body", FilePath.PlusFilePath("Player_body\\Down_Player_Body.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Body", FilePath.PlusFilePath("Player_body\\Right_Player_Body.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Body", FilePath.PlusFilePath("Player_body\\Left_Player_Body.bmp"), 7, 1);

		// Pants Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Pants", FilePath.PlusFilePath("Player_pants\\Up_Player_pants.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Pants", FilePath.PlusFilePath("Player_pants\\Down_Player_pants.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Pants", FilePath.PlusFilePath("Player_pants\\Right_Player_pants.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Pants", FilePath.PlusFilePath("Player_pants\\Left_Player_pants.bmp"), 7, 1);

		// Shirt Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Shirt", FilePath.PlusFilePath("Player_shirt\\Up_Player_shirt.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Shirt", FilePath.PlusFilePath("Player_shirt\\Down_Player_shirt.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Shirt", FilePath.PlusFilePath("Player_shirt\\Right_Player_shirt.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Shirt", FilePath.PlusFilePath("Player_shirt\\Left_Player_shirt.bmp"), 7, 1);

		// Arm Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_arm", FilePath.PlusFilePath("Player_arm\\Up_Player_arm.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_arm", FilePath.PlusFilePath("Player_arm\\Down_Player_arm.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_arm", FilePath.PlusFilePath("Player_arm\\Right_Player_arm.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_arm", FilePath.PlusFilePath("Player_arm\\Left_Player_arm.bmp"), 7, 1);

		// ResourcesManager::GetInst().CreateSpriteSheet("Player_hair", FilePath.PlusFilePath("Player_hair\\Player_hair.bmp"), 9, 1);
		// ResourcesManager::GetInst().CreateSpriteFolder("Player_hat", FilePath.PlusFilePath("Player_hat"));
	}

	BodyRenderer = CreateRenderer(RenderOrder::Play);
	BodyRenderer->SetScaleRatio(3.7f);

	PantsRenderer = CreateRenderer(RenderOrder::pants);
	PantsRenderer->SetScaleRatio(3.7f);

	ShirtRenderer = CreateRenderer(RenderOrder::shirt);
	ShirtRenderer->SetScaleRatio(3.7f);
	
	ArmRenderer = CreateRenderer(RenderOrder::arm);
	ArmRenderer->SetScaleRatio(3.7f);

	// HairRenderer = CreateRenderer(RenderOrder::hair);
	// HatRenderer = CreateRenderer(RenderOrder::Equip);

	// Body
	{
		// Up
		{
			BodyRenderer->CreateAnimation("Up_Idle", "Up_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Up_Run", "Up_Player_Body", 1, 8, 0.08f);
		}
		// Down
		{
			BodyRenderer->CreateAnimation("Down_Idle", "Down_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Down_Run", "Down_Player_Body", 1, 8, 0.08f);
		}
		// Right
		{
			BodyRenderer->CreateAnimation("Right_Idle", "Right_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Right_Run", "Right_Player_Body", 1, 6, 0.1f);
		}
		// Left
		{
			BodyRenderer->CreateAnimation("Left_Idle", "Left_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Left_Run", "Left_Player_Body", 1, 6, 0.1f);
		}
	}

	// Pants
	{
		//Up
		{
			PantsRenderer->CreateAnimation("Up_Idle", "Up_Player_Pants", 0, 0);
			PantsRenderer->CreateAnimation("Up_Run", "Up_Player_Pants", 1, 8, 0.08f);
		}

		//Down
		{
			PantsRenderer->CreateAnimation("Down_Idle", "Down_Player_Pants", 0, 0);
			PantsRenderer->CreateAnimation("Down_Run", "Down_Player_Pants", 1, 8, 0.08f);
		}

		//Right
		{
			PantsRenderer->CreateAnimation("Right_Idle", "Right_Player_Pants", 0, 0);
			PantsRenderer->CreateAnimation("Right_Run", "Right_Player_Pants", 1, 6, 0.1f);
		}

		//Left
		{
			PantsRenderer->CreateAnimation("Left_Idle", "Left_Player_Pants", 0, 0);
			PantsRenderer->CreateAnimation("Left_Run", "Left_Player_Pants", 1, 6, 0.1f);
		}
	}

	// Shirt
	{
		// ShirtRenderer->SetRenderPos({0, 6});
		//Up
		{
			ShirtRenderer->CreateAnimation("Up_Idle", "Up_Player_Shirt", 0, 0);
			ShirtRenderer->CreateAnimation("Up_Run", "Up_Player_Shirt", 1, 8, 0.08f);
		}

		//Down
		{
			ShirtRenderer->CreateAnimation("Down_Idle", "Down_Player_Shirt", 0, 0);
			ShirtRenderer->CreateAnimation("Down_Run", "Down_Player_Shirt", 1, 8, 0.08f);
		}

		//Right
		{
			ShirtRenderer->CreateAnimation("Right_Idle", "Right_Player_Shirt", 0, 0);
			ShirtRenderer->CreateAnimation("Right_Run", "Right_Player_Shirt", 1, 6, 0.1f);
		}

		//Left
		{
			ShirtRenderer->CreateAnimation("Left_Idle", "Left_Player_Shirt", 0, 0);
			ShirtRenderer->CreateAnimation("Left_Run", "Left_Player_Shirt", 1, 6, 0.1f);
		}
	}
	
	// Arm
	{
		// Up
		{
			ArmRenderer->CreateAnimation("Up_Idle", "Up_Player_arm", 0, 0);
			ArmRenderer->CreateAnimation("Up_Run", "Up_Player_arm", 1, 8, 0.08f);
		}

		// Down
		{
			ArmRenderer->CreateAnimation("Down_Idle", "Down_Player_arm", 0, 0);
			ArmRenderer->CreateAnimation("Down_Run", "Down_Player_arm", 1, 8, 0.08f);
		}

		// Right
		{
			ArmRenderer->CreateAnimation("Right_Idle", "Right_Player_arm", 0, 0);
			ArmRenderer->CreateAnimation("Right_Run", "Right_Player_arm", 1, 6, 0.1f);
		}

		// Left
		{
			ArmRenderer->CreateAnimation("Left_Idle", "Left_Player_arm", 0, 0);
			ArmRenderer->CreateAnimation("Left_Run", "Left_Player_arm", 1, 6, 0.1f);
		}
		//ArmRenderer->CreateAnimation("UseTool", "Player_arm", 4, 8, 0.08f);
	}

	//{
	//	HairRenderer->CreateAnimation("Idle", "Player_hair", 0, 0);
	//	HairRenderer->CreateAnimation("Run", "Player_hair", 1, 8, 0.1f);
	//	HairRenderer->SetScaleRatio(3.7f);
	//	HairRenderer->SetRenderPos({ 0,-3.5f });
	//	HairRenderer->ChangeAnimation("Idle");
	//}

	//{
	//	HatRenderer = CreateRenderer("Player_hat_05.bmp", RenderOrder::Equip);
	//	HatRenderer->SetTexture("Player_hat_05.bmp");
	//	HatRenderer->SetRenderPos({0,-32});
	//	HatRenderer->SetRenderScale(HatRenderer->GetTextureScale() * 3.7f);
	//}

	Dir = PlayerDir::Right;
	ChangeState(PlayerState::Idle);
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	SetPos(WinScale.Half());
}

void Player::Update(float _DeltaTime)
{
	StateUpdate(_DeltaTime);
}

void Player::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_DeltaTime);
	case PlayerState::Run:
		return RunUpdate(_DeltaTime);
	case PlayerState::UseTool:
		return UseToolUpdate(_DeltaTime);
	default:
		break;
	}
}

void Player::ChangeState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		case PlayerState::UseTool:
			UseToolStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Player::DirCheck()
{
	PlayerDir CheckDir = PlayerDir::Null;
	bool ChangeDir = false;

	if (true == GameEngineInput::IsPress('A'))
	{
		CheckDir = PlayerDir::Left;
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		CheckDir = PlayerDir::Right;
	}
	
	if (true == GameEngineInput::IsPress('W'))
	{
		CheckDir = PlayerDir::Up;
	}
	
	if (true == GameEngineInput::IsPress('S'))
	{
		CheckDir = PlayerDir::Down;
	}

	if (PlayerDir::Null != CheckDir)
	{
		Dir = CheckDir;
		ChangeDir = true;
	}

	if (PlayerDir::Null != CheckDir && true == ChangeDir)
	{
		ChangeAnimationState(CurState);
	}
}

void Player::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;
	float4 ShirtPos = { 0, 2 };
	switch (Dir)
	{
	case PlayerDir::Up:
		ShirtPos = { 0 ,1 };
		AnimationName = "Up_";
		break;
	case PlayerDir::Down:
		AnimationName = "Down_";
		break;
	case PlayerDir::Right:
		AnimationName = "Right_";
		break;
	case PlayerDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	ShirtPos *= 3;
	ShirtRenderer->SetRenderPos(ShirtPos);
	AnimationName += _StateName;

	CurState = _StateName;

	BodyRenderer->ChangeAnimation(AnimationName);
	PantsRenderer->ChangeAnimation(AnimationName);
	ShirtRenderer->ChangeAnimation(AnimationName);
	ArmRenderer->ChangeAnimation(AnimationName);
}