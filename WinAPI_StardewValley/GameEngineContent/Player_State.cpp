#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void Player::IdleStart()
{
	BodyRenderer->ChangeAnimation("Idle");
	HairRenderer->ChangeAnimation("Idle");
	ArmRenderer->ChangeAnimation("Idle");
	ShirtRenderer->ChangeAnimation("Idle");
	PantsRenderer->ChangeAnimation("Idle");
}

void Player::RunStart()
{
	BodyRenderer->ChangeAnimation("Run");
	HairRenderer->ChangeAnimation("Run");
	ArmRenderer->ChangeAnimation("Run");
	ShirtRenderer->ChangeAnimation("Run");
	PantsRenderer->ChangeAnimation("Run");
}

void Player::UseToolStart()
{
	BodyRenderer->ChangeAnimation("Idle");
	HairRenderer->ChangeAnimation("Idle");
	ArmRenderer->ChangeAnimation("UseTool");
	ShirtRenderer->ChangeAnimation("Idle");
	PantsRenderer->ChangeAnimation("Idle");
}

void Player::IdleUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		ChangeState(PlayerState::Run);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChangeState(PlayerState::UseTool);
		return;
	}
}


void Player::RunUpdate(float _DeltaTime)
{
	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A'))
	{
		MovePos = { -Speed * _DeltaTime, 0.0f };
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		MovePos = { Speed * _DeltaTime, 0.0f };
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		MovePos = { 0.0f, -Speed * _DeltaTime };
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		MovePos = { 0.0f, Speed * _DeltaTime };
	}

	if (MovePos == float4::ZERO)
	{
		ChangeState(PlayerState::Idle);
	}

	AddPos(MovePos);
	GetLevel()->GetMainCamera()->AddPos(MovePos);
}

void Player::UseToolUpdate(float _DeltaTime)
{
	static float Check = 0.48f;
	if (0 >= Check)
	{
		ChangeState(PlayerState::Idle);
		Check = 0.48f;
	}
	Check -= _DeltaTime;
}