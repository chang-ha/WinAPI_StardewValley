#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Player.h"
#include "ContentLevel.h"
#include "ContentActor.h"

void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Player::RunStart()
{
	ChangeAnimationState("Run");
}

void Player::ToolStart()
{

	if (true)
	{
		ChangeAnimationState("Tool1");
	}
	else if (true)
	{
		//ChangeAnimationState("Tool1");
	}
	else if (true)
	{
		//ChangeAnimationState("Tool1");
	}

	if (PlayerDir::Up == Dir)
	{
		ShirtRenderer->SetRenderPos({ 0,16 });
	}
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
		ChangeState(PlayerState::Tool);
		return;
	}
}


void Player::RunUpdate(float _DeltaTime)
{
	DirCheck();
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') /*&& Dir == PlayerDir::Left*/)
	{
		CheckPos = { -32, 32 };
		MovePos = { -Speed * _DeltaTime, 0.0f };
	}

	if (true == GameEngineInput::IsPress('D') /*&& Dir == PlayerDir::Right*/)
	{
		CheckPos = { 32, 32 };
		MovePos = { Speed * _DeltaTime, 0.0f };
	}

	if (true == GameEngineInput::IsPress('W') /*&& Dir == PlayerDir::Up*/)
	{
		MovePos = { 0.0f, -Speed * _DeltaTime };
	}

	if (true == GameEngineInput::IsPress('S') /*&& Dir == PlayerDir::Down*/)
	{
		CheckPos = { 0, 48 };
		MovePos = { 0.0f, Speed * _DeltaTime };
	}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChangeState(PlayerState::Idle);
	}

	// Map Collision
	unsigned int Color = GetFrontColor(RGB(0, 0, 0), CheckPos);
	if (RGB(0, 0, 0) == Color)
	{
		return;
	}

	AddPos(MovePos);

	// CameraSetting
	{
		float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
		float4 WinScale_Half = GameEngineWindow::MainWindow.GetScale().Half();
		float4 BackScale_Half = PlayLevel->GetRenderScale().Half();

		if (PlayerDir::Left == Dir && CameraPos.X > WinScale_Half.X - BackScale_Half.X && GetPos().X <= CameraPos.X + WinScale_Half.X)
		{
			GetLevel()->GetMainCamera()->AddPos(MovePos);
			CameraPos = GetLevel()->GetMainCamera()->GetPos();
			if (CameraPos.X < WinScale_Half.X - BackScale_Half.X)
			{
				CameraPos.X = WinScale_Half.X - BackScale_Half.X;
				GetLevel()->GetMainCamera()->SetPos(CameraPos);
			}
		}
		else if (PlayerDir::Right == Dir && BackScale_Half.X - WinScale_Half.X > CameraPos.X && GetPos().X >= CameraPos.X + WinScale_Half.X)
		{
			GetLevel()->GetMainCamera()->AddPos(MovePos);
			CameraPos = GetLevel()->GetMainCamera()->GetPos();
			if (BackScale_Half.X - WinScale_Half.X < CameraPos.X)
			{
				CameraPos.X = BackScale_Half.X - WinScale_Half.X;
				GetLevel()->GetMainCamera()->SetPos(CameraPos);
			}
		}

		if (PlayerDir::Up == Dir && CameraPos.Y > WinScale_Half.Y - BackScale_Half.Y && GetPos().Y <= CameraPos.Y + WinScale_Half.Y)
		{
			GetLevel()->GetMainCamera()->AddPos(MovePos);
			CameraPos = GetLevel()->GetMainCamera()->GetPos();
			if (CameraPos.Y < WinScale_Half.Y - BackScale_Half.Y)
			{
				CameraPos.Y = WinScale_Half.Y - BackScale_Half.Y;
				GetLevel()->GetMainCamera()->SetPos(CameraPos);
			}
		}
		else if (PlayerDir::Down == Dir && BackScale_Half.Y - WinScale_Half.Y > CameraPos.Y && GetPos().Y >= CameraPos.Y + WinScale_Half.Y)
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

void Player::ToolUpdate(float _DeltaTime)
{
	static float Check = 0.5f;
	if (0 >= Check)
	{
		ChangeState(PlayerState::Idle);
		Check = 0.5f;
	}
	Check -= _DeltaTime;
}