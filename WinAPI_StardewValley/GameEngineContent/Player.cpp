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
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Player\\");
		ResourcesManager::GetInst().CreateSpriteSheet("Player_hair", FilePath.PlusFilePath("Player_hair\\Player_hair.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteFolder("Player_body", FilePath.PlusFilePath("Player_body"));
		ResourcesManager::GetInst().CreateSpriteFolder("Player_arm", FilePath.PlusFilePath("Player_arm"));
		ResourcesManager::GetInst().CreateSpriteSheet("Player_shirt", FilePath.PlusFilePath("Player_shirt\\Player_shirts.bmp"),4,1);
		ResourcesManager::GetInst().CreateSpriteSheet("Player_pants", FilePath.PlusFilePath("Player_pants\\Player_pants.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteFolder("Player_hat", FilePath.PlusFilePath("Player_hat"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_hair\\Player_hair_75.bmp"));

	}
		BodyRenderer = CreateRenderer(RenderOrder::Play);
		HairRenderer = CreateRenderer(RenderOrder::Play);
		ArmRenderer = CreateRenderer(RenderOrder::Play);
		ShirtRenderer = CreateRenderer(RenderOrder::Equip);
		PantsRenderer = CreateRenderer(RenderOrder::Equip);
		// HatRenderer = CreateRenderer(RenderOrder::Equip);s

	{
		BodyRenderer->CreateAnimation("Idle", "Player_body", 0, 0);
		BodyRenderer->CreateAnimation("Run", "Player_body", 0, 3, 0.2f);
		BodyRenderer->SetScaleRatio(3.7f);
		BodyRenderer->ChangeAnimation("Idle");
	}

	{
		HairRenderer->CreateAnimation("Idle", "Player_hair", 0, 0);
		HairRenderer->CreateAnimation("Run", "Player_hair", 0, 3, 0.2f);
		HairRenderer->SetScaleRatio(3.7f);
		HairRenderer->SetRenderPos({ 0,3 });
		HairRenderer->ChangeAnimation("Idle");
	}

	{
		ArmRenderer->CreateAnimation("Idle", "Player_arm", 0, 0);
		ArmRenderer->CreateAnimation("Run", "Player_arm", 0, 3, 0.2f);
		ArmRenderer->CreateAnimation("UseTool", "Player_arm", 4, 9, 0.08f);
		ArmRenderer->SetScaleRatio(3.7f);
		ArmRenderer->ChangeAnimation("Idle");
	}

	{
		ShirtRenderer->CreateAnimation("Idle", "Player_shirt", 0, 0);
		ShirtRenderer->CreateAnimation("Run", "Player_shirt", 0, 3, 0.2f);
		ShirtRenderer->SetRenderPos({ 0,9 });
		ShirtRenderer->SetScaleRatio(3.7f);
		ShirtRenderer->ChangeAnimation("Idle");
	}

	{
		PantsRenderer->CreateAnimation("Idle", "Player_pants", 0, 0);
		PantsRenderer->CreateAnimation("Run", "Player_pants", 0, 3, 0.2f);
		PantsRenderer->SetScaleRatio(3.7f);
		PantsRenderer->ChangeAnimation("Idle");
	}

	//{
	//	HatRenderer = CreateRenderer("Player_hat_05.bmp", RenderOrder::Equip);
	//	HatRenderer->SetTexture("Player_hat_05.bmp");
	//	HatRenderer->SetRenderPos({0,-32});
	//	HatRenderer->SetRenderScale(HatRenderer->GetTextureScale() * 3.7f);
	//}

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
