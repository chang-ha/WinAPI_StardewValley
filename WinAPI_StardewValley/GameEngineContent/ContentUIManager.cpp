﻿#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentUIManager.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "ContentMouse.h"

// Test
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentInventory.h"
#include "Player.h"

ContentUIManager* ContentUIManager::MainUI = nullptr;

ContentUIManager::ContentUIManager()
{
}

ContentUIManager::~ContentUIManager()
{

}

void ContentUIManager::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Clock.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\UI\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Clock.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Clock_hand.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Energy.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Inventory.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Sleep.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Shop_Pierre.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Cancel.bmp"));
	}
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("Clock.bmp");
	Clock = CreateUIRenderer("Clock.bmp", RenderOrder::UI);
	Clock->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	Clock->SetRenderPos({ GlobalValue::WinScale.X - Texture->GetScale().Half().X * RENDERRATIO, Texture->GetScale().Half().Y * RENDERRATIO });

	Texture = ResourcesManager::GetInst().FindTexture("Clock_hand.bmp");
	ClockHand = CreateUIRenderer("Clock_hand.bmp", RenderOrder::UI);
	ClockHand->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	ClockHand->SetRenderPos({ GlobalValue::WinScale.X - Texture->GetScale().Half().X * RENDERRATIO - 135, Texture->GetScale().Half().Y * RENDERRATIO + 10 });

	Texture = ResourcesManager::GetInst().FindTexture("Energy.bmp");
	Energy = CreateUIRenderer("Energy.bmp", RenderOrder::UI);
	Energy->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	Energy->SetRenderPos({ GlobalValue::WinScale.X - Texture->GetScale().Half().X * RENDERRATIO, GlobalValue::WinScale.Y - Texture->GetScale().Half().Y * RENDERRATIO });

	DayTextRenderer = CreateUIRenderer(RenderOrder::UI);
	DayTextRenderer->SetText("월.    1", 30, "Sandoll 미생");
	DayTextRenderer->SetRenderPos({ GlobalValue::WinScale.X - 100, 13 });

	Inventory = CreateUIRenderer("UI_Inventory.bmp", RenderOrder::UI);
	InventoryDownRender();

	// SleepUI
	SleepUITexture = ResourcesManager::GetInst().FindTexture("UI_Sleep.bmp");
	SleepUIRenderer = CreateUIRenderer(RenderOrder::UIMouse);
	SleepUIRenderer->SetTexture("UI_Sleep.bmp");
	SleepUIRenderer->SetRenderPos({GlobalValue::WinScale.Half().X, GlobalValue::WinScale.Y - Texture->GetScale().Half().Y});
	SleepUIRenderer->SetRenderScale(Texture->GetScale() * UIRenderRatio);
	SleepUIRenderer->Off();

	SleepYesCollision = CreateCollision(CollisionOrder::Button);
	SleepYesCollision->SetCollisionPos({ GlobalValue::WinScale.hX(), GlobalValue::WinScale.Y * 0.78f });
	SleepYesCollision->SetCollisionScale({GlobalValue::WinScale.hX() + 100, 50});
	SleepYesCollision->Off();

	SleepNoCollision = CreateCollision(CollisionOrder::Button);
	SleepNoCollision->SetCollisionPos({ GlobalValue::WinScale.hX(), GlobalValue::WinScale.Y * 0.88f });
	SleepNoCollision->SetCollisionScale({ GlobalValue::WinScale.hX() + 100, 50});
	SleepNoCollision->Off();

	// ShopUI
	Texture = ResourcesManager::GetInst().FindTexture("UI_Shop_Pierre.bmp");
	ShopRenderer = CreateUIRenderer("UI_Shop_Pierre.bmp", RenderOrder::UI);
	ShopRenderer->SetRenderPos(GlobalValue::WinScale.Half());
	ShopRenderer->SetRenderScale(Texture->GetScale() * 0.9f);
	ShopRenderer->Off();

	CancelRenderer = CreateUIRenderer("UI_Cancel.bmp", RenderOrder::UI);
	CancelRenderer->SetRenderPos({GlobalValue::WinScale.Half().X + Texture->GetScale().Half().X, GlobalValue::WinScale.Half().Y - Texture->GetScale().Half().Y});
	CancelRenderer->Off();

	// PrevSelectRenderer = CreateUIRenderer(RenderOrder::UI);
	// NextSelectRenderer = CreateUIRenderer(RenderOrder::UI);


	// Debug Renderer
	Text1Renderer = CreateUIRenderer(RenderOrder::PlayOver);
	Text2Renderer = CreateUIRenderer(RenderOrder::PlayOver);
	Text3Renderer = CreateUIRenderer(RenderOrder::PlayOver);
	Text4Renderer = CreateUIRenderer(RenderOrder::PlayOver);
	Text1Renderer->SetText("콜리젼디버그 : F1", 30, "Sandoll 미생");
	Text1Renderer->SetRenderPos({ 0, 0 });
	Text2Renderer->SetText("맵 콜리전디버그 : F2", 30, "Sandoll 미생");
	Text2Renderer->SetRenderPos({ 0, 30 });
	Text3Renderer->SetText("이전레벨이동 : F3", 30, "Sandoll 미생");
	Text3Renderer->SetRenderPos({ 0, 60 });
	Text4Renderer->SetText("다음레벨이동 : F4", 30, "Sandoll 미생");
	Text4Renderer->SetRenderPos({ 0, 90 });
}

