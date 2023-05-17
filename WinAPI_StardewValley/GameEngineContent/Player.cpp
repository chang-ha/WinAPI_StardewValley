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

		// Arm Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Player_arm", FilePath.PlusFilePath("Player_arm\\Player_arm.bmp"), 9, 1);

		ResourcesManager::GetInst().CreateSpriteSheet("Player_hair", FilePath.PlusFilePath("Player_hair\\Player_hair.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Player_shirt", FilePath.PlusFilePath("Player_shirt\\Player_shirts.bmp"),9,1);
		ResourcesManager::GetInst().CreateSpriteSheet("Player_pants", FilePath.PlusFilePath("Player_pants\\Player_pants.bmp"), 9, 1);
		// ResourcesManager::GetInst().CreateSpriteFolder("Player_hat", FilePath.PlusFilePath("Player_hat"));
	}

	BodyRenderer = CreateRenderer(RenderOrder::Play);
	// HairRenderer = CreateRenderer(RenderOrder::hair);
	// ArmRenderer = CreateRenderer(RenderOrder::arm);
	// ShirtRenderer = CreateRenderer(RenderOrder::shirt);
	// PantsRenderer = CreateRenderer(RenderOrder::pants);
	// HatRenderer = CreateRenderer(RenderOrder::Equip);

	//Body
	{
		// Up
		{
			BodyRenderer->CreateAnimation("Up_Idle", "Up_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Up_Run", "Up_Player_Body", 1, 8, 0.1f);
			BodyRenderer->SetScaleRatio(3.7f);
		}
		// Down
		{
			BodyRenderer->CreateAnimation("Down_Idle", "Down_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Down_Run", "Down_Player_Body", 1, 8, 0.1f);
			BodyRenderer->SetScaleRatio(3.7f);
		}
		// Right
		{
			BodyRenderer->CreateAnimation("Right_Idle", "Right_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Right_Run", "Right_Player_Body", 1, 6, 0.1f);
			BodyRenderer->SetScaleRatio(3.7f);
			BodyRenderer->ChangeAnimation("Right_Idle");
		}
		// Left
		{
			BodyRenderer->CreateAnimation("Left_Idle", "Left_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Left_Run", "Left_Player_Body", 1, 6, 0.1f);
			BodyRenderer->SetScaleRatio(3.7f);
		}
	}

	//Arm
	{
		//Up
		//{
		//	ArmRenderer->CreateAnimation("Idle", "Player_arm", 0, 0);
		//	ArmRenderer->CreateAnimation("Run", "Player_arm", 1, 8, 0.1f);
		//	ArmRenderer->CreateAnimation("UseTool", "Player_arm", 4, 8, 0.08f);
		//	ArmRenderer->SetScaleRatio(3.7f);
		//	ArmRenderer->ChangeAnimation("Idle");
		//}
	}

	//{
	//	HairRenderer->CreateAnimation("Idle", "Player_hair", 0, 0);
	//	HairRenderer->CreateAnimation("Run", "Player_hair", 1, 8, 0.1f);
	//	HairRenderer->SetScaleRatio(3.7f);
	//	HairRenderer->SetRenderPos({ 0,-3.5f });
	//	HairRenderer->ChangeAnimation("Idle");
	//}


	//{
	//	ShirtRenderer->CreateAnimation("Idle", "Player_shirt", 0, 0);
	//	ShirtRenderer->CreateAnimation("Run", "Player_shirt", 1, 8, 0.1f);
	//	ShirtRenderer->SetRenderPos({ 0,7 });
	//	ShirtRenderer->SetScaleRatio(3.7f);
	//	ShirtRenderer->ChangeAnimation("Idle");
	//}

	//{
	//	PantsRenderer->CreateAnimation("Idle", "Player_pants", 0, 0);
	//	PantsRenderer->CreateAnimation("Run", "Player_pants", 1, 8, 0.1f);
	//	PantsRenderer->SetScaleRatio(3.7f);
	//	PantsRenderer->ChangeAnimation("Idle");
	//}

	//{
	//	HatRenderer = CreateRenderer("Player_hat_05.bmp", RenderOrder::Equip);
	//	HatRenderer->SetTexture("Player_hat_05.bmp");
	//	HatRenderer->SetRenderPos({0,-32});
	//	HatRenderer->SetRenderScale(HatRenderer->GetTextureScale() * 3.7f);
	//}

	Dir = PlayerDir::Down;
	ChangeState(PlayerState::Idle);
	// ChangeAnimationState("Idle");
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

	if (true == GameEngineInput::IsDown('A'))
	{
		CheckDir = PlayerDir::Left;
	}

	if (true == GameEngineInput::IsDown('D'))
	{
		CheckDir = PlayerDir::Right;
	}

	if (true == GameEngineInput::IsDown('W'))
	{
		CheckDir = PlayerDir::Up;
	}

	if (true == GameEngineInput::IsDown('S'))
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
	// "Idle"
	// _StateName

	std::string AnimationName;

	switch (Dir)
	{
	case PlayerDir::Up:
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

	AnimationName += _StateName;

	CurState = _StateName;

	BodyRenderer->ChangeAnimation(AnimationName);
	// ArmRenderer->ChangeAnimation(AnimationName);
}