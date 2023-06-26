#pragma region
// MoneyValue
#define PLAYERMONEY_DISTANCE 0.0117f
#define SHOPMONEY_DISTANCE 0.0136f
#define SELLMONEY_DISTANCE 0.0153f
#define SELLMONEY_X 0.617f

// ShopValue
#define ITEMSELECT_START_X 0.609f
#define ITEMSELECT_START_Y 0.211f
#define ITEMSELECT_Y 0.1056f

#define ITEMRENDER_START_X 0.345f
#define ITEMRENDER_START_Y 0.21f
#define ITEMRENDER_Y 0.1055f

#define ITEMNAME_X 0.37f

#define ITEMPRICE_START_Y 0.185f
#define ITEMPRICE_X 0.84f
#define ITEMPRICE_Y 0.106f

#define ITEMCOLLISION_START_Y 0.7f
#define ITEMCOLLISION_X 0.605f
#define ITEMCOLLISION_Y 0.105f
#pragma endregion

#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "ContentUIManager.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "ContentMouse.h"
#include "ContentInventory.h"
#include "Player.h"
#include "ContentItem.h"

ContentUIManager* ContentUIManager::MainUI = nullptr;

ContentUIManager::ContentUIManager()
{
	MainUI = this;
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
	// Texture Load
	if (false == ResourcesManager::GetInst().IsLoadTexture("Clock.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\UI\\");
		// Clock UI
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Clock.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Clock_hand.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Clock_hand_Mask.bmp"));
		// Energy UI
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Energy.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("EnergyBar.bmp"));
		// MiniInventory UI
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Inventory.bmp"));
		// Sleep UI
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Sleep.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Yes.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_No.bmp"));
		// SleepLevelUI
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_SellBackGround.bmp"));
		// Money UI
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Money_0.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Money_1.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Money_2.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Money_3.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Money_4.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Money_5.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Money_6.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Money_7.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Money_8.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Money_9.bmp"));
		// Shop UI
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Shop_Pierre.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Cancel.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Shop_Select.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Shop_Seed_Parsnip.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Shop_Seed_Cauliflower.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Shop_Seed_Garlic.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Shop_Seed_Potato.bmp"));
		// ShippingBox UI
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_ShippingBox.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_ShippingBox_Inventory.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Ok_Button.bmp"));
	}

	// Sound Load
	if (nullptr == GameEngineSound::FindSound("purchase.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("purchase.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("cancel.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("money_up.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("pick_item.wav"));
	}
	
	// BasicUI
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("Clock.bmp");
	Clock = CreateUIRenderer("Clock.bmp", RenderOrder::UI);
	Clock->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	Clock->SetRenderPos({ GlobalValue::WinScale.X - Texture->GetScale().Half().X * RENDERRATIO, Texture->GetScale().Half().Y * RENDERRATIO });

	Texture = ResourcesManager::GetInst().FindTexture("Clock_hand.bmp");
	ClockHand = CreateUIRenderer("Clock_hand.bmp", RenderOrder::UI);
	ClockHand->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	ClockHand->SetRenderPos({ GlobalValue::WinScale.X - Texture->GetScale().Half().X * RENDERRATIO - 135, Texture->GetScale().Half().Y * RENDERRATIO + 5 });
	ClockHand->SetMaskTexture("Clock_hand_Mask.bmp");
	ClockHand->SetAngle(181.0f);

	Texture = ResourcesManager::GetInst().FindTexture("Energy.bmp");
	Energy = CreateUIRenderer("Energy.bmp", RenderOrder::UI);
	Energy->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	Energy->SetRenderPos({ GlobalValue::WinScale.X - Texture->GetScale().Half().X * RENDERRATIO, GlobalValue::WinScale.Y - Texture->GetScale().Half().Y * RENDERRATIO });

	EnergyBar = CreateUIRenderer("EnergyBar.bmp", RenderOrder::UI);
	EnergyBar->SetRenderScale(float4{6, EnergyValue } * RENDERRATIO);
	EnergyBar->SetRenderPos({ GlobalValue::WinScale.X - Texture->GetScale().Half().X * RENDERRATIO, GlobalValue::WinScale.Y - 6});

	DayTextRenderer = CreateUIRenderer(RenderOrder::UI);
	DayTextRenderer->SetText("월.    1", 30, "Sandoll 미생");
	DayTextRenderer->SetRenderPos({ GlobalValue::WinScale.X - 100, 13 });

	TimeTextRenderer = CreateUIRenderer(RenderOrder::UI);
	TimeTextRenderer->SetText("6 : 00 오전", 30, "Sandoll 미생");
	TimeTextRenderer->SetRenderPos({ GlobalValue::WinScale.X - 120, 82 });

	Inventory = CreateUIRenderer("UI_Inventory.bmp", RenderOrder::UI);
	InventoryDownRender();
	
	// MoneyUI
	Texture = ResourcesManager::GetInst().FindTexture("UI_Money_0.bmp");
	MoneyData& PlayerMoney = AllMoney[MoneyEnum::PlayerMoney];
	PlayerMoney.Init(float4{0.983f, 0.174f}, PLAYERMONEY_DISTANCE, Texture->GetScale() * 2.0f);

	MoneyData& ShopMoney = AllMoney[MoneyEnum::ShopPlayerMoney];
	ShopMoney.Init(float4{ 0.4235f, 0.637f }, SHOPMONEY_DISTANCE, Texture->GetScale() * 2.0f);

	MoneyData& CropsMoney = AllMoney[MoneyEnum::CropsMoney];
	CropsMoney.Init(0.15f, SELLMONEY_DISTANCE, Texture->GetScale() * 2.3f, "농사");

	MoneyData& ResourcesMoney = AllMoney[MoneyEnum::ResourcesMoney];
	ResourcesMoney.Init(0.3f, SELLMONEY_DISTANCE, Texture->GetScale() * 2.3f, "채집");

	MoneyData& FishingMoney = AllMoney[MoneyEnum::FishingMoney];
	FishingMoney.Init(0.45f, SELLMONEY_DISTANCE, Texture->GetScale() * 2.3f, "낚시");

	MoneyData& MiningMoney = AllMoney[MoneyEnum::MiningMoney];
	MiningMoney.Init(0.6f, SELLMONEY_DISTANCE, Texture->GetScale() * 2.3f, "채광");

	MoneyData& EtcMoney = AllMoney[MoneyEnum::EtcMoney];
	EtcMoney.Init(0.75f, SELLMONEY_DISTANCE, Texture->GetScale() * 2.3f, "기타");

	MoneyData& TotalMoney = AllMoney[MoneyEnum::TotalMoney];
	TotalMoney.Init(0.9f, SELLMONEY_DISTANCE, Texture->GetScale() * 2.3f, "총합");
	
	// SleepUI
	SleepUITexture = ResourcesManager::GetInst().FindTexture("UI_Sleep.bmp");
	SleepUIRenderer = CreateUIRenderer("UI_Sleep.bmp", RenderOrder::UIMouse);
	SleepUIRenderer->SetRenderPos({GlobalValue::WinScale.hX(), GlobalValue::WinScale.Y - SleepUITexture->GetScale().hY()});
	SleepUIRenderer->SetRenderScale(SleepUITexture->GetScale() * UIRenderRatio);
	SleepUIRenderer->Off();

	Texture = ResourcesManager::GetInst().FindTexture("UI_Yes.bmp");
	SleepYesRenderer = CreateUIRenderer("UI_Yes.bmp", RenderOrder::UIMouse);
	SleepYesRenderer->SetRenderPos({ GlobalValue::WinScale.hX() - 2, GlobalValue::WinScale.Y * 0.81f });
	SleepYesRenderer->SetRenderScale(Texture->GetScale() * 0.8145f);
	SleepYesRenderer->Off();
	SleepNoRenderer = CreateUIRenderer("UI_No.bmp", RenderOrder::UIMouse);
	SleepNoRenderer->SetRenderPos({ GlobalValue::WinScale.hX() - 2, GlobalValue::WinScale.Y * 0.895f });
	SleepNoRenderer->SetRenderScale(Texture->GetScale() * 0.8145f);
	SleepNoRenderer->Off();

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

		GameEngineRenderer* _ItemNameTextRenderer = CreateUIRenderer(RenderOrder::UI);
		_ItemNameTextRenderer->SetText(" ");
		_ItemNameTextRenderer->SetRenderPos({ GlobalValue::WinScale.X * ITEMNAME_X, GlobalValue::WinScale.Y * (ITEMPRICE_START_Y + ITEMPRICE_Y * x) });
		_ItemNameTextRenderer->Off();

		GameEngineRenderer* _ItemPriceTextRenderer = CreateUIRenderer(RenderOrder::UI);
		_ItemPriceTextRenderer->SetText(" ");
		_ItemPriceTextRenderer->SetRenderPos({ GlobalValue::WinScale.X * ITEMPRICE_X, GlobalValue::WinScale.Y * (ITEMPRICE_START_Y + ITEMPRICE_Y * x) });
		_ItemPriceTextRenderer->Off();

		GameEngineCollision* _ItemCollision = CreateCollision(CollisionOrder::Button);
		_ItemCollision->SetCollisionScale({ Texture->GetScale().X * 0.9f, Texture->GetScale().Y * 0.5f });
		_ItemCollision->SetCollisionPos({ GlobalValue::WinScale.X * ITEMCOLLISION_X, GlobalValue::WinScale.Y * (ITEMCOLLISION_START_Y + ITEMCOLLISION_Y * x) });
		_ItemCollision->Off();

		ShopItem[x]->ItemRenderer = _ItemRenderer;
		ShopItem[x]->ItemNameTextRenderer = _ItemNameTextRenderer;
		ShopItem[x]->ItemPriceTextRenderer = _ItemPriceTextRenderer;
		ShopItem[x]->ItemCollision = _ItemCollision;
	}
	ShopItemSetting();
	// PrevSelectRenderer = CreateUIRenderer(RenderOrder::UI);
	// NextSelectRenderer = CreateUIRenderer(RenderOrder::UI);

	// ShippingBox UI
	ShipInventoryRenderer = CreateUIRenderer("UI_ShippingBox_Inventory.bmp", RenderOrder::UI);
	ShipInventoryRenderer->Off();
	SellInventoryRenderer = CreateUIRenderer("UI_ShippingBox.bmp", RenderOrder::UI);
	SellInventoryRenderer->Off();
	SellItemRenderer = CreateUIRenderer(RenderOrder::UI);
	SellItemRenderer->Off();
	SellItemCollision = CreateCollision(CollisionOrder::Inventory_Item);
	SellItemCollision->Off();
	OkButtonRenderer = CreateUIRenderer("Ok_Button.bmp", RenderOrder::UI);
	OkButtonRenderer->Off();
	OkButtonCollision = CreateCollision(CollisionOrder::Button);
	OkButtonCollision->Off();

	ShipInventoryRenderer->SetRenderPos({GlobalValue::WinScale.hX(), GlobalValue::WinScale.Y * 0.8f});
	Texture = ResourcesManager::GetInst().FindTexture("UI_ShippingBox.bmp");
	SellInventoryRenderer->SetRenderPos({ GlobalValue::WinScale.hX(), GlobalValue::WinScale.Y * 0.6f });
	SellInventoryRenderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	SellItemRenderer->SetRenderPos({ GlobalValue::WinScale.hX(), GlobalValue::WinScale.Y * 0.6f });
	SellItemRenderer->SetRenderScale(TILESIZE * RENDERRATIO);
	SellItemCollision->SetCollisionScale(TILESIZE);
	OkButtonRenderer->SetRenderPos({ GlobalValue::WinScale.X * 0.8f, GlobalValue::WinScale.Y * 0.9f });
	OkButtonCollision->SetCollisionScale(TILESIZE);


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
	if (true == GameEngineInput::IsDown(VK_F6))
	{
		ClockHand->AddAngle(10.0f);
		// EnergyValue -= 10.0f;
	}
	
	EnergyBar->SetRenderScale(float4{ 6, EnergyValue } *RENDERRATIO);
	DayUIUpdate(_Delta);
	SleepUIUpdate(_Delta);
	ShopUIUpdate(_Delta);
	ShippingUIUpdate(_Delta);
	AllMoney[MoneyEnum::PlayerMoney].CurMoney = PlayerMoney;
	AllMoney[MoneyEnum::ShopPlayerMoney].CurMoney = PlayerMoney;
	for (std::pair<const MoneyEnum, MoneyData>& _Data : AllMoney)
	{
		MoneyUIUpdate(&_Data.second, _Delta);
	}
}

