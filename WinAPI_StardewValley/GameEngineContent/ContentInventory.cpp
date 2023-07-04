#define MAXSIZE 12

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentInventory.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "Player.h"
#include "ContentItem.h"
#include "ContentUIManager.h"
#include "ContentMouse.h"


ContentInventory* ContentInventory::MainInventory = nullptr;

ContentInventory::ContentInventory()
{
}

ContentInventory::~ContentInventory()
{
	for (int x = 0; x < AllItem.size(); x++)
	{
		if (nullptr != AllItem[x])
		{
			delete AllItem[x];
			AllItem[x] = nullptr;
		}
	}
}

void ContentInventory::Start()
{
	// Texture Load
	if (false == ResourcesManager::GetInst().IsLoadTexture("Inventory.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\UI\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Inventory.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Inventory_Select.bmp"));
	}

	// Sound Load
	if (nullptr == GameEngineSound::FindSound("toolSwap.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("toolSwap.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("sell.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("shipping_in.wav"));
	}

	// Init Inventory
	AllItem.resize(MAXSIZE);
	for (int x = 0; x < AllItem.size(); x++)
	{
		AllItem[x] = new InventoryItemData();

		GameEngineRenderer* _ItemRenderer = CreateUIRenderer(RenderOrder::Inventory_Item);
		_ItemRenderer->SetRenderScale(TILESIZE * RENDERRATIO);
		_ItemRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });
		_ItemRenderer->Off();

		GameEngineCollision* _ItemCollision = CreateCollision(CollisionOrder::Inventory_Item);
		_ItemCollision->SetCollisionScale(TILESIZE);
		_ItemCollision->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + float4{ GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });

		GameEngineRenderer* _ItemCountRenderer = CreateUIRenderer(RenderOrder::Inventory_Item);
		_ItemCountRenderer->SetText(" ");
		_ItemCountRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.29f + 0.04f * x), GlobalValue::WinScale.Y * (0.955f - PosSettingValue) });

		AllItem[x]->ItemRenderer = _ItemRenderer;
		AllItem[x]->ItemCollision = _ItemCollision;
		AllItem[x]->ItemCountRenderer = _ItemCountRenderer;
	}

	// Create Renderer
	InventoryRenderer = CreateUIRenderer(RenderOrder::UI);
	CurIndexRenderer = CreateUIRenderer(RenderOrder::UIMouse);

	// Renderer Setting
	InventoryRenderer->SetTexture("Inventory.bmp");
	InventoryRenderer->SetRenderPos(GlobalValue::WinScale.Half());
	InventoryRenderer->Off();

	CurIndexRenderer->SetTexture("UI_Inventory_Select.bmp");;

	// Inventory Text
	PlayerNameText = CreateUIRenderer(RenderOrder::UI);
	PlayerNameText->SetText("Player", 40, "Sandoll 미생");
	PlayerNameText->SetRenderPos({ GlobalValue::WinScale.X * 0.325f, GlobalValue::WinScale.Y * 0.73f });
	PlayerNameText->Off();

	FarmNameText = CreateUIRenderer(RenderOrder::UI);
	FarmNameText->SetText("Player의 농장", 48, "Sandoll 미생");
	FarmNameText->SetRenderPos({ GlobalValue::WinScale.X * 0.53f, GlobalValue::WinScale.Y * 0.53f });
	FarmNameText->Off();

	PlayerMoneyText = CreateUIRenderer(RenderOrder::UI);
	PlayerMoneyText->SetText("현재 소지금 : 500 골드", 48, "Sandoll 미생");
	PlayerMoneyText->SetRenderPos({ GlobalValue::WinScale.X * 0.5f, GlobalValue::WinScale.Y * 0.6f });
	PlayerMoneyText->Off();

	TotalMoneyText = CreateUIRenderer(RenderOrder::UI);
	TotalMoneyText->SetText("총 소득금 : 0 골드", 48, "Sandoll 미생");
	TotalMoneyText->SetRenderPos({ GlobalValue::WinScale.X * 0.52f, GlobalValue::WinScale.Y * 0.65f });
	TotalMoneyText->Off();

	// Player Default Item
	GameEngineLevel* CurLevel = GetLevel();
	ContentItem* Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
	Item->Init("axe.bmp", ItemType::Axe);
	PushItem(Item);

	Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
	Item->Init("hoe.bmp", ItemType::Hoe);
	PushItem(Item);

	Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
	Item->Init("pickaxe.bmp", ItemType::PickAxe);
	PushItem(Item);

	Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
	Item->Init("wateringcan.bmp", ItemType::WateringCan);
	PushItem(Item);

	Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
	Item->Init("sickle.bmp", ItemType::Sickle);
	PushItem(Item);
}

