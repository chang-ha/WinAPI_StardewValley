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
	EffectPlayer.Stop();
	PrevTileColor = RGB(0, 0, 0);
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
	EffectPlayer.Stop();

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
	if (true == GameEngineInput::IsFree('A')
		&& true == GameEngineInput::IsFree('W')
		&& true == GameEngineInput::IsFree('S')
		&& true == GameEngineInput::IsFree('D'))
	{
		DirCheck();
		ChangeState(PlayerState::Idle);
		return;
	}

	DirCheck();

	// Player TileColor Check
	if (PlayerDir::Up == (PlayerDir::Up & Dir))
	{
		CurTileColor = GetFrontColor(RGB(0, 0, 0));
	}
	else
	{
		CurTileColor = GetFrontColor(RGB(0, 0, 0), DownCollision);
	}

	static float PerTime = 0.2f;
	if (PrevTileColor != CurTileColor && PerTime < 0.0f)
	{
		PrevTileColor = CurTileColor;
		EffectPlayer.Stop();
		PerTime = 0.2f;
		switch (CurTileColor)
		{
		case Tile::Wood:
			EffectPlayer = GameEngineSound::SoundPlay("woodyStep.wav");
			break;
		case Tile::Grass :
			EffectPlayer = GameEngineSound::SoundPlay("grassyStep.wav");
			break;
		case Tile::Sand :
			EffectPlayer = GameEngineSound::SoundPlay("sandyStep.wav");
			break;
		case Tile::Stone:
			EffectPlayer = GameEngineSound::SoundPlay("stoneStep.wav");
			break;
		case Tile::Floor:
			EffectPlayer = GameEngineSound::SoundPlay("thudStep.wav");
			break;
		default:
			// EffectPlayer.Stop();
			break;
		}
		EffectPlayer.SetVolume(0.5f);
	}
	PerTime -= _DeltaTime;

	// Player Move(Right, Left)
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	unsigned int Color = 0;

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

	// Map Collision
	//Color = GetFrontColor(RGB(0, 0, 0), CheckPos);
	//if (RGB(0, 0, 0) == Color)
	//{
	//	MovePos.X = 0.0f;
	//}

	Color = GetFrontColor(RGB(0, 0, 0), CheckPos + MovePos);
	if (RGB(0, 0, 0) == Color)
	{
		if (LeftCollision == CheckPos)
		{
			while (RGB(0,0,0 == GetFrontColor(RGB(0, 0, 0), CheckPos + MovePos)))
			{
				MovePos += float4::RIGHT;
			}
		}
		else if(RightCollision == CheckPos)
		{
			while (RGB(0, 0, 0 == GetFrontColor(RGB(0, 0, 0), CheckPos + MovePos)))
			{
				MovePos += float4::LEFT;
			}
		}
	}

	// Player Move(Up, Down)
	if (true == GameEngineInput::IsPress('W') && PlayerDir::Up == (Dir & PlayerDir::Up))
	{
		CheckPos = UpCollision;
		MovePos += { 0.0f, -Speed * _DeltaTime };
	}
	else if (true == GameEngineInput::IsPress('S') && PlayerDir::Down == (Dir & PlayerDir::Down))
	{
		CheckPos = DownCollision;
		MovePos += { 0.0f, Speed * _DeltaTime };
	}

	// Map Collision
	//Color = GetFrontColor(RGB(0, 0, 0), CheckPos);
	//if (RGB(0, 0, 0) == Color)
	//{
	//	MovePos.Y = 0.0f;
	//}

	Color = GetFrontColor(RGB(0, 0, 0), CheckPos + MovePos);
	if (RGB(0, 0, 0) == Color)
	{
		if (UpCollision == CheckPos)
		{
			while (RGB(0, 0, 0 == GetFrontColor(RGB(0, 0, 0), CheckPos + MovePos)))
			{
				MovePos += float4::DOWN;
			}
		}
		else if (DownCollision == CheckPos)
		{
			while (RGB(0, 0, 0 == GetFrontColor(RGB(0, 0, 0), CheckPos + MovePos)))
			{
				MovePos += float4::UP;
			}
		}
	}



	if (float4::ZERO == MovePos)
	{
		return;
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