void ContentUIManager::BasicUIOn()
{
	Clock->On();
	ClockHand->On();
	Energy->On();
	EnergyBar->On();
	Inventory->On();
	DayTextRenderer->On();
	TimeTextRenderer->On();
	AllMoney[MoneyEnum::PlayerMoney].IsUpdate = true;
}

void ContentUIManager::BasicUIOff()
{
	Clock->Off();
	ClockHand->Off();
	Energy->Off();
	EnergyBar->Off();
	Inventory->Off();
	DayTextRenderer->Off();
	TimeTextRenderer->Off();
	AllMoney[MoneyEnum::PlayerMoney].MoneyRendererOff();
	AllMoney[MoneyEnum::PlayerMoney].IsUpdate = false;
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
	if (true == ShopRenderer->IsUpdate())
	{
		return;
	}

	Inventory->Off();
	Player::MainPlayer->StopPlayer();
	ShopRenderer->On();
	CancelRenderer->On();
	CancelCollision->On();
	AllMoney[MoneyEnum::ShopPlayerMoney].IsUpdate = true;
	AllMoney[MoneyEnum::ShopPlayerMoney].CurMoney = PlayerMoney;
	AllMoney[MoneyEnum::ShopPlayerMoney].CurTextMoney = PlayerMoney + 1;
	for (int x = 0; x < ShopItem.size(); x++)
	{
		ShopItem[x]->ItemRenderer->On();
		ShopItem[x]->ItemCollision->On();
		ShopItem[x]->ItemNameTextRenderer->On();
		ShopItem[x]->ItemPriceTextRenderer->On();
	}
	ContentInventory::MainInventory->SetPosInventoryShop();
}