void ContentUIManager::SleepUIOn()
{
	ContentInventory::MainInventory->Off();
	Inventory->Off();
	Player::MainPlayer->StopPlayer();
	SleepUIRenderer->On();
	SleepYesCollision->On();
	SleepNoCollision->On();
}

void ContentUIManager::ShopUIOn()
{
	ContentInventory::MainInventory->Off();
	Inventory->Off();
	Player::MainPlayer->StopPlayer();
	ShopRenderer->On();
	CancelRenderer->On();
}

void ContentUIManager::ShopUIOff()
{
	ContentInventory::MainInventory->On();
	Inventory->On();
	Player::MainPlayer->SetIsUpdate(true);
	ShopRenderer->Off();
	CancelRenderer->Off();
}

void ContentUIManager::Update(float _Delta)
{
	// Day Code
	if (true == DayChange)
	{
		std::string Day = "";
		switch (DayValue % 7)
		{
		case 0:
			Day = "일";
			break;
		case 1:
			Day = "월";
			break;
		case 2:
			Day = "화";
			break;
		case 3:
			Day = "수";
			break;
		case 4:
			Day = "목";
			break;
		case 5:
			Day = "금";
			break;
		case 6:
			Day = "토";
			break;
		default:
			break;
		}
		DayTextRenderer->SetText(Day + ".    " + std::to_string(DayValue), 30, "Sandoll 미생");
	}

	// Sleep UI

	// SleepUI Datail
	if (0.8f > UIRenderRatio && true == SleepUIRenderer->IsUpdate())
	{
		UIRenderRatio += 2.4f * _Delta;
		SleepUIRenderer->SetRenderScale(SleepUITexture->GetScale() * UIRenderRatio);
	}
	else if (0.8f <= UIRenderRatio && false == SleepUIRenderer->IsUpdate())
	{
		UIRenderRatio = 0.1f;
		SleepUIRenderer->SetRenderScale(SleepUITexture->GetScale() * UIRenderRatio);
	}

	if (false == SleepUIRenderer->IsUpdate())
	{
		return;
	}

	if (true == SleepYesCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect) && true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ContentUIManager::MainUI->Clock->Off();
		ContentUIManager::MainUI->ClockHand->Off();
		ContentUIManager::MainUI->Energy->Off();
		ContentUIManager::MainUI->Inventory->Off();
		ContentUIManager::MainUI->DayTextRenderer->Off();
		SleepUIRenderer->Off();
		SleepYesCollision->Off();
		SleepNoCollision->Off();
		GameEngineCore::ChangeLevel("SleepLevel");
	}
	else if (true == SleepNoCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect) && true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ContentInventory::MainInventory->On();
		Inventory->On();
		Player::MainPlayer->SetIsUpdate(true);
		SleepUIRenderer->Off();
		SleepYesCollision->Off();
		SleepNoCollision->Off();
	}
}

void ContentUIManager::InventoryUpRender()
{
	Inventory->SetRenderPos({ GlobalValue::WinScale.Half().X, 50 });
}

void ContentUIManager::InventoryDownRender()
{
	Inventory->SetRenderPos({ GlobalValue::WinScale.Half().X, GlobalValue::WinScale.Y - 50 });
}