void ContentInventory::PushItem(ContentItem* _Item)
{
	ContentItem* Find = FindItem(_Item);
	if (nullptr == Find)
	{
		int PushIndex = BlankSpace();

		// Item Off
		_Item->Off();
		_Item->Collision->Off();
		
		// Inventory Item & ItemCount Renderer
		AllItem[PushIndex]->ItemRenderer->SetTexture("Inventory_" + _Item->GetItemName());
		AllItem[PushIndex]->ItemRenderer->On();

		AllItem[PushIndex]->Item = _Item;
	}
	else if (nullptr != Find)
	{
		Find->PlusItemCount(_Item->GetItemCount());
		_Item->Death();
	}

}

void ContentInventory::PopItem(const int _Index)
{
	if (nullptr == AllItem[_Index]->Item)
	{
		return;
	}

	AllItem[_Index]->ItemCountRenderer->SetText(" ");
	AllItem[_Index]->ItemRenderer->Off();
	AllItem[_Index]->Item = nullptr;
}

void ContentInventory::DeathItem(const int _Index)
{
	if (nullptr == AllItem[_Index]->Item)
	{
		return;
	}

	AllItem[_Index]->ItemCountRenderer->SetText(" ");
	AllItem[_Index]->ItemRenderer->Off();
	AllItem[_Index]->Item->Death();
	AllItem[_Index]->Item = nullptr;
}

	
bool ContentInventory::IsFull(const ContentItem* _Item)
{
	int Index = BlankSpace();

	if (-1 == Index)
	{
		if (nullptr != FindItem(_Item))
		{
			return false;
		}
		return true;
	}
	return false;
}

ContentItem* ContentInventory::FindItem(const ContentItem* _Item, int* _ResultIndex)
{
	for (int x = 0; x < AllItem.size(); x++)
	{
		if (nullptr == AllItem[x]->Item)
		{
			continue;
		}

		if (AllItem[x]->Item->GetItemName() == _Item->GetItemName())
		{
			if (nullptr != _ResultIndex)
			{
				*_ResultIndex = x;
			}
			return  AllItem[x]->Item;
		}
	}
	return nullptr;
}

int ContentInventory::BlankSpace()
{
	for (int x = 0; x < AllItem.size(); x++)
	{
		if (nullptr == AllItem[x]->Item)
		{
			return x;
		}
	}
	return -1;
}

void ContentInventory::SetPosInventoryItem()
{
	for (int x = 0; x < AllItem.size(); x++)
	{
		AllItem[x]->ItemCollision->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + float4{GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * (0.945f - PosSettingValue )});
		AllItem[x]->ItemCountRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.29f + 0.04f * x), GlobalValue::WinScale.Y * (0.955f - PosSettingValue) });

		if (nullptr != AllItem[x]->ItemRenderer)
		{
			AllItem[x]->ItemRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });
		}
	}
}

void ContentInventory::SetPosInventoryShop()
{
	for (int x = 0; x < AllItem.size(); x++)
	{
		AllItem[x]->ItemCollision->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + float4{ GlobalValue::WinScale.X * (0.48f + 0.036f * x), GlobalValue::WinScale.Y * 0.66f });
		AllItem[x]->ItemCountRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.49f + 0.036f * x), GlobalValue::WinScale.Y * 0.67f });

		if (nullptr != AllItem[x]->ItemRenderer)
		{
			AllItem[x]->ItemRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.48f + 0.036f * x), GlobalValue::WinScale.Y * 0.66f });
		}
	}
}

void ContentInventory::SetPosShippingBox()
{
	for (int x = 0; x < AllItem.size(); x++)
	{
		AllItem[x]->ItemCollision->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + float4{ GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * 0.715f });
		AllItem[x]->ItemCountRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.29f + 0.04f * x), GlobalValue::WinScale.Y * 0.725f });

		if (nullptr != AllItem[x]->ItemRenderer)
		{
			AllItem[x]->ItemRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * 0.715f });
		}
	}
}