void ContentUIManager::ShopUIOff()
{
	if (false == ShopRenderer->IsUpdate())
	{
		return;
	}
	Inventory->On();
	Player::MainPlayer->SetIsUpdate(true);
	ShopRenderer->Off();
	CancelRenderer->Off();
	CancelCollision->Off();
	ItemSelectRenderer->Off();
	AllMoney[MoneyEnum::ShopPlayerMoney].IsUpdate = false;
	AllMoney[MoneyEnum::ShopPlayerMoney].MoneyRendererOff();
	for (int x = 0; x < ShopItem.size(); x++)
	{
		ShopItem[x]->ItemRenderer->Off();
		ShopItem[x]->ItemCollision->Off();
		ShopItem[x]->ItemNameTextRenderer->Off();
		ShopItem[x]->ItemPriceTextRenderer->Off();
	}
	ContentInventory::MainInventory->SetPosInventoryItem();
}

void ContentUIManager::DayUIUpdate(float _Delta)
{
	if (false == DayTextRenderer->IsUpdate())
	{
		return;
	}

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

	// Time Code
	static float PerTime = 1.0f;
	if (0.0f >= PerTime)
	{
		std::string MinuteString = "";
		MinuteValue += 10;
		if (0 == MinuteValue)
		{
			MinuteString = "00";
		}
		else if (60 == MinuteValue)
		{
			HourValue += 1;
			MinuteValue = 0;
			MinuteString = "00";
		}
		else
		{
			MinuteString = std::to_string(MinuteValue);
		}

		if ( 12 == HourValue && false ==  Meridiem && 0 == MinuteValue)
		{
			Meridiem = true;
		}
		else if (12 == HourValue && true == Meridiem && 0 == MinuteValue)
		{
			Meridiem = false;
		}
		else if (13 == HourValue)
		{
			HourValue = 1;
		}

		std::string MeridiemString = "";
		if (false == Meridiem)
		{
			MeridiemString = " 오전";
		}
		else
		{
			MeridiemString = " 오후";
		}

		TimeTextRenderer->SetText(std::to_string(HourValue) + " : " + MinuteString + MeridiemString, 30, "Sandoll 미생");
		ClockHand->AddAngle(1.5f);
		PerTime = 1.0f;
	}
	PerTime -= _Delta;
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

	if (false == SleepUIRenderer->IsUpdate() || 0.8f > UIRenderRatio)
	{
		return;
	}

	if (true == SleepYesCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect))
	{
		SleepYesRenderer->On();
		if (true == GameEngineInput::IsDown(VK_LBUTTON))
		{
			BasicUIOff();
			SleepUIRenderer->Off();
			SleepYesCollision->Off();
			SleepNoCollision->Off();
			SleepYesRenderer->Off();
			GameEngineCore::ChangeLevel("SleepLevel");
		}
	}
	else if (true == SleepYesRenderer->IsUpdate() 
		&& false == SleepYesCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect))
	{
		SleepYesRenderer->Off();
	}
	
	if (true == SleepNoCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect))
	{
		SleepNoRenderer->On();
		if (true == GameEngineInput::IsDown(VK_LBUTTON))
		{
			ContentInventory::MainInventory->On();
			Inventory->On();
			Player::MainPlayer->SetIsUpdate(true);
			SleepUIRenderer->Off();
			SleepYesCollision->Off();
			SleepNoCollision->Off();
			SleepNoRenderer->Off();
		}
	}
	else if (true == SleepNoRenderer->IsUpdate()
		&& false == SleepNoCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect))
	{
		SleepNoRenderer->Off();
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

	bool IsCollision = false;
	for (int x = 0; x < ShopItem.size(); x++)
	{
		if (true == ShopItem[x]->ItemCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect))
		{
			ItemSelectRenderer->SetRenderPos({ GlobalValue::WinScale.X * ITEMSELECT_START_X, GlobalValue::WinScale.Y * (ITEMSELECT_START_Y + ITEMSELECT_Y * x)});
			IsCollision = true;
			ItemSelectRenderer->On();
		}

		if (true == GameEngineInput::IsDown(VK_LBUTTON)
			&& true == ShopItem[x]->ItemCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect))
		{
			int CheckMoney = PlayerMoney;
			CheckMoney -= ShopItem[x]->ItemBuyPrice;
			if (0 > CheckMoney)
			{
				EffectPlayer = GameEngineSound::SoundPlay("cancel.wav");
				return;
			}

			if (true == ContentMouse::MainMouse->GetItemRenderer()->IsUpdate())
			{
				std::string CurItemName = ContentMouse::MainMouse->GetPickItem()->GetItemName();
				if (("Seed_Parsnip.bmp" == CurItemName && 0 == x)
					|| ("Seed_Cauliflower.bmp" == CurItemName && 1 == x)
					|| ("Seed_Garlic.bmp" == CurItemName && 2 == x)
					|| ("Seed_Potato.bmp" == CurItemName && 3 == x))
				{
					ContentMouse::MainMouse->GetPickItem()->PlusItemCount(1);
					ContentMouse::MainMouse->SetItemCountRenderer(ContentMouse::MainMouse->GetPickItem()->GetItemCount());
					ContentMouse::MainMouse->GetItemCountRenderer()->On();
					PlayerMoney -= ShopItem[x]->ItemBuyPrice;
					EffectPlayer = GameEngineSound::SoundPlay("purchase.wav");
				}
				else
				{
					EffectPlayer = GameEngineSound::SoundPlay("cancel.wav");
				}
			}
			else
			{
				ContentItem* _Item = GetLevel()->CreateActor<ContentItem>();
				switch (x)
				{
				case 0:
					_Item->Init("Seed_Parsnip.bmp", ItemType::Seed);
					break;
				case 1:
					_Item->Init("Seed_Cauliflower.bmp", ItemType::Seed);
					break;
				case 2:
					_Item->Init("Seed_Garlic.bmp", ItemType::Seed);
					break;
				case 3:
					_Item->Init("Seed_Potato.bmp", ItemType::Seed);
					break;
				default:
					break;
				}

				if (true == ContentInventory::MainInventory->IsFull(_Item))
				{
					_Item->Death();
					EffectPlayer = GameEngineSound::SoundPlay("cancel.wav");
					return;
				}
				ContentMouse::MainMouse->GetItemRenderer()->SetTexture("Inventory_" + _Item->GetItemName());
				ContentMouse::MainMouse->GetItemRenderer()->On();
				ContentMouse::MainMouse->SetPickItem(_Item);
				PlayerMoney -= ShopItem[x]->ItemBuyPrice;
				EffectPlayer = GameEngineSound::SoundPlay("purchase.wav");
			}
		}
	}

	if (false == IsCollision)
	{
		ItemSelectRenderer->Off();
	}
}

