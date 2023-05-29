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
		//ChangeAnimationState("Tool2");
	}
	else if (true)
	{
		//ChangeAnimationState("Tool3");
	}

	if (PlayerDir::Up == Dir)
	{
		ArmRenderer->SetOrder(1); // RenderOrder::PlayBelow
		ShirtRenderer->SetRenderPos({ 0,4 * RENDERRATIO });
	}
}

void Player::Tool2Start()
{

	ChangeAnimationState("Tool2");

	if (PlayerDir::Down == Dir)
	{
		ShirtRenderer->SetRenderPos({ 0,4 * RENDERRATIO });
	}
	if (PlayerDir::Up == Dir)
	{
		ArmRenderer->SetOrder(1); // RenderOrder::PlayBelow
		ShirtRenderer->SetRenderPos({ 0,4 * RENDERRATIO });
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
	if (true == GameEngineInput::IsDown(VK_RBUTTON))
	{
		DirCheck();
		ChangeState(PlayerState::Tool2);
		return;
	}
}


void Player::RunUpdate(float _DeltaTime)
{
	DirCheck();
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && PlayerDir::Left == (Dir & PlayerDir::Left))
	{
		CheckPos = LeftCollision;
		MovePos += { -Speed * _DeltaTime, 0.0f };
	}
	else if (true == GameEngineInput::IsPress('D') && PlayerDir::Right == (Dir & PlayerDir::Right))
	{
		CheckPos = RightCollision;
		MovePos += { Speed * _DeltaTime, 0.0f };
	}

	if (true == GameEngineInput::IsPress('W') && PlayerDir::Up == (Dir & PlayerDir::Up))
	{
		MovePos += { 0.0f, -Speed * _DeltaTime };
	}
	else if (true == GameEngineInput::IsPress('S') && PlayerDir::Down == (Dir & PlayerDir::Down))
	{
		CheckPos = DownCollision;
		MovePos += { 0.0f, Speed * _DeltaTime };
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

	Color = GetFrontColor(RGB(0, 0, 0), MovePos);
	if (RGB(0, 0, 0) == Color)
	{
		// MovePos = CheckPos;
	}

	AddPos(MovePos);

	// CameraSetting
	{
		float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
		float4 WinScale_Half = GameEngineWindow::MainWindow.GetScale().Half();
		float4 BackScale_Half = PlayLevel->GetRenderScale().Half();

		if ((PlayerDir::Left == (Dir & PlayerDir::Left)) && CameraPos.X > WinScale_Half.X - BackScale_Half.X && GetPos().X <= CameraPos.X + WinScale_Half.X)
		{
			GetLevel()->GetMainCamera()->AddPos({MovePos.X, 0});
			CameraPos = GetLevel()->GetMainCamera()->GetPos();
			if (CameraPos.X < WinScale_Half.X - BackScale_Half.X)
			{
				CameraPos.X = WinScale_Half.X - BackScale_Half.X;
				GetLevel()->GetMainCamera()->SetPos(CameraPos);
			}
		}
		else if ((PlayerDir::Right == (Dir & PlayerDir::Right)) && BackScale_Half.X - WinScale_Half.X > CameraPos.X && GetPos().X >= CameraPos.X + WinScale_Half.X)
		{
			GetLevel()->GetMainCamera()->AddPos({MovePos.X,0});
			CameraPos = GetLevel()->GetMainCamera()->GetPos();
			if (BackScale_Half.X - WinScale_Half.X < CameraPos.X)
			{
				CameraPos.X = BackScale_Half.X - WinScale_Half.X;
				GetLevel()->GetMainCamera()->SetPos(CameraPos);
			}
		}

		if ((PlayerDir::Up == (Dir & PlayerDir::Up)) && CameraPos.Y > WinScale_Half.Y - BackScale_Half.Y && GetPos().Y <= CameraPos.Y + WinScale_Half.Y)
		{
			GetLevel()->GetMainCamera()->AddPos({0, MovePos.Y});
			CameraPos = GetLevel()->GetMainCamera()->GetPos();
			if (CameraPos.Y < WinScale_Half.Y - BackScale_Half.Y)
			{
				CameraPos.Y = WinScale_Half.Y - BackScale_Half.Y;
				GetLevel()->GetMainCamera()->SetPos(CameraPos);
			}
		}
		else if ((PlayerDir::Down == (Dir & PlayerDir::Down)) && BackScale_Half.Y - WinScale_Half.Y > CameraPos.Y && GetPos().Y >= CameraPos.Y + WinScale_Half.Y)
		{
			GetLevel()->GetMainCamera()->AddPos({0, MovePos.Y});
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
	if (true == ArmRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		ArmRenderer->SetOrder(7); // RenderOrder::arm
	}
}

void Player::Tool2Update(float _DeltaTime)
{
	if (true == ArmRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		ArmRenderer->SetOrder(7); // RenderOrder::arm
	}
}