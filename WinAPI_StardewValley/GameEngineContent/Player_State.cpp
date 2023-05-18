#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "ContentLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Player::RunStart()
{
	ChangeAnimationState("Run");
}

void Player::UseToolStart()
{
    // BodyRenderer->ChangeAnimation("Idle");
	// ArmRenderer->ChangeAnimation("UseTool");
	// HairRenderer->ChangeAnimation("Idle");
	// ShirtRenderer->ChangeAnimation("Idle");
	// PantsRenderer->ChangeAnimation("Idle");
}

void Player::IdleUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(PlayerState::Run);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		DirCheck();
		// ChangeState(PlayerState::UseTool);
		return;
	}
}


void Player::RunUpdate(float _DeltaTime)
{
	DirCheck();
	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') /*&& Dir == PlayerDir::Left*/)
	{
		MovePos = { -Speed * _DeltaTime, 0.0f };
	}

	if (true == GameEngineInput::IsPress('D') /*&& Dir == PlayerDir::Right*/)
	{
		MovePos = { Speed * _DeltaTime, 0.0f };
	}

	if (true == GameEngineInput::IsPress('W') /*&& Dir == PlayerDir::Up*/)
	{
		MovePos = { 0.0f, -Speed * _DeltaTime };
	}

	if (true == GameEngineInput::IsPress('S') /*&& Dir == PlayerDir::Down*/)
	{
		MovePos = { 0.0f, Speed * _DeltaTime };
	}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChangeState(PlayerState::Idle);
	}
	AddPos(MovePos);
	CameraSetting(MovePos);

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

void Player::CameraSetting(float4 MovePos)
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	float4 HalfWinScale = GameEngineWindow::MainWindow.GetScale().Half();
	float4 HalfBackScale = PlayLevel->GetBackScale().Half() * 4;

	if (PlayerDir::Right == Dir && HalfBackScale.X - HalfWinScale.X > CameraPos.X && GetPos().X >= CameraPos.X + HalfWinScale.X)
	{
		GetLevel()->GetMainCamera()->AddPos(MovePos);
		CameraPos = GetLevel()->GetMainCamera()->GetPos();
		if (HalfBackScale.X - HalfWinScale.X < CameraPos.X)
		{
			CameraPos.X = HalfBackScale.X - HalfWinScale.X;
			GetLevel()->GetMainCamera()->SetPos(CameraPos);
		}
		// return;
	}

	if (PlayerDir::Left == Dir && CameraPos.X - HalfWinScale.X > -HalfBackScale.X && GetPos().X <= CameraPos.X + HalfWinScale.X)
	{
		GetLevel()->GetMainCamera()->AddPos(MovePos);
		CameraPos = GetLevel()->GetMainCamera()->GetPos();
		if (CameraPos.X < HalfWinScale.X - HalfBackScale.X)
		{
			CameraPos.X = HalfWinScale.X - HalfBackScale.X;
			GetLevel()->GetMainCamera()->SetPos(CameraPos);
		}
		// return;
	}

	if (PlayerDir::Down == Dir && HalfBackScale.Y - HalfWinScale.Y > CameraPos.Y && GetPos().Y >= CameraPos.Y + HalfWinScale.Y)
	{
		GetLevel()->GetMainCamera()->AddPos(MovePos);
		CameraPos = GetLevel()->GetMainCamera()->GetPos();
		if (HalfBackScale.Y - HalfWinScale.Y < CameraPos.Y)
		{
			CameraPos.Y = HalfBackScale.Y - HalfWinScale.Y;
			GetLevel()->GetMainCamera()->SetPos(CameraPos);
		}
		// return;
	}

	if (PlayerDir::Up == Dir && CameraPos.Y - HalfWinScale.Y > -HalfBackScale.Y && GetPos().Y <= CameraPos.Y + HalfWinScale.Y)
	{
		GetLevel()->GetMainCamera()->AddPos(MovePos);
		CameraPos = GetLevel()->GetMainCamera()->GetPos();
		if (CameraPos.Y < HalfWinScale.Y - HalfBackScale.Y)
		{
			CameraPos.Y = HalfWinScale.Y - HalfBackScale.Y;
			GetLevel()->GetMainCamera()->SetPos(CameraPos);
		}
		// return;
	}
}