#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"
#include "ContentLevel.h"
#include "ContentActor.h"
#include "ContentUIManager.h"
#include "Farm.h"
#include "ContentItem.h"
#include "ContentInventory.h"
#include "ContentCrops.h"

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
	ContentUIManager::MainUI->PlusEnergyValue(-2.0f);
	ChangeAnimationState("Tool1");


	switch (CurItem->GetItemType())
	{
	case ItemType::Axe:
		// Tool Axe
		ToolCollisionCreate(CollisionOrder::Axe);
		ToolRenderer->SetSprite(ToolDir + "Axe.bmp");
		break;
	case ItemType::Hoe:
		// Tool Hoe
	{
		ToolCollisionCreate(CollisionOrder::Hoe);
		ToolRenderer->SetSprite(ToolDir + "Hoe.bmp");
		Farm* _Farm = dynamic_cast<Farm*>(PlayLevel);
		if (nullptr != _Farm)
		{
			_Farm->GroundHoe();
		}
	}
	break;
	case ItemType::PickAxe:
		// Tool PickAxe
		ToolRenderer->SetSprite(ToolDir + "PickAxe.bmp");
		ToolCollisionCreate(CollisionOrder::PickAxe);
		break;
	}

	if (PlayerDir::Up == Dir)
	{
		ShirtRenderer->SetRenderPos({ 0,4 * RENDERRATIO });
		ArmRenderer->SetYPivot(-1);
	}
	EffectPlayer.SetVolume(0.6f);
}

void Player::Tool2Start()
{
	// Tool WateringCan
	ChangeAnimationState("Tool2");
	ToolRenderer->SetSprite(ToolDir + "WateringCan.bmp");

	WaterRenderer->On();
	WaterRenderer->ChangeAnimation("Water", 0, true);
	WaterRenderer->SetRenderPos(PlayLevel->GetUITileMap()->IndexToPos(TileLimit().iX(), TileLimit().iY()) + TILESIZE.Half() * RENDERRATIO - GetPos());
	EffectPlayer = GameEngineSound::SoundPlay("wateringcan.wav");

	Farm* _Farm = dynamic_cast<Farm*>(PlayLevel);
	if (nullptr != _Farm)
	{
		_Farm->GroundWatering();
	}

	if (PlayerDir::Down == Dir)
	{
		ShirtRenderer->SetRenderPos({ 0,4 * RENDERRATIO });
	}

	if (PlayerDir::Up == Dir)
	{
		ShirtRenderer->SetRenderPos({ 0,4 * RENDERRATIO });
		ArmRenderer->SetYPivot(-1);
	}
}

void Player::HarvestStart()
{
	// Harvest
	ChangeAnimationState("Harvest");
	if (PlayerDir::Down == Dir)
	{
		ShirtRenderer->SetRenderPos({ 0,4 * RENDERRATIO });
	}

	if (PlayerDir::Up == Dir)
	{
		ShirtRenderer->SetRenderPos({ 0,4 * RENDERRATIO });
		ArmRenderer->SetYPivot(-1);
	}
}