void ContentUIManager::ShopItemSetting()
{
	for (int x = 0; x < ShopItem.size(); x++)
	{
		std::string _FileName = "";
		switch (x)
		{
		case 0:
			_FileName = "Shop_Seed_Parsnip.bmp";
			ShopItem[x]->ItemBuyPrice = 20;
			ShopItem[x]->ItemNameTextRenderer->SetText("파스닙 씨앗", 45, "Sandoll 미생");
			break;
		case 1:
			_FileName = "Shop_Seed_Cauliflower.bmp";
			ShopItem[x]->ItemBuyPrice = 80;
			ShopItem[x]->ItemNameTextRenderer->SetText("콜리플라워 씨앗", 45, "Sandoll 미생");
			break;
		case 2:
			_FileName = "Shop_Seed_Garlic.bmp";
			ShopItem[x]->ItemBuyPrice = 40;
			ShopItem[x]->ItemNameTextRenderer->SetText("마늘 씨앗", 45, "Sandoll 미생");
			break;
		case 3:
			_FileName = "Shop_Seed_Potato.bmp";
			ShopItem[x]->ItemBuyPrice = 50;
			ShopItem[x]->ItemNameTextRenderer->SetText("감자 씨앗", 45, "Sandoll 미생");
			break;
		default:
			break;
		}
		ShopItem[x]->ItemRenderer->SetTexture(_FileName);
		ShopItem[x]->ItemPriceTextRenderer->SetText(std::to_string(ShopItem[x]->ItemBuyPrice), 45, "Sandoll 미생");
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

void ContentUIManager::SellCurItem()
{
	if (nullptr == SellItem)
	{
		MsgBoxAssert("판매할 아이템이 없는데 판매하려고 했습니다.");
	}

	switch (SellItem->GetItemType())
	{
	case Resources:
		AllMoney[MoneyEnum::ResourcesMoney].CurMoney += SellItem->GetItemPrice() * SellItem->GetItemCount();
		AllMoney[MoneyEnum::TotalMoney].CurMoney += SellItem->GetItemPrice() * SellItem->GetItemCount();
		break;
	case Crops:
		AllMoney[MoneyEnum::CropsMoney].CurMoney = SellItem->GetItemPrice() * SellItem->GetItemCount();
		AllMoney[MoneyEnum::TotalMoney].CurMoney += SellItem->GetItemPrice() * SellItem->GetItemCount();
		break;
	case Seed:
		AllMoney[MoneyEnum::EtcMoney].CurMoney = SellItem->GetItemPrice() * SellItem->GetItemCount();
		AllMoney[MoneyEnum::TotalMoney].CurMoney += SellItem->GetItemPrice() * SellItem->GetItemCount();
		break;
	default:
		MsgBoxAssert("판매할 수 없는 아이템을 판매하려고 했습니다.");
		break;
	}
}

void ContentUIManager::ShippingUIOn()
{
	SellItemCollision->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + float4{ GlobalValue::WinScale.hX(), GlobalValue::WinScale.Y * 0.6f });
	OkButtonCollision->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + float4{ GlobalValue::WinScale.X * 0.8f, GlobalValue::WinScale.Y * 0.9f });
	Inventory->Off();
	Player::MainPlayer->StopPlayer();
	ShipInventoryRenderer->On();
	SellInventoryRenderer->On();
	SellItemCollision->On();
	OkButtonRenderer->On();
	OkButtonCollision->On();
	ContentInventory::MainInventory->SetPosShippingBox();
}

