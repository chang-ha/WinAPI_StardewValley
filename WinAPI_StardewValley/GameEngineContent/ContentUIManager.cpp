﻿#define ITEMRENDER_START_X 0.345f
#define ITEMRENDER_START_Y 0.21f
#define ITEMRENDER_Y 0.1055f

#define ITEMPRICE_START_Y 0.18f
#define ITEMPRICE_X 0.84f
#define ITEMPRICE_Y 0.11f

#define ITEMCOLLISION_START_Y 0.7f
#define ITEMCOLLISION_X 0.605f
#define ITEMCOLLISION_Y 0.105f

#include <GameEngineBase/GameEnginePath.h>

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

#include <GameEngineCore/GameEngineCamera.h>

ContentUIManager* ContentUIManager::MainUI = nullptr;

ContentUIManager::ContentUIManager()
{
}

ContentUIManager::~ContentUIManager()
{
	for (int x = 0; x < ShopItem.size(); x++)
	{
		if (nullptr != ShopItem[x])
		{
			delete ShopItem[x];
			ShopItem[x] = nullptr;
		}
	}
}

void ContentUIManager::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Clock.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI\\Clock.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI\\Clock_hand.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI\\Energy.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI\\UI_Inventory.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI\\UI_Sleep.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI\\UI_Shop_Pierre.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI\\UI_Cancel.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI\\UI_Shop_Select.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI\\Shop_Seed_Parsnip.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI\\Shop_Seed_Cauliflower.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI\\Shop_Seed_Garlic.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI\\Shop_Seed_Potato.bmp"));
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
	SleepUIRenderer->SetRenderPos({GlobalValue::WinScale.hX(), GlobalValue::WinScale.Y - SleepUITexture->GetScale().hY()});
	SleepUIRenderer->SetRenderScale(SleepUITexture->GetScale() * UIRenderRatio);
	SleepUIRenderer->Off();

	SleepYesCollision = CreateCollision(CollisionOrder::Button);
	SleepYesCollision->SetCollisionPos({ GlobalValue::WinScale.hX(), GlobalValue::WinScale.Y * 0.78f });
	SleepYesCollision->SetCollisionScale({GlobalValue::WinScale.hX() + 150, 50});
	SleepYesCollision->Off();

	SleepNoCollision = CreateCollision(CollisionOrder::Button);
	SleepNoCollision->SetCollisionPos({ GlobalValue::WinScale.hX(), GlobalValue::WinScale.Y * 0.88f });
	SleepNoCollision->SetCollisionScale({ GlobalValue::WinScale.hX() + 150, 50});
	SleepNoCollision->Off();

	// ShopUI
	Texture = ResourcesManager::GetInst().FindTexture("UI_Shop_Pierre.bmp");
	ShopRenderer = CreateUIRenderer("UI_Shop_Pierre.bmp", RenderOrder::UI);
	ShopRenderer->SetRenderPos(GlobalValue::WinScale.Half());
	ShopRenderer->SetRenderScale(Texture->GetScale() * 0.9f);
	ShopRenderer->Off();

	CancelRenderer = CreateUIRenderer("UI_Cancel.bmp", RenderOrder::UI);
	CancelRenderer->SetRenderPos({GlobalValue::WinScale.hX() + Texture->GetScale().hX() - 75, GlobalValue::WinScale.hY() - Texture->GetScale().hY() + 40});
	CancelRenderer->SetRenderScale(float4{11, 11} *RENDERRATIO);
	CancelRenderer->Off();

	CancelCollision = CreateCollision(CollisionOrder::Button);
	CancelCollision->SetCollisionPos({GlobalValue::WinScale.X - 140, GlobalValue::WinScale.hY() + 117});
	CancelCollision->SetCollisionScale(float4{ 11, 11 } *RENDERRATIO);
	CancelCollision->Off();

	Texture = ResourcesManager::GetInst().FindTexture("UI_Shop_Select.bmp");
	ItemSelectRenderer = CreateUIRenderer("UI_Shop_Select.bmp", RenderOrder::UI);
	ItemSelectRenderer->SetRenderPos(GlobalValue::WinScale.Half());
	ItemSelectRenderer->SetRenderScale(Texture->GetScale() * 0.9f);
	ItemSelectRenderer->Off();

	ShopItem.resize(4);

	for (int x = 0; x < ShopItem.size(); x++)
	{
		ShopItem[x] = new ShopItemData();

		GameEngineRenderer* _ItemRenderer = CreateUIRenderer(RenderOrder::Inventory_Item);
		_ItemRenderer->SetRenderPos({ GlobalValue::WinScale.X * ITEMRENDER_START_X, GlobalValue::WinScale.Y * (ITEMRENDER_START_Y + ITEMRENDER_Y * x) });
		_ItemRenderer->SetRenderScale(TILESIZE * RENDERRATIO * 1.2f);
		_ItemRenderer->Off();

		GameEngineRenderer* _ItemPriceTextRenderer = CreateUIRenderer(RenderOrder::UI);
		_ItemPriceTextRenderer->SetText("20", 45, "Sandoll 미생");
		_ItemPriceTextRenderer->SetRenderPos({ GlobalValue::WinScale.X * ITEMPRICE_X, GlobalValue::WinScale.Y * (ITEMPRICE_START_Y + ITEMPRICE_Y * x) });
		_ItemPriceTextRenderer->Off();

		GameEngineCollision* _ItemCollision = CreateCollision(CollisionOrder::Button);
		_ItemCollision->SetCollisionScale({ Texture->GetScale().X * 0.9f, Texture->GetScale().Y * 0.5f });
		_ItemCollision->SetCollisionPos({ GlobalValue::WinScale.X * ITEMCOLLISION_X, GlobalValue::WinScale.Y * (ITEMCOLLISION_START_Y + ITEMCOLLISION_Y * x) });
		_ItemCollision->Off();

		ShopItem[x]->ItemRenderer = _ItemRenderer;
		ShopItem[x]->ItemPriceTextRenderer = _ItemPriceTextRenderer;
		ShopItem[x]->ItemCollision = _ItemCollision;
	}
	ShopItemSetting();

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

	SleepUIUpdate(_Delta);
	ShopUIUpdate(_Delta);
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
	Inventory->Off();
	Player::MainPlayer->StopPlayer();
	ShopRenderer->On();
	CancelRenderer->On();
	CancelCollision->On();
	for (int x = 0; x < ShopItem.size(); x++)
	{
		ShopItem[x]->ItemRenderer->On();
		ShopItem[x]->ItemCollision->On();
		ShopItem[x]->ItemPriceTextRenderer->On();
}
	ContentInventory::MainInventory->SetPosInventoryShop();
}