void Player::IdleUpdate(float _DeltaTime)
{
	// EffectPlayer.Stop();
	if (nullptr != ToolCollision && false == ToolCollision->IsDeath())
	{
		ToolCollision->Death();
	}

	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(PlayerState::Run);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_RBUTTON))
	{
		// Harvest
		std::vector<GameEngineCollision*> _CollisionResult;
		ToolCollisionCreate(CollisionOrder::PlayerAction);
		if (true == ToolCollision->Collision(CollisionOrder::Crops, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
		{
			ContentCrops* _Crops = dynamic_cast<ContentCrops*>(_CollisionResult[0]->GetActor());
			if (nullptr == _Crops)
			{
				MsgBoxAssert("해당 액터의 CollisionOrder가 잘못되어 있습니다.");
			}

			if (true == _Crops->Harvest())
			{
				ToolDirCheck();
				ChangeState(PlayerState::Harvest);
			}
		}
	}

	// Use Item
	CurItem = ContentInventory::MainInventory->GetCurItem();
	if (nullptr == CurItem)
	{
		return;
	}

	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		std::vector<GameEngineCollision*> _CollisionResult;
		if (true == ContentMouse::MainMouse->GetMouseCollision()->Collision(CollisionOrder::Inventory_Item, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
		{
			return;
		}

		if (ItemType::Resources == CurItem->GetItemType())
		{
			return;
		}
		else if (ItemType::Crops == CurItem->GetItemType())
		{
			return;
		}
		else if (ItemType::Seed == CurItem->GetItemType())
		{
			Farm* _Farm = dynamic_cast<Farm*>(PlayLevel);
			if (nullptr != _Farm)
			{
				ToolCollisionCreate(CollisionOrder::Axe);
				_Farm->GroundSeeding(CurItem);
				ToolCollision->Death();
			}
			return;
		}
		else if (ItemType::WateringCan == CurItem->GetItemType())
		{
			ToolDirCheck();
			ChangeState(PlayerState::Tool2);
			return;
		}
		else
		{
			ToolDirCheck();
			ChangeState(PlayerState::Tool);
			return;
		}
	}
}


void Player::RunUpdate(float _DeltaTime)
{
	// Change To Idle
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

	// Player TileColor Check & StepSound Play
	if (PlayerDir::Right == (Dir & PlayerDir::Right))
	{
		CurTileColor = GetTileColor(RGB(0, 0, 0), RightCollision);
	}
	else if (PlayerDir::Left == (Dir & PlayerDir::Left))
	{
		CurTileColor = GetTileColor(RGB(0, 0, 0), LeftCollision);
	}
	else if (PlayerDir::Up == (Dir & PlayerDir::Up))
	{
		CurTileColor = GetTileColor(RGB(0, 0, 0), UpCollision);
	}
	else if (PlayerDir::Down == (Dir & PlayerDir::Down))
	{
		CurTileColor = GetTileColor(RGB(0, 0, 0), DownCollision);
	}

	static float PerTime = 0.2f;
	if (PrevTileColor != CurTileColor && 0.0f > PerTime)
	{
		PrevTileColor = CurTileColor;
		EffectPlayer.Stop();
		PerTime = 0.2f;
		switch (CurTileColor)
		{
		case Tile::Wood:
			EffectPlayer = GameEngineSound::SoundPlay("woodyStep.wav", 10000);
			break;
		case Tile::Grass:
			EffectPlayer = GameEngineSound::SoundPlay("grassyStep.wav", 10000);
			break;
		case Tile::Sand:
			EffectPlayer = GameEngineSound::SoundPlay("sandyStep.wav", 10000);
			break;
		case Tile::Stone:
			EffectPlayer = GameEngineSound::SoundPlay("stoneStep.wav", 10000);
			break;
		case Tile::Floor:
			EffectPlayer = GameEngineSound::SoundPlay("thudStep.wav", 10000);
			break;
		default:
			break;
		}
		EffectPlayer.SetVolume(0.8f);
	}
	PerTime -= _DeltaTime;


	// Player Move
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	unsigned int Color = 0;

	///////// Player Move(Right, Left)

	if (true == GameEngineInput::IsPress('A') && PlayerDir::Left == (Dir & PlayerDir::Left))
	{
		CheckPos = LeftCollision;
		MovePos += { -Speed * _DeltaTime, 0.0f };
	}
	else if (true == GameEngineInput::IsPress('D') && PlayerDir::Right == (Dir & PlayerDir::Right))
	{
		CheckPos = RightCollision;
		MovePos += { Speed* _DeltaTime, 0.0f };
	}

	// MapCollision
	Color = GetTileColor(RGB(0, 0, 0), CheckPos + MovePos);
	if (RGB(0, 0, 0) == Color)
	{
		if (LeftCollision == CheckPos)
		{
			while (RGB(0, 0, 0) == Color)
			{
				MovePos += float4::RIGHT;
				Color = GetTileColor(RGB(0, 0, 0), CheckPos + MovePos);
			}
		}
		else if (RightCollision == CheckPos)
		{
			while (RGB(0, 0, 0) == Color)
			{
				MovePos += float4::LEFT;
				Color = GetTileColor(RGB(0, 0, 0), CheckPos + MovePos);
			}
		}
		MovePos.X = static_cast<float>(MovePos.iX());
	}

	// ActorCollision
	std::vector<GameEngineCollision*> _CollisionResult;
	if (true == BodyCollision->CollisionNext(MovePos, CollisionOrder::Resources, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
	{
		if (LeftCollision == CheckPos)
		{
			while (BodyCollision->CollisionNext(MovePos, CollisionOrder::Resources, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
			{
				MovePos += float4::RIGHT;
				BodyCollision->CollisionNext(MovePos, CollisionOrder::Resources, _CollisionResult, CollisionType::Rect, CollisionType::Rect);
			}
		}
		else if (RightCollision == CheckPos)
		{
			while (BodyCollision->CollisionNext(MovePos, CollisionOrder::Resources, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
			{
				MovePos += float4::LEFT;
				BodyCollision->CollisionNext(MovePos, CollisionOrder::Resources, _CollisionResult, CollisionType::Rect, CollisionType::Rect);
			}
		}
		MovePos.X = static_cast<float>(MovePos.iX());
	}

	///////// Player Move(Up, Down)
	if (true == GameEngineInput::IsPress('W') && PlayerDir::Up == (Dir & PlayerDir::Up))
	{
		CheckPos = UpCollision;
		MovePos += { 0.0f, -Speed * _DeltaTime };
	}
	else if (true == GameEngineInput::IsPress('S') && PlayerDir::Down == (Dir & PlayerDir::Down))
	{
		CheckPos = DownCollision;
		MovePos += { 0.0f, Speed* _DeltaTime };
	}

	// MapCollision
	Color = GetTileColor(RGB(0, 0, 0), CheckPos + MovePos);
	if (RGB(0, 0, 0) == Color)
	{
		if (UpCollision == CheckPos)
		{
			while (RGB(0, 0, 0) == Color)
			{
				MovePos += float4::DOWN;
				Color = GetTileColor(RGB(0, 0, 0), CheckPos + MovePos);
			}
		}
		else if (DownCollision == CheckPos)
		{
			while (RGB(0, 0, 0) == Color)
			{
				MovePos += float4::UP;
				Color = GetTileColor(RGB(0, 0, 0), CheckPos + MovePos);
			}
		}
		MovePos.Y = static_cast<float>(MovePos.iY());
	}

	// ActorCollision
	if (true == BodyCollision->CollisionNext(MovePos, CollisionOrder::Resources, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
	{
		if (UpCollision == CheckPos)
		{
			while (BodyCollision->CollisionNext(MovePos, CollisionOrder::Resources, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
			{
				MovePos += float4::DOWN;
				BodyCollision->CollisionNext(MovePos, CollisionOrder::Resources, _CollisionResult, CollisionType::Rect, CollisionType::Rect);
			}
		}
		else if (DownCollision == CheckPos)
		{
			while (BodyCollision->CollisionNext(MovePos, CollisionOrder::Resources, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
			{
				MovePos += float4::UP;
				BodyCollision->CollisionNext(MovePos, CollisionOrder::Resources, _CollisionResult, CollisionType::Rect, CollisionType::Rect);
			}
		}
		MovePos.Y = static_cast<float>(MovePos.iY());
	}

	AddPos(MovePos);

	// Change Map
	Color = GetTileColor(RGB(0, 0, 0), CheckPos + MovePos);
	if (Tile::PrevMap == Color)
	{
		GameEngineCore::ChangeLevel(PlayLevel->GetPrevLevel());
	}
	else if (Tile::NextMap == Color)
	{
		GameEngineCore::ChangeLevel(PlayLevel->GetNextLevel());
	}
	else if (Tile::Building == Color)
	{
		GameEngineCore::ChangeLevel(PlayLevel->GetBuildingLevel());
	}

	static bool SleepUIOnce = false;
	if (Tile::SleepTile == Color && false == SleepUIOnce)
	{
		SleepUIOnce = true;
		ContentUIManager::MainUI->SleepUIOn();
	}
	else if (Tile::Floor == Color && true == SleepUIOnce)
	{
		SleepUIOnce = false;
	}

	// CameraSetting
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	float4 BackScale = PlayLevel->GetRenderScale();

	if ((PlayerDir::Left == (Dir & PlayerDir::Left)) && CameraPos.X > 0 && GetPos().X <= CameraPos.X + GlobalValue::WinScale.Half().X)
	{
		GetLevel()->GetMainCamera()->AddPos({ MovePos.X, 0 });
		CameraPos = GetLevel()->GetMainCamera()->GetPos();
		if (CameraPos.X < 0)
		{
			CameraPos.X = 0;
			GetLevel()->GetMainCamera()->SetPos(CameraPos);
		}
	}
	else if ((PlayerDir::Right == (Dir & PlayerDir::Right)) && BackScale.X - GlobalValue::WinScale.X > CameraPos.X && GetPos().X >= CameraPos.X + GlobalValue::WinScale.Half().X)
	{
		GetLevel()->GetMainCamera()->AddPos({ MovePos.X,0 });
		CameraPos = GetLevel()->GetMainCamera()->GetPos();
		if (BackScale.X - GlobalValue::WinScale.X < CameraPos.X)
		{
			CameraPos.X = BackScale.X - GlobalValue::WinScale.X;
			GetLevel()->GetMainCamera()->SetPos(CameraPos);
		}
	}

	if ((PlayerDir::Up == (Dir & PlayerDir::Up)) && CameraPos.Y > 0 && GetPos().Y < CameraPos.Y + GlobalValue::WinScale.Half().Y)
	{
		GetLevel()->GetMainCamera()->AddPos({ 0, MovePos.Y });
		CameraPos = GetLevel()->GetMainCamera()->GetPos();
		if (CameraPos.Y <= 0)
		{
			CameraPos.Y = 0;
			GetLevel()->GetMainCamera()->SetPos(CameraPos);
		}
	}
	else if ((PlayerDir::Down == (Dir & PlayerDir::Down)) && BackScale.Y - GlobalValue::WinScale.Y > CameraPos.Y && GetPos().Y >= CameraPos.Y + GlobalValue::WinScale.Half().Y)
	{
		GetLevel()->GetMainCamera()->AddPos({ 0, MovePos.Y });
		CameraPos = GetLevel()->GetMainCamera()->GetPos();
		if (BackScale.Y - GlobalValue::WinScale.Y <= CameraPos.Y)
		{
			CameraPos.Y = BackScale.Y - GlobalValue::WinScale.Y;
			GetLevel()->GetMainCamera()->SetPos(CameraPos);
		}
	}
}

void Player::ToolUpdate(float _DeltaTime)
{
	ToolRenderer->On();
	switch (Dir)
	{
	case Null:
		break;
	case Up:
		switch (ArmRenderer->GetCurFrame())
		{
		case 0:
			ToolRenderer->SetOrder(static_cast<int>(RenderOrder::Play));
			ToolRenderer->SetYPivot(-5 * RENDERRATIO);
			break;
		case 1:
			ToolRenderer->SetRenderPos(float4{ 0, 5 } *RENDERRATIO);
			ToolRenderer->SetTexture("Up2_" + CurItem->GetItemName());
			break;
		default:
			ToolRenderer->Off();
			ToolRenderer->SetOrder(static_cast<int>(RenderOrder::PlayOver));
			ToolRenderer->SetYPivot(0);
			break;
		}
		break;
	case Down:
		switch (ArmRenderer->GetCurFrame())
		{
		case 0:
			ToolRenderer->SetRenderPos(float4{ -4, 1 } *RENDERRATIO);
			break;
		case 1:
			ToolRenderer->SetAngle(-5.0f);
			ToolRenderer->SetRenderPos(float4{ 0, 5 } *RENDERRATIO);
			break;
		case 2:
			ToolRenderer->Off();
			ToolRenderer->SetAngle(0.0f);
			break;
		case 3:
			ToolRenderer->On();
			ToolRenderer->SetTexture("Down2_" + CurItem->GetItemName());
			ToolRenderer->SetRenderPos(float4{ 0, 23 } *RENDERRATIO);
			break;
		case 4:
			ToolRenderer->SetRenderPos(float4{ 0, 24 } *RENDERRATIO);
			break;
		default:
			break;
		}
		break;
	case Right:
		switch (ArmRenderer->GetCurFrame())
		{
		case 0:
			ToolRenderer->SetAngle(-14.0f);
			break;
		case 1:
			ToolRenderer->SetAngle(25.0f);
			break;
		case 2:
			ToolRenderer->SetAngle(60.0f);
			break;
		case 3:
			ToolRenderer->SetRenderPos(float4{ 0, -1 } *RENDERRATIO);
			ToolRenderer->SetAngle(107.0f);
			break;
		case 4:
			ToolRenderer->SetRenderPos(float4{ 0, 1 } *RENDERRATIO);
			break;
		default:
			break;
		}
		break;
	case Left:
		switch (ArmRenderer->GetCurFrame())
		{
		case 0:
			ToolRenderer->SetAngle(14.0f);
			break;
		case 1:
			ToolRenderer->SetAngle(-25.0f);
			break;
		case 2:
			ToolRenderer->SetAngle(-60.0f);
			break;
		case 3:
			ToolRenderer->SetRenderPos(float4{ 0, -1 } *RENDERRATIO);
			ToolRenderer->SetAngle(-107.0f);
			break;
		case 4:
			ToolRenderer->SetRenderPos(float4{ 0, 1 } *RENDERRATIO);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	if (true == ArmRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		ToolCollision->Death();
		ArmRenderer->SetYPivot(5 * RENDERRATIO);
		ToolRenderer->SetRenderPos({});
		ToolRenderer->SetAngle({});
		ToolRenderer->Off();
	}
}

void Player::Tool2Update(float _DeltaTime)
{
	ToolRenderer->On();

	switch (Dir)
	{
	case Null:
		break;
	case Up:
		switch (ArmRenderer->GetCurFrame())
		{
		case 0:
			ToolRenderer->SetOrder(static_cast<int>(RenderOrder::PlayBelow));
			ToolRenderer->SetRenderPos(float4{ 0, 20 } *RENDERRATIO);
			break;
		case 1:
			ToolRenderer->SetRenderPos(float4{ 0, 12 } *RENDERRATIO);
			break;
		case 2:
			ToolRenderer->SetRenderPos(float4{ 0, 0 } *RENDERRATIO);
			break;
		default:
			break;
		}
		break;
	case Down:
		switch (ArmRenderer->GetCurFrame())
		{
		case 0:
			ToolRenderer->SetOrder(static_cast<int>(RenderOrder::Play));
			ToolRenderer->SetYPivot(-5 * RENDERRATIO);
			ToolRenderer->SetRenderPos(float4{ 0, 20 } *RENDERRATIO);
			break;
		case 1:
			ToolRenderer->SetRenderPos(float4{ 0, 18 } *RENDERRATIO);
			break;
		case 2:
			ToolRenderer->SetRenderPos(float4{ 0, 22 } *RENDERRATIO);
			ToolRenderer->SetTexture("Down2_" + CurItem->GetItemName());
			break;
		default:
			break;
		}
		break;
	case Right:
		switch (ArmRenderer->GetCurFrame())
		{
		case 0:
			ToolRenderer->SetRenderPos(float4{ 12, 17 } *RENDERRATIO);
			break;
		case 1:
			ToolRenderer->SetRenderPos(float4{ 10, 15 } *RENDERRATIO);
			ToolRenderer->SetAngle(10.0f);
			break;
		case 2:
			ToolRenderer->SetRenderPos(float4{ 12, 8 } *RENDERRATIO);
			ToolRenderer->SetAngle(0.0f);
			ToolRenderer->SetTexture("Right2_" + CurItem->GetItemName());
			break;
		default:
			break;
		}
		break;
	case Left:
		switch (ArmRenderer->GetCurFrame())
		{
		case 0:
			ToolRenderer->SetRenderPos(float4{ -12, 17 } *RENDERRATIO);
			break;
		case 1:
			ToolRenderer->SetRenderPos(float4{ -10, 15 } *RENDERRATIO);
			ToolRenderer->SetAngle(-10.0f);
			break;
		case 2:
			ToolRenderer->SetRenderPos(float4{ -12, 8 } *RENDERRATIO);
			ToolRenderer->SetAngle(0.0f);
			ToolRenderer->SetTexture("Left2_" + CurItem->GetItemName());
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	if (true == ArmRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		ArmRenderer->SetYPivot(5 * RENDERRATIO);
		ToolRenderer->SetRenderPos({});
		ToolRenderer->SetAngle({});
		ToolRenderer->Off();
		if (PlayerDir::Up == Dir)
		{
			ToolRenderer->SetOrder(static_cast<int>(RenderOrder::PlayOver));
		}
	}
}

void Player::HarvestUpdate(float _DeltaTime)
{
	if (true == ArmRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		ToolCollision->Death();
		ArmRenderer->SetYPivot(5 * RENDERRATIO);
	}
}