void ContentUIManager::ShippingUIOff()
{
	Inventory->On();
	Player::MainPlayer->SetIsUpdate(true);
	ShipInventoryRenderer->Off();
	SellItemRenderer->Off();
	SellInventoryRenderer->Off();
	SellItemCollision->Off();
	OkButtonRenderer->Off();
	OkButtonCollision->Off();
	ContentInventory::MainInventory->SetPosInventoryItem();
}

void ContentUIManager::ShippingUIUpdate(float _Delta)
{
	if (false == ShipInventoryRenderer->IsUpdate())
	{
		return;
	}

	if (true == OkButtonCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect)
		&& true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ShippingUIOff();
	}

	if (true == SellItemCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect)
		&& true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		if (nullptr == SellItem)
		{
			return;
		}

		ContentInventory::MainInventory->PushItem(SellItem);
		SellItemRenderer->Off();
		SellItem = nullptr;
		EffectPlayer = GameEngineSound::SoundPlay("pick_item.wav");
	}
}


// MoneyData Init

void ContentUIManager::MoneyData::On()
{
	IsUpdate = true;
	BackRenderer->On();
	TextRenderer->On();
}
void ContentUIManager::MoneyData::Off()
{
	IsUpdate = false;
	BackRenderer->Off();
	TextRenderer->Off();
}