void ContentUIManager::ShopUIOff()
{
	Inventory->On();
	Player::MainPlayer->SetIsUpdate(true);
	ShopRenderer->Off();
	CancelRenderer->Off();
	CancelCollision->Off();
	for (int x = 0; x < ShopItem.size(); x++)
	{
		ShopItem[x]->ItemRenderer->Off();
		ShopItem[x]->ItemCollision->Off();
		ShopItem[x]->ItemPriceTextRenderer->Off();
	}
	ContentInventory::MainInventory->SetPosInventoryItem();
}

void ContentUIManager::SleepUIUpdate(float _Delta)
{
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
void ContentUIManager::ShopUIUpdate(float _Delta)
{
	if (false == ShopRenderer->IsUpdate())
	{
		return;
	}

	if (true == GameEngineInput::IsDown(VK_LBUTTON) 
		&& true == CancelCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect))
	{
		ShopUIOff();
	}
}

void ContentUIManager::ShopItemSetting()
{
	for (int x = 0; x < ShopItem.size(); x++)
	{
		std::string _FileName = "";
		int _ItemPrice = 0;
		switch (x)
		{
		case 0:
			_FileName = "Shop_Seed_Parsnip.bmp";
			_ItemPrice = 20;
			break;
		case 1:
			_FileName = "Shop_Seed_Cauliflower.bmp";
			_ItemPrice = 30;
			break;
		case 2:
			_FileName = "Shop_Seed_Garlic.bmp";
			_ItemPrice = 40;
			break;
		case 3:
			_FileName = "Shop_Seed_Potato.bmp";
			_ItemPrice = 50;
			break;
		default:
			break;
		}
		ShopItem[x]->ItemRenderer->SetTexture(_FileName);
		ShopItem[x]->ItemPriceTextRenderer->SetText(std::to_string(_ItemPrice), 45, "Sandoll 미생");
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