void ContentInventory::UseItem(ContentItem* _Item)
{
	if (AllItem[CurIndex]->Item->GetItemName() != _Item->GetItemName())
	{
		MsgBoxAssert("현재 인덱스와 사용하려는 아이템의 인덱스가 맞지 않습니다.");
	}

	int ItemIndex = 0;
	ContentItem* Find = FindItem(_Item, &ItemIndex);
	if (nullptr == Find)
	{
		MsgBoxAssert("인벤토리에 없는 아이템을 사용하려고 했습니다.");
	}

	if (1 == AllItem[CurIndex]->Item->GetItemCount())
	{
		DeathItem(CurIndex);
	}
	else
	{
		AllItem[CurIndex]->Item->MinusItemCount(1);
	}
}


void ContentInventory::Update(float _Delta)
{
	CurIndexUpdate();

	// CollisionPos Update
	if (true == ContentUIManager::MainUI->Inventory->IsUpdate())
	{
		for (int x = 0; x < AllItem.size(); x++)
		{
			if (nullptr == AllItem[x])
			{
				continue;
			}
			AllItem[x]->ItemCollision->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + float4{ GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });
		}
	}

	// ItemCountRenderer Update
	for (int x = 0; x < AllItem.size(); x++)
	{
		if (nullptr == AllItem[x]->Item)
		{
			continue;
		}

		if (1 == AllItem[x]->Item->GetItemCount())
		{
			AllItem[x]->ItemCountRenderer->SetText(" ");
			continue;
		}
		AllItem[x]->ItemCountRenderer->SetText(std::to_string(AllItem[x]->Item->GetItemCount()), 20, "Sandoll 미생");
	}

	// Mouse Interaction
	bool IsCollision = false;
	for (int x = 0; x < AllItem.size(); x++)
	{
		if (true == AllItem[x]->ItemCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect))
		{
			ItemPriceUpdate(x);
			IsCollision = true;
		}

		if (false == IsCollision)
		{
			ContentMouse::MainMouse->ItemPriceOff();
		}

		if (true == AllItem[x]->ItemCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect)
			&& true == GameEngineInput::IsDown(VK_LBUTTON))
		{
			if (true == ContentUIManager::MainUI->Inventory->IsUpdate())
			{
				CurIndex = x;
				EffectPlayer = GameEngineSound::SoundPlay("toolSwap.wav");
				return;
			}

			InventoryUpdate(x);
			ShopInventoryUpdate(x);
			ShippingInventoryUpdate(x);
		}
	}

	// Inventory On/Off
	if (true == ContentUIManager::MainUI->ShopRenderer->IsUpdate() || true == ContentUIManager::MainUI->ShipInventoryRenderer->IsUpdate())
	{
		return;
	}

	if (true == InventoryRenderer->IsUpdate())
	{
		PlayerMoneyText->SetText("현재 소지금 : " + std::to_string(ContentUIManager::MainUI->PlayerMoney) + " 골드", 48, "Sandoll 미생");
		TotalMoneyText->SetText("총 소득금 : " + std::to_string(ContentUIManager::MainUI->TotalGetMoney) + " 골드", 48, "Sandoll 미생");
	}

	if (true == GameEngineInput::IsDown('E') || true == GameEngineInput::IsDown(VK_ESCAPE))
	{
		if (true == InventoryRenderer->IsUpdate())
		{
			// Inventory Off
			InventoryRenderer->Off();
			PlayerNameText->Off();
			FarmNameText->Off();
			PlayerMoneyText->Off();
			TotalMoneyText->Off();
			ContentUIManager::MainUI->Inventory->On();
			PosSettingValue = 0.0f;
			SetPosInventoryItem();

			Player::MainPlayer->SetIsUpdate(true);
		}
		else
		{
			// Inventory On
			InventoryRenderer->On();
			PlayerNameText->On();
			FarmNameText->On();
			PlayerMoneyText->On();
			PlayerMoneyText->SetText("현재 소지금 : " + std::to_string(ContentUIManager::MainUI->PlayerMoney) +" 골드", 48, "Sandoll 미생");
			TotalMoneyText->On();
			TotalMoneyText->SetText("총 소득금 : "+ std::to_string(ContentUIManager::MainUI->TotalGetMoney) + " 골드", 48, "Sandoll 미생");
			ContentUIManager::MainUI->Inventory->Off();
			PosSettingValue = 0.702f;
			SetPosInventoryItem();

			Player::MainPlayer->StopPlayer();
		}
	}
}

