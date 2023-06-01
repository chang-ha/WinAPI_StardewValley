#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/TileMap.h>

#include "Player.h"
#include "ContentLevel.h"
#include "ContentsEnum.h"
#include "ContentUIManager.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
{

}

Player::~Player()
{

}

void Player::LevelStart()
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
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_body_Tool1", FilePath.PlusFilePath("Player_body\\Up_Player_body_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_body_Tool1", FilePath.PlusFilePath("Player_body\\Down_Player_body_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_body_Tool1", FilePath.PlusFilePath("Player_body\\Right_Player_body_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_body_Tool1", FilePath.PlusFilePath("Player_body\\Left_Player_body_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_body_Tool2", FilePath.PlusFilePath("Player_body\\Down_Player_body_Tool2.bmp"), 3, 1);		
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_body_Tool2", FilePath.PlusFilePath("Player_body\\Right_Player_body_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_body_Tool2", FilePath.PlusFilePath("Player_body\\Left_Player_body_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_body_Tool2", FilePath.PlusFilePath("Player_body\\Up_Player_body_Tool2.bmp"), 3, 1);

		// Pants Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Pants", FilePath.PlusFilePath("Player_pants\\Up_Player_pants1.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Pants", FilePath.PlusFilePath("Player_pants\\Down_Player_pants1.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Pants", FilePath.PlusFilePath("Player_pants\\Right_Player_pants1.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Pants", FilePath.PlusFilePath("Player_pants\\Left_Player_pants1.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Pants_Tool1", FilePath.PlusFilePath("Player_pants\\Down_Player_pants1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Pants_Tool1", FilePath.PlusFilePath("Player_pants\\Right_Player_pants1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Pants_Tool1", FilePath.PlusFilePath("Player_pants\\Left_Player_pants1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Pants_Tool1", FilePath.PlusFilePath("Player_pants\\Up_Player_pants1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Pants_Tool2", FilePath.PlusFilePath("Player_pants\\Down_Player_pants1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Pants_Tool2", FilePath.PlusFilePath("Player_pants\\Right_Player_pants1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Pants_Tool2", FilePath.PlusFilePath("Player_pants\\Left_Player_pants1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Pants_Tool2", FilePath.PlusFilePath("Player_pants\\Up_Player_pants1_Tool2.bmp"), 3, 1);

		// Shirt Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Shirt", FilePath.PlusFilePath("Player_shirt\\Up_Player_shirt1.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Shirt", FilePath.PlusFilePath("Player_shirt\\Down_Player_shirt1.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Shirt", FilePath.PlusFilePath("Player_shirt\\Right_Player_shirt1.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Shirt", FilePath.PlusFilePath("Player_shirt\\Left_Player_shirt1.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Shirt_Tool1", FilePath.PlusFilePath("Player_shirt\\Down_Player_shirt1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Shirt_Tool1", FilePath.PlusFilePath("Player_shirt\\Right_Player_shirt1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Shirt_Tool1", FilePath.PlusFilePath("Player_shirt\\Left_Player_shirt1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Shirt_Tool1", FilePath.PlusFilePath("Player_shirt\\Up_Player_shirt1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Shirt_Tool2", FilePath.PlusFilePath("Player_shirt\\Down_Player_shirt1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Shirt_Tool2", FilePath.PlusFilePath("Player_shirt\\Right_Player_shirt1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Shirt_Tool2", FilePath.PlusFilePath("Player_shirt\\Left_Player_shirt1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Shirt_Tool2", FilePath.PlusFilePath("Player_shirt\\Up_Player_shirt1_Tool2.bmp"), 3, 1);

		// Arm Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_arm", FilePath.PlusFilePath("Player_arm\\Up_Player_arm.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_arm", FilePath.PlusFilePath("Player_arm\\Down_Player_arm.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_arm", FilePath.PlusFilePath("Player_arm\\Right_Player_arm.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_arm", FilePath.PlusFilePath("Player_arm\\Left_Player_arm.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_arm_Tool1", FilePath.PlusFilePath("Player_arm\\Down_Player_arm_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_arm_Tool1", FilePath.PlusFilePath("Player_arm\\Right_Player_arm_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_arm_Tool1", FilePath.PlusFilePath("Player_arm\\Left_Player_arm_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_arm_Tool1", FilePath.PlusFilePath("Player_arm\\Up_Player_arm_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_arm_Tool2", FilePath.PlusFilePath("Player_arm\\Down_Player_arm_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_arm_Tool2", FilePath.PlusFilePath("Player_arm\\Right_Player_arm_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_arm_Tool2", FilePath.PlusFilePath("Player_arm\\Left_Player_arm_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_arm_Tool2", FilePath.PlusFilePath("Player_arm\\Up_Player_arm_Tool2.bmp"), 3, 1);

		// Hair Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_hair", FilePath.PlusFilePath("Player_hair\\Up_Player_hair1.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_hair", FilePath.PlusFilePath("Player_hair\\Down_Player_hair1.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_hair", FilePath.PlusFilePath("Player_hair\\Right_Player_hair1.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_hair", FilePath.PlusFilePath("Player_hair\\Left_Player_hair1.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_hair_Tool1", FilePath.PlusFilePath("Player_hair\\Down_Player_hair1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_hair_Tool1", FilePath.PlusFilePath("Player_hair\\Right_Player_hair1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_hair_Tool1", FilePath.PlusFilePath("Player_hair\\Left_Player_hair1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_hair_Tool1", FilePath.PlusFilePath("Player_hair\\Up_Player_hair1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_hair_Tool2", FilePath.PlusFilePath("Player_hair\\Down_Player_hair1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_hair_Tool2", FilePath.PlusFilePath("Player_hair\\Right_Player_hair1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_hair_Tool2", FilePath.PlusFilePath("Player_hair\\Left_Player_hair1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_hair_Tool2", FilePath.PlusFilePath("Player_hair\\Up_Player_hair1_Tool2.bmp"), 3, 1);

		// ResourcesManager::GetInst().CreateSpriteFolder("Player_hat", FilePath.PlusFilePath("Player_hat"));
	}

	// Sound Load
	if (nullptr == GameEngineSound::FindSound("grassyStep.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("grassyStep.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("woodyStep.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("sandyStep.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("stoneStep.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("thudStep.wav"));
	}

	// Player Renderer 
	BodyRenderer = CreateRenderer(RenderOrder::Play);
	BodyRenderer->SetScaleRatio(RENDERRATIO);

	PantsRenderer = CreateRenderer(RenderOrder::Pants);
	PantsRenderer->SetScaleRatio(RENDERRATIO);

	ShirtRenderer = CreateRenderer(RenderOrder::Shirt);
	ShirtRenderer->SetScaleRatio(RENDERRATIO);
	
	ArmRenderer = CreateRenderer(RenderOrder::Arm);
	ArmRenderer->SetScaleRatio(RENDERRATIO);

	HairRenderer = CreateRenderer(RenderOrder::Hair);
	HairRenderer->SetScaleRatio(RENDERRATIO);

	// HatRenderer = CreateRenderer(RenderOrder::Hat);
	
	// Body
	{
		// Up
		{
			BodyRenderer->CreateAnimation("Up_Idle", "Up_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Up_Run", "Up_Player_Body", 1, 8, 0.08f);
			BodyRenderer->CreateAnimation("Up_Tool1", "Up_Player_body_Tool1", 0, 4, TOOL1SPEED, false);
			BodyRenderer->CreateAnimation("Up_Tool2", "Up_Player_body_Tool2", 0, 2, TOOL2SPEED, false);
			BodyRenderer->FindAnimation("Up_Tool2")->Inters[2] = 1.0f;
		}

		// Down
		{
			BodyRenderer->CreateAnimation("Down_Idle", "Down_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Down_Run", "Down_Player_Body", 1, 8, 0.08f);
			BodyRenderer->CreateAnimation("Down_Tool1", "Down_Player_body_Tool1", 0, 4, TOOL1SPEED, false);
			BodyRenderer->CreateAnimation("Down_Tool2", "Down_Player_body_Tool2", 0, 2, TOOL2SPEED, false);
			BodyRenderer->FindAnimation("Down_Tool2")->Inters[2] = 1.0f;
		}
		
		// Right
		{
			BodyRenderer->CreateAnimation("Right_Idle", "Right_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Right_Run", "Right_Player_Body", 1, 6, 0.1f);
			BodyRenderer->CreateAnimation("Right_Tool1", "Right_Player_body_Tool1", 0, 4, TOOL1SPEED, false);
			BodyRenderer->CreateAnimation("Right_Tool2", "Right_Player_body_Tool2", 0, 2, TOOL2SPEED, false);
			BodyRenderer->FindAnimation("Right_Tool2")->Inters[2] = 1.0f;
		}
		
		// Left
		{
			BodyRenderer->CreateAnimation("Left_Idle", "Left_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Left_Run", "Left_Player_Body", 1, 6, 0.1f);
			BodyRenderer->CreateAnimation("Left_Tool1", "Left_Player_body_Tool1", 0, 4, TOOL1SPEED, false);
			BodyRenderer->CreateAnimation("Left_Tool2", "Left_Player_body_Tool2", 0, 2, TOOL2SPEED, false);
			BodyRenderer->FindAnimation("Left_Tool2")->Inters[2] = 1.0f;
		}
	}

	// Pants
	{
		//Up
		{
			PantsRenderer->CreateAnimation("Up_Idle", "Up_Player_Pants", 0, 0);
			PantsRenderer->CreateAnimation("Up_Run", "Up_Player_Pants", 1, 8, 0.08f);
			PantsRenderer->CreateAnimation("Up_Tool1", "Up_Player_Pants_Tool1", 0, 4, TOOL1SPEED, false);
			PantsRenderer->CreateAnimation("Up_Tool2", "Up_Player_Pants_Tool2", 0, 2, TOOL2SPEED, false);
			PantsRenderer->FindAnimation("Up_Tool2")->Inters[2] = 1.0f;
		}

		//Down
		{
			PantsRenderer->CreateAnimation("Down_Idle", "Down_Player_Pants", 0, 0);
			PantsRenderer->CreateAnimation("Down_Run", "Down_Player_Pants", 1, 8, 0.08f);
			PantsRenderer->CreateAnimation("Down_Tool1", "Down_Player_Pants_Tool1", 0, 4, TOOL1SPEED, false);
			PantsRenderer->CreateAnimation("Down_Tool2", "Down_Player_Pants_Tool2", 0, 2, TOOL2SPEED, false);
			PantsRenderer->FindAnimation("Down_Tool2")->Inters[2] = 1.0f;
		}

		//Right
		{
			PantsRenderer->CreateAnimation("Right_Idle", "Right_Player_Pants", 0, 0);
			PantsRenderer->CreateAnimation("Right_Run", "Right_Player_Pants", 1, 6, 0.1f);
			PantsRenderer->CreateAnimation("Right_Tool1", "Right_Player_Pants_Tool1", 0, 4, TOOL1SPEED, false);
			PantsRenderer->CreateAnimation("Right_Tool2", "Right_Player_Pants_Tool2", 0, 2, TOOL2SPEED, false);
			PantsRenderer->FindAnimation("Right_Tool2")->Inters[2] = 1.0f;
		}

		//Left
		{
			PantsRenderer->CreateAnimation("Left_Idle", "Left_Player_Pants", 0, 0);
			PantsRenderer->CreateAnimation("Left_Run", "Left_Player_Pants", 1, 6, 0.1f);
			PantsRenderer->CreateAnimation("Left_Tool1", "Left_Player_Pants_Tool1", 0, 4, TOOL1SPEED, false);
			PantsRenderer->CreateAnimation("Left_Tool2", "Left_Player_Pants_Tool2", 0, 2, TOOL2SPEED, false);
			PantsRenderer->FindAnimation("Left_Tool2")->Inters[2] = 1.0f;
		}
	}

	// Shirt
	{
		//Up
		{
			ShirtRenderer->CreateAnimation("Up_Idle", "Up_Player_Shirt", 0, 0);
			ShirtRenderer->CreateAnimation("Up_Run", "Up_Player_Shirt", 1, 8, 0.08f);
			ShirtRenderer->CreateAnimation("Up_Tool1", "Up_Player_Shirt_Tool1", 0, 4, TOOL1SPEED, false);
			ShirtRenderer->CreateAnimation("Up_Tool2", "Up_Player_Shirt_Tool2", 0, 2, TOOL2SPEED, false);
			ShirtRenderer->FindAnimation("Up_Tool2")->Inters[2] = 1.0f;
		}

		//Down
		{
			ShirtRenderer->CreateAnimation("Down_Idle", "Down_Player_Shirt", 0, 0);
			ShirtRenderer->CreateAnimation("Down_Run", "Down_Player_Shirt", 1, 8, 0.08f);
			ShirtRenderer->CreateAnimation("Down_Tool1", "Down_Player_Shirt_Tool1", 0, 4, TOOL1SPEED, false);
			ShirtRenderer->CreateAnimation("Down_Tool2", "Down_Player_Shirt_Tool2", 0, 2, TOOL2SPEED, false);
			ShirtRenderer->FindAnimation("Down_Tool2")->Inters[2] = 1.0f;
		}

		//Right
		{
			ShirtRenderer->CreateAnimation("Right_Idle", "Right_Player_Shirt", 0, 0);
			ShirtRenderer->CreateAnimation("Right_Run", "Right_Player_Shirt", 1, 6, 0.1f);
			ShirtRenderer->CreateAnimation("Right_Tool1", "Right_Player_Shirt_Tool1", 0, 4, TOOL1SPEED, false);
			ShirtRenderer->CreateAnimation("Right_Tool2", "Right_Player_Shirt_Tool2", 0, 2, TOOL2SPEED, false);
			ShirtRenderer->FindAnimation("Right_Tool2")->Inters[2] = 1.0f;
		}

		//Left
		{
			ShirtRenderer->CreateAnimation("Left_Idle", "Left_Player_Shirt", 0, 0);
			ShirtRenderer->CreateAnimation("Left_Run", "Left_Player_Shirt", 1, 6, 0.1f);
			ShirtRenderer->CreateAnimation("Left_Tool1", "Left_Player_Shirt_Tool1", 0, 4, TOOL1SPEED, false);
			ShirtRenderer->CreateAnimation("Left_Tool2", "Left_Player_Shirt_Tool2", 0, 2, TOOL2SPEED, false);
			ShirtRenderer->FindAnimation("Left_Tool2")->Inters[2] = 1.0f;
		}
	}
	
	// Arm
	{
		// Up
		{
			ArmRenderer->CreateAnimation("Up_Idle", "Up_Player_arm", 0, 0);
			ArmRenderer->CreateAnimation("Up_Run", "Up_Player_arm", 1, 8, 0.08f);
			ArmRenderer->CreateAnimation("Up_Tool1", "Up_Player_arm_Tool1", 0, 4, TOOL1SPEED, false);
			ArmRenderer->CreateAnimation("Up_Tool2", "Up_Player_arm_Tool2", 0, 2, TOOL2SPEED, false);
			ArmRenderer->FindAnimation("Up_Tool2")->Inters[2] = 1.0f;
		}

		// Down
		{
			ArmRenderer->CreateAnimation("Down_Idle", "Down_Player_arm", 0, 0);
			ArmRenderer->CreateAnimation("Down_Run", "Down_Player_arm", 1, 8, 0.08f);
			ArmRenderer->CreateAnimation("Down_Tool1", "Down_Player_arm_Tool1", 0, 4, TOOL1SPEED, false);
			ArmRenderer->CreateAnimation("Down_Tool2", "Down_Player_arm_Tool2", 0, 2, TOOL2SPEED, false);
			ArmRenderer->FindAnimation("Down_Tool2")->Inters[2] = 1.0f;
		}

		// Right
		{
			ArmRenderer->CreateAnimation("Right_Idle", "Right_Player_arm", 0, 0);
			ArmRenderer->CreateAnimation("Right_Run", "Right_Player_arm", 1, 6, 0.1f);
			ArmRenderer->CreateAnimation("Right_Tool1", "Right_Player_arm_Tool1", 0, 4, TOOL1SPEED, false);
			ArmRenderer->CreateAnimation("Right_Tool2", "Right_Player_arm_Tool2", 0, 2, TOOL2SPEED, false);
			ArmRenderer->FindAnimation("Right_Tool2")->Inters[2] = 1.0f;
		}

		// Left
		{
			ArmRenderer->CreateAnimation("Left_Idle", "Left_Player_arm", 0, 0);
			ArmRenderer->CreateAnimation("Left_Run", "Left_Player_arm", 1, 6, 0.1f);
			ArmRenderer->CreateAnimation("Left_Tool1", "Left_Player_arm_Tool1", 0, 4, TOOL1SPEED, false);
			ArmRenderer->CreateAnimation("Left_Tool2", "Left_Player_arm_Tool2", 0, 2, TOOL2SPEED, false);
			ArmRenderer->FindAnimation("Left_Tool2")->Inters[2] = 1.0f;
		}
	}

	// Hair
	{
		//Up
		{
			HairRenderer->CreateAnimation("Up_Idle", "Up_Player_hair", 0, 0);
			HairRenderer->CreateAnimation("Up_Run", "Up_Player_hair", 1, 8, 0.08f);
			HairRenderer->CreateAnimation("Up_Tool1", "Up_Player_hair_Tool1", 0, 4, TOOL1SPEED, false);
			HairRenderer->CreateAnimation("Up_Tool2", "Up_Player_hair_Tool2", 0, 2, TOOL2SPEED, false);
			HairRenderer->FindAnimation("Up_Tool2")->Inters[2] = 1.0f;
		}

		//Down
		{
			HairRenderer->CreateAnimation("Down_Idle", "Down_Player_hair", 0, 0);
			HairRenderer->CreateAnimation("Down_Run", "Down_Player_hair", 1, 8, 0.08f);
			HairRenderer->CreateAnimation("Down_Tool1", "Down_Player_hair_Tool1", 0, 4, TOOL1SPEED, false);
			HairRenderer->CreateAnimation("Down_Tool2", "Down_Player_hair_Tool2", 0, 2, TOOL2SPEED, false);
			HairRenderer->FindAnimation("Down_Tool2")->Inters[2] = 1.0f;
		}

		//Right
		{
			HairRenderer->CreateAnimation("Right_Idle", "Right_Player_hair", 0, 0);
			HairRenderer->CreateAnimation("Right_Run", "Right_Player_hair", 1, 6, 0.1f);
			HairRenderer->CreateAnimation("Right_Tool1", "Right_Player_hair_Tool1", 0, 4, TOOL1SPEED, false);
			HairRenderer->CreateAnimation("Right_Tool2", "Right_Player_hair_Tool2", 0, 2, TOOL2SPEED, false);
			HairRenderer->FindAnimation("Right_Tool2")->Inters[2] = 1.0f;
		}

		//Left
		{
			HairRenderer->CreateAnimation("Left_Idle", "Left_Player_hair", 0, 0);
			HairRenderer->CreateAnimation("Left_Run", "Left_Player_hair", 1, 6, 0.1f);
			HairRenderer->CreateAnimation("Left_Tool1", "Left_Player_hair_Tool1", 0, 4, TOOL1SPEED, false);
			HairRenderer->CreateAnimation("Left_Tool2", "Left_Player_hair_Tool2", 0, 2, TOOL2SPEED, false);
			HairRenderer->FindAnimation("Left_Tool2")->Inters[2] = 1.0f;
		}
	}

	//{
	//	HatRenderer = CreateRenderer("Player_hat_05.bmp", RenderOrder::Equip);
	//	HatRenderer->SetTexture("Player_hat_05.bmp");
	//	HatRenderer->SetRenderPos({0,-32});
	//	HatRenderer->SetRenderScale(HatRenderer->GetTextureScale() * 3.7f);
	//}

	// Player Collision
	UpCollision = { 0, 8 * RENDERRATIO };
	LeftCollision = { -8 * RENDERRATIO, 12 * RENDERRATIO };
	RightCollision = { 8 * RENDERRATIO, 12 * RENDERRATIO };
	DownCollision = { 0 , 16 * RENDERRATIO };

	Dir = PlayerDir::Right;
	ChangeState(PlayerState::Idle);
}

void Player::Update(float _Delta)
{
	StateUpdate(_Delta);
	if (true == GameEngineInput::IsDown('P'))
	{
		CollisionDebug = !CollisionDebug;
	}

	if (true == GameEngineInput::IsDown(VK_F2))
	{
		FPS = !FPS;
	}
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Run:
		return RunUpdate(_Delta);
	case PlayerState::Tool:
		return ToolUpdate(_Delta);
	case PlayerState::Tool2:
		return ToolUpdate(_Delta);
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
		case PlayerState::Tool:
			ToolStart();
			break;
		case PlayerState::Tool2:
			Tool2Start();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Player::DirCheck()
{
	int CheckDir = PlayerDir::Null;
	bool ChangeDir = false;

	if (true == GameEngineInput::IsPress('A'))
	{
		CheckDir += PlayerDir::Left;
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		CheckDir += PlayerDir::Right;
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		CheckDir += PlayerDir::Up;
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		CheckDir += PlayerDir::Down;
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

void Player::ToolDirCheck()
{
	float4 MousePos = PlayLevel->GetMainMouse()->GetPos();
	if (GetPos().X - MousePos.X > 16 * RENDERRATIO)
	{
		Dir = PlayerDir::Left;
	}
	else if (GetPos().X - MousePos.X < -16 * RENDERRATIO)
	{
		Dir = PlayerDir::Right;
	}
	else if (GetPos().Y - MousePos.Y > 0)
	{
		Dir = PlayerDir::Up;
	}
	else if (GetPos().Y - MousePos.Y < 0 )
	{
		Dir = PlayerDir::Down;
	}
}

float4 Player::TileLimit(TileMap* _CurTile)
{
	float4 Index = _CurTile->PosToIndex(PlayLevel->GetMainMouse()->GetPos());
	float4 FarmerIndex = _CurTile->PosToIndex(GetPos() + DownCollision);

	if (Index.iX() <= FarmerIndex.iX() - 1)
	{
		Index.X = FarmerIndex.X - 1.0f;
		if (Index.iY() <= FarmerIndex.iY() - 1)
		{
			Index.Y = FarmerIndex.Y - 1.0f;
		}
		else if (Index.iY() >= FarmerIndex.iY() + 1)
		{
			Index.Y = FarmerIndex.Y + 1.0f;
		}
		else
		{
			Index.Y = FarmerIndex.Y;
		}
	}
	else if (Index.iX() >= FarmerIndex.iX() + 1)
	{
		Index.X = FarmerIndex.X + 1.0f;
		if (Index.iY() <= FarmerIndex.iY() - 1)
		{
			Index.Y = FarmerIndex.Y - 1.0f;
		}
		else if (Index.iY() >= FarmerIndex.iY() + 1)
		{
			Index.Y = FarmerIndex.Y + 1.0f;
		}
		else
		{
			Index.Y = FarmerIndex.Y;
		}
	}
	else
	{
		Index.X = FarmerIndex.X;
		if (Index.iY() <= FarmerIndex.iY() - 1)
		{
			Index.Y = FarmerIndex.Y - 1.0f;
		}
		else if (Index.iY() >= FarmerIndex.iY() + 1)
		{
			Index.Y = FarmerIndex.Y + 1.0f;
		}
		else
		{
			Index.Y = FarmerIndex.Y;
		}
	}
	return Index;
}

void Player::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	if (PlayerDir::Right == (Dir & PlayerDir::Right))
	{
		AnimationName = "Right_";
	}
	else if (PlayerDir::Left == (Dir & PlayerDir::Left))
	{
		AnimationName = "Left_";
	}
	else if (PlayerDir::Up == (Dir & PlayerDir::Up))
	{
		AnimationName = "Up_";
	}
	else if (PlayerDir::Down == (Dir & PlayerDir::Down))
	{
		AnimationName = "Down_";
	}

	// ShirtPos Setting
	ShirtRenderer->SetRenderPos({ 0, 2 * RENDERRATIO });

	// Animation Change
	AnimationName += _StateName;
	CurState = _StateName;
	BodyRenderer->ChangeAnimation(AnimationName);
	PantsRenderer->ChangeAnimation(AnimationName);
	ShirtRenderer->ChangeAnimation(AnimationName);
	ArmRenderer->ChangeAnimation(AnimationName);
	HairRenderer->ChangeAnimation(AnimationName);
}

void Player::Render(float _Delta)
{
	if (true == CollisionDebug)
	{
		HDC handle = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

		CollisionData PlayerCollision;
		PlayerCollision.Pos = WindowActorPos();
		PlayerCollision.Scale = { 4,4 };
		PlayerCollision.Pos = WindowActorPos() + UpCollision;
		Rectangle(handle, PlayerCollision.iLeft(), PlayerCollision.iTop(), PlayerCollision.iRight(), PlayerCollision.iBot());

		PlayerCollision.Pos = WindowActorPos() + RightCollision;
		Rectangle(handle, PlayerCollision.iLeft(), PlayerCollision.iTop(), PlayerCollision.iRight(), PlayerCollision.iBot());

		PlayerCollision.Pos = WindowActorPos() + LeftCollision;
		Rectangle(handle, PlayerCollision.iLeft(), PlayerCollision.iTop(), PlayerCollision.iRight(), PlayerCollision.iBot());

		PlayerCollision.Pos = WindowActorPos() + DownCollision;
		Rectangle(handle, PlayerCollision.iLeft(), PlayerCollision.iTop(), PlayerCollision.iRight(), PlayerCollision.iBot());
	}
}