void ContentUIManager::MoneyData::Init(const float4& _MoneyRender, const float _XDistance, const float4& _RenderScale)
{
	MoneyRenderer.resize(8);
	for (int x = 0; x < MoneyRenderer.size(); x++)
	{
		MoneyRenderer[x] = ContentUIManager::MainUI->CreateUIRenderer("UI_Money_0.bmp", RenderOrder::UI_Money);
		MoneyRenderer[x]->SetRenderPos({ GlobalValue::WinScale.X * (_MoneyRender.X - x * _XDistance), GlobalValue::WinScale.Y * _MoneyRender.Y });
		MoneyRenderer[x]->SetRenderScale(_RenderScale);
		MoneyRenderer[x]->Off();
	}
}

void ContentUIManager::MoneyData::Init(const float _BackGround_Y, const float _XDistance, const float4& _RenderScale, const std::string& _Text)
{
	MoneyRenderer.resize(8);
	for (int x = 0; x < MoneyRenderer.size(); x++)
	{
		MoneyRenderer[x] = ContentUIManager::MainUI->CreateUIRenderer("UI_Money_0.bmp", RenderOrder::UI_Money);
		MoneyRenderer[x]->SetRenderPos({ GlobalValue::WinScale.X * (0.617f - x * _XDistance), GlobalValue::WinScale.Y * (_BackGround_Y + 0.005f) });
		MoneyRenderer[x]->SetRenderScale(_RenderScale);
		MoneyRenderer[x]->Off();
	}

	BackRenderer = ContentUIManager::MainUI->CreateUIRenderer(RenderOrder::UI);
	BackRenderer->SetTexture("UI_SellBackGround.bmp");
	BackRenderer->SetRenderPos({ GlobalValue::WinScale.X * 0.5f, GlobalValue::WinScale.Y * _BackGround_Y });
	BackRenderer->Off();
	TextRenderer = ContentUIManager::MainUI->CreateUIRenderer(RenderOrder::UI);
	TextRenderer->SetText(_Text, 50, "Sandoll 미생");
	TextRenderer->SetRenderPos({ GlobalValue::WinScale.X * 0.365f, GlobalValue::WinScale.Y * (_BackGround_Y - 0.03f) });
	TextRenderer->Off();
}


