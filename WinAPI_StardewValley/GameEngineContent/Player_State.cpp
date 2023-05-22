#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Player.h"
#include "ContentLevel.h"

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

	// CameraSetting
	{
		float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
		float4 WinScale_Half = GameEngineWindow::MainWindow.GetScale().Half();
		float4 BackScale_Half = PlayLevel->GetRenderScale().Half();

		if (PlayerDir::Right == Dir && BackScale_Half.X - WinScale_Half.X > CameraPos.X && GetPos().X >= CameraPos.X + WinScale_Half.X)
		{
			GetLevel()->GetMainCamera()->AddPos(MovePos);
			CameraPos = GetLevel()->GetMainCamera()->GetPos();
			if (BackScale_Half.X - WinScale_Half.X < CameraPos.X)
			{
				CameraPos.X = BackScale_Half.X - WinScale_Half.X;
				GetLevel()->GetMainCamera()->SetPos(CameraPos);
			}
		}

		if (PlayerDir::Left == Dir && CameraPos.X - WinScale_Half.X > -BackScale_Half.X && GetPos().X <= CameraPos.X + WinScale_Half.X)
		{
			GetLevel()->GetMainCamera()->AddPos(MovePos);
			CameraPos = GetLevel()->GetMainCamera()->GetPos();
			if (CameraPos.X < WinScale_Half.X - BackScale_Half.X)
			{
				CameraPos.X = WinScale_Half.X - BackScale_Half.X;
				GetLevel()->GetMainCamera()->SetPos(CameraPos);
			}
		}

		if (PlayerDir::Up == Dir && CameraPos.Y - WinScale_Half.Y > -BackScale_Half.Y && GetPos().Y <= CameraPos.Y + WinScale_Half.Y)
		{
			GetLevel()->GetMainCamera()->AddPos(MovePos);
			CameraPos = GetLevel()->GetMainCamera()->GetPos();
			if (CameraPos.Y < WinScale_Half.Y - BackScale_Half.Y)
			{
				CameraPos.Y = WinScale_Half.Y - BackScale_Half.Y;
				GetLevel()->GetMainCamera()->SetPos(CameraPos);
			}
		}

		if (PlayerDir::Down == Dir && BackScale_Half.Y - WinScale_Half.Y > CameraPos.Y && GetPos().Y >= CameraPos.Y + WinScale_Half.Y)
		{
			GetLevel()->GetMainCamera()->AddPos(MovePos);
			CameraPos = GetLevel()->GetMainCamera()->GetPos();
			if (BackScale_Half.Y - WinScale_Half.Y < CameraPos.Y)
			{
				CameraPos.Y = BackScale_Half.Y - WinScale_Half.Y;
				GetLevel()->GetMainCamera()->SetPos(CameraPos);
			}
		}
	}
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