void ContentInventory::CurIndexUpdate()
{
	if (false == ContentUIManager::MainUI->Inventory->IsUpdate() && false == InventoryRenderer->IsUpdate())
	{
		CurIndexRenderer->Off();
		return;
	}

	if (false == CurIndexRenderer->IsUpdate())
	{
		CurIndexRenderer->On();
	}

	// Change CurIndex
	for (int i = '0'; i <= '9'; i++)
	{
		if (true == GameEngineInput::IsDown('0'))
		{
			EffectPlayer = GameEngineSound::SoundPlay("toolSwap.wav");
			CurIndex = 9;
		}
		else if (true == GameEngineInput::IsDown(i))
		{
			EffectPlayer = GameEngineSound::SoundPlay("toolSwap.wav");
			CurIndex = static_cast<int>(i) - '0' - 1;
		}
	}

	if (true == GameEngineInput::IsDown('-'))
	{
		EffectPlayer = GameEngineSound::SoundPlay("toolSwap.wav");
		CurIndex = 10;
	}
	else if (true == GameEngineInput::IsDown('='))
	{
		EffectPlayer = GameEngineSound::SoundPlay("toolSwap.wav");
		CurIndex = 11;
	}

	// CurIndexRenderer
	CurIndexRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.28f + 0.04f * CurIndex), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });
}

void ContentInventory::ItemPriceUpdate(int _CurIndex)
{
	if (false == ContentUIManager::MainUI->ShopRenderer->IsUpdate() 
		|| nullptr == AllItem[_CurIndex]->Item 
		|| true == ContentMouse::MainMouse->GetItemRenderer()->IsUpdate()
		|| 0 == AllItem[_CurIndex]->Item->GetItemPrice())
	{
		return;
	}

	ContentMouse::MainMouse->ItemPriceOn();
	ContentMouse::MainMouse->SetItemPrice(AllItem[_CurIndex]->Item->GetItemPrice() * AllItem[_CurIndex]->Item->GetItemCount());
}

void ContentInventory::InventoryUpdate(int _CurIndex)
{
	if (false == InventoryRenderer->IsUpdate())
	{
		return;
	}

	if (nullptr != AllItem[_CurIndex]->Item && false == ContentMouse::MainMouse->GetItemRenderer()->IsUpdate())
	{
		// Inventory -> Mouse
		ContentMouse::MainMouse->GetItemRenderer()->SetTexture("Inventory_" + AllItem[_CurIndex]->Item->ItemName);
		ContentMouse::MainMouse->GetItemRenderer()->On();
		ContentMouse::MainMouse->SetPickItem(AllItem[_CurIndex]->Item);

		PopItem(_CurIndex);
	}
	else if (nullptr != AllItem[_CurIndex]->Item && true == ContentMouse::MainMouse->GetItemRenderer()->IsUpdate())
	{
		// Mouse -> Inventroy & Inventory -> Mouse
		if (ContentMouse::MainMouse->GetPickItem()->GetItemName() == AllItem[_CurIndex]->Item->ItemName)
		{
			AllItem[_CurIndex]->Item->PlusItemCount(ContentMouse::MainMouse->GetPickItem()->GetItemCount());
			ContentMouse::MainMouse->GetItemRenderer()->Off();
			ContentMouse::MainMouse->GetItemCountRenderer()->Off();
		}
		else
		{
			ContentItem* TempValue = ContentMouse::MainMouse->GetPickItem();

			ContentMouse::MainMouse->GetItemRenderer()->SetTexture("Inventory_" + AllItem[_CurIndex]->Item->ItemName);
			ContentMouse::MainMouse->SetPickItem(AllItem[_CurIndex]->Item);

			AllItem[_CurIndex]->ItemCountRenderer->SetText(" ");
			AllItem[_CurIndex]->ItemRenderer->SetTexture("Inventory_" + TempValue->GetItemName());
			AllItem[_CurIndex]->Item = TempValue;
		}
	}
	else if (nullptr == AllItem[_CurIndex]->Item && true == ContentMouse::MainMouse->GetItemRenderer()->IsUpdate())
	{
		MouseToInventory(_CurIndex);
	}
}