void ContentUIManager::MoneyData::MoneyRendererOff()
{
	for (int x = 0; x < MoneyRenderer.size(); x++)
	{
		MoneyRenderer[x]->Off();
	}
}

void ContentUIManager::MoneyUIUpdate(MoneyData* _CurMoney, float _Delta)
{
	if (false == _CurMoney->IsUpdate)
	{
		return;
	}

	if (_CurMoney->CurMoney > _CurMoney->CurTextMoney)
	{
		_CurMoney->CurTextMoney += static_cast<int>(MoneyUpSpeed * _Delta);
		if (_CurMoney->CurMoney < _CurMoney->CurTextMoney)
		{
			_CurMoney->CurTextMoney = _CurMoney->CurMoney;
		}
	}
	else if (_CurMoney->CurMoney < _CurMoney->CurTextMoney)
	{
		_CurMoney->CurTextMoney -= static_cast<int>(MoneyUpSpeed * _Delta);
		if (_CurMoney->CurMoney > _CurMoney->CurTextMoney)
		{
			_CurMoney->CurTextMoney = _CurMoney->CurMoney;
		}
	}
	else if (false == _CurMoney->SoundValue && _CurMoney->CurMoney == _CurMoney->CurTextMoney)
	{
		_CurMoney->SoundValue = true;
		_CurMoney->MoneySound.SetLoop(0);
	}

	if (true == _CurMoney->SoundValue && false == _CurMoney->IsUpdateEnd())
	{
		_CurMoney->MoneySound = GameEngineSound::SoundPlay("money_up.wav", 10000);
		_CurMoney->SoundValue = false;
	}

	// Calcu Digit
	int MoneyDigit = 0;
	int CheckValue = _CurMoney->CurTextMoney;
	while (0 != CheckValue / 10)
	{
		CheckValue /= 10;
		++MoneyDigit;
	}

	// Renderer On to Digit number
	CheckValue = _CurMoney->CurTextMoney;
	for (int x = 0; x < _CurMoney->MoneyRenderer.size(); x++)
	{
		if (x > MoneyDigit)
		{
			_CurMoney->MoneyRenderer[x]->Off();
			continue;
		}
		int MoneyString = (CheckValue % 10);
		CheckValue /= 10;
		_CurMoney->MoneyRenderer[x]->SetTexture("UI_Money_" + std::to_string(MoneyString) + ".bmp");
		_CurMoney->MoneyRenderer[x]->On();
	}
}

void ContentUIManager::SleepMoneyRenderOff()
{
	std::map<MoneyEnum, MoneyData>::iterator StartIter = AllMoney.find(CropsMoney);
	std::map<MoneyEnum, MoneyData>::iterator EndIter = AllMoney.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		MoneyData* _CurData = &StartIter->second;
		_CurData->MoneyRendererOff();
		_CurData->IsUpdate = false;
		_CurData->CurMoney = 0;
		_CurData->CurTextMoney = 0;
		_CurData->BackRenderer->Off();
		_CurData->TextRenderer->Off();
	}
}
