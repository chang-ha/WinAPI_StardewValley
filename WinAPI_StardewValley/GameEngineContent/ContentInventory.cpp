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

void ContentInventory::UseItem(ContentItem* _Item)
{
	int ItemIndex = 0;
	ContentItem* Find = FindItem(_Item, &ItemIndex);
	if (nullptr == Find)
	{
		MsgBoxAssert("인벤토리에 없는 아이템을 사용하려고 했습니다.");
	}

	if (1 == Find->GetItemCount())
	{
		PopItem(ItemIndex);
	}
	else
	{
		Find->MinusItemCount(1);
	}
}

void ContentInventory::Start()
{
	// Resize Vector
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
	}

	// Create Renderer
	InventoryRenderer = CreateUIRenderer(RenderOrder::UI);
	CurIndexRenderer = CreateUIRenderer(RenderOrder::UIMouse);

	// Renderer Setting
	InventoryRenderer->SetTexture("Inventory.bmp");
	InventoryRenderer->SetRenderPos(GlobalValue::WinScale.Half());
	InventoryRenderer->SetRenderScaleToTexture();
	InventoryRenderer->Off();

	CurIndexRenderer->SetTexture("UI_Inventory_Select.bmp");;
	CurIndexRenderer->SetRenderScaleToTexture();

	// Inventory Text
	NameText = CreateUIRenderer(RenderOrder::UI);
	NameText->SetText("Player", 40, "Sandoll 미생");
	NameText->SetRenderScale({ 100, 40 });
	NameText->SetRenderPos({GlobalValue::WinScale.X * 0.325f, GlobalValue::WinScale.Y * 0.72f});
	NameText->Off();


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

	// TestCode
	Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
	Item->Init("Seed_Parsnip.bmp", ItemType::Seed, 20);
	PushItem(Item);

	Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
	Item->Init("Seed_Cauliflower.bmp", ItemType::Seed, 20);
	PushItem(Item);

	Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
	Item->Init("Seed_Garlic.bmp", ItemType::Seed, 20);
	PushItem(Item);

	Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
	Item->Init("Seed_Potato.bmp", ItemType::Seed, 20);
	PushItem(Item);
}

void ContentInventory::Update(float _Delta)
{
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

	// CollisionPos Update
	for (int x = 0; x < AllItem.size(); x++)
	{
		if (nullptr == AllItem[x])
		{
			continue;
		}
		AllItem[x]->ItemCollision->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + float4{ GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });
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
			continue;
		}
		AllItem[x]->ItemCountRenderer->SetText(std::to_string(AllItem[x]->Item->GetItemCount()), 20, "Sandoll 미생");
	}

	// Inventory On/Off
	if (true == GameEngineInput::IsDown('I') || true == GameEngineInput::IsDown(VK_ESCAPE))
	{
		if (true == InventoryRenderer->IsUpdate())
		{
			// Inventory Off
			InventoryRenderer->Off();
			NameText->Off();
			ContentUIManager::MainUI->Inventory->On();
			PosSettingValue = 0.0f;
			SetPosInventoryItem();

			Player::MainPlayer->SetIsUpdate(true);
		}
		else
		{
			// Inventory On
			InventoryRenderer->On();
			NameText->On();
			ContentUIManager::MainUI->Inventory->Off();
			PosSettingValue = 0.702f;
			SetPosInventoryItem();

			Player::MainPlayer->StopPlayer();
		}
	}

	// Mouse Interaction
	for (int x = 0; x < AllItem.size(); x++)
	{
		if (true == AllItem[x]->ItemCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect)
			&& true == GameEngineInput::IsDown(VK_LBUTTON))
		{
			if (nullptr != AllItem[x]->Item && false == ContentMouse::MainMouse->GetItemRenderer()->IsUpdate())
			{
				// Inventory -> Mouse
				ContentMouse::MainMouse->GetItemRenderer()->SetTexture("Inventory_" + AllItem[x]->Item->ItemName);
				ContentMouse::MainMouse->GetItemRenderer()->On();
				ContentMouse::MainMouse->SetPickItem(AllItem[x]->Item);

				AllItem[x]->ItemCountRenderer->SetText(" ");
				AllItem[x]->ItemRenderer->Off();
				AllItem[x]->Item = nullptr;
			}
			else if (nullptr != AllItem[x]->Item && true == ContentMouse::MainMouse->GetItemRenderer()->IsUpdate())
			{
				// Mouse -> Inventroy & Inventory -> Mouse
				ContentItem* TempValue = ContentMouse::MainMouse->GetPickItem();

				ContentMouse::MainMouse->GetItemRenderer()->SetTexture("Inventory_" + AllItem[x]->Item->ItemName);
				ContentMouse::MainMouse->SetPickItem(AllItem[x]->Item);

				AllItem[x]->ItemCountRenderer->SetText(" ");
				AllItem[x]->ItemRenderer->SetTexture("Inventory_" + TempValue->GetItemName());
				AllItem[x]->Item = TempValue;
			}
			else if (nullptr == AllItem[x]->Item && true == ContentMouse::MainMouse->GetItemRenderer()->IsUpdate())
			{
				// Mouse -> Inventory
				AllItem[x]->ItemRenderer->SetTexture("Inventory_" + ContentMouse::MainMouse->GetPickItem()->GetItemName());
				AllItem[x]->ItemRenderer->On();

				AllItem[x]->ItemCountRenderer->SetText(" ");
				AllItem[x]->Item = ContentMouse::MainMouse->GetPickItem();
				ContentMouse::MainMouse->GetItemRenderer()->Off();
			}
		}
	}
}