void ContentInventory::ShopInventoryUpdate(int _CurIndex)
{
	if (false == ContentUIManager::MainUI->ShopRenderer->IsUpdate())
	{
		return;
	}

	if (false == ContentMouse::MainMouse->GetItemRenderer()->IsUpdate() && nullptr != AllItem[_CurIndex]->Item)
	{
		// Sell InventoryItem
		if (0 == AllItem[_CurIndex]->Item->GetItemPrice())
		{
			EffectPlayer = GameEngineSound::SoundPlay("cancel.wav");
			return;
		}
		EffectPlayer = GameEngineSound::SoundPlay("sell.wav");
		int PlusMoney = AllItem[_CurIndex]->Item->GetItemPrice() * AllItem[_CurIndex]->Item->GetItemCount();
		ContentUIManager::MainUI->PlayerMoney += PlusMoney;
		ContentUIManager::MainUI->TotalGetMoney += PlusMoney;
		PopItem(_CurIndex);
	}
	else if (true == ContentMouse::MainMouse->GetItemRenderer()->IsUpdate() && nullptr == AllItem[_CurIndex]->Item)
	{
		MouseToInventory(_CurIndex);
	}
	else if (true == ContentMouse::MainMouse->GetItemRenderer()->IsUpdate() && nullptr != AllItem[_CurIndex]->Item)
	{
		if (AllItem[_CurIndex]->Item->GetItemName() == ContentMouse::MainMouse->GetPickItem()->GetItemName())
		{
			AllItem[_CurIndex]->Item->PlusItemCount(ContentMouse::MainMouse->GetPickItem()->GetItemCount());
			ContentMouse::MainMouse->GetItemRenderer()->Off();
			ContentMouse::MainMouse->GetItemCountRenderer()->Off();
			ContentMouse::MainMouse->SetPickItem(nullptr);
		}
	}
}

void ContentInventory::ShippingInventoryUpdate(int _CurIndex)
{
	if (false == ContentUIManager::MainUI->ShipInventoryRenderer->IsUpdate())
	{
		return;
	}
	
	if (nullptr == AllItem[_CurIndex]->Item)
	{
		return;
	}

	// Inventory To ShippingBox
	if (true == GameEngineInput::IsDown(VK_LBUTTON)
		&& false == ContentUIManager::MainUI->SellItemRenderer->IsUpdate())
	{
		if (0 == AllItem[_CurIndex]->Item->GetItemPrice())
		{
			return; 
		}
		ContentUIManager::MainUI->SellItemRenderer->SetTexture("Inventory_" + AllItem[_CurIndex]->Item->ItemName);
		ContentUIManager::MainUI->SellItemRenderer->On();
		ContentUIManager::MainUI->SetSellItem(AllItem[_CurIndex]->Item);

		PopItem(_CurIndex);
		EffectPlayer = GameEngineSound::SoundPlay("shipping_in.wav");
	}
	else if (true == GameEngineInput::IsDown(VK_LBUTTON)
		&& true == ContentUIManager::MainUI->SellItemRenderer->IsUpdate())
	{
		if (0 == AllItem[_CurIndex]->Item->GetItemPrice())
		{
			return;
		}
		ContentUIManager::MainUI->SellCurItem();
		ContentUIManager::MainUI->SellItemRenderer->SetTexture("Inventory_" + AllItem[_CurIndex]->Item->ItemName);
		ContentUIManager::MainUI->SellItemRenderer->On();
		ContentUIManager::MainUI->SetSellItem(AllItem[_CurIndex]->Item);

		PopItem(_CurIndex);
		EffectPlayer = GameEngineSound::SoundPlay("shipping_in.wav");
	}

}


void ContentInventory::MouseToInventory(int _CurIndex)
{
	AllItem[_CurIndex]->ItemRenderer->SetTexture("Inventory_" + ContentMouse::MainMouse->GetPickItem()->GetItemName());
	AllItem[_CurIndex]->ItemRenderer->On();
	AllItem[_CurIndex]->ItemCountRenderer->SetText(" ");
	AllItem[_CurIndex]->Item = ContentMouse::MainMouse->GetPickItem();

	ContentMouse::MainMouse->GetItemRenderer()->Off();
	ContentMouse::MainMouse->GetItemCountRenderer()->Off();
	ContentMouse::MainMouse->SetPickItem(nullptr);
}


