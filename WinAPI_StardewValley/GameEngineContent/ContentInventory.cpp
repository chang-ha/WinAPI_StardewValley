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
		GameEngineRenderer* _ItemRenderer = CreateUIRenderer(RenderOrder::Inventory_Item);
		_ItemRenderer->SetTexture("Inventory_" + _Item->GetItemName());
		_ItemRenderer->SetRenderScale(_Item->Texture->GetScale() * RENDERRATIO);
		_ItemRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.28f + 0.04f * PushIndex), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });

		AllItem[PushIndex]->Item = _Item;
		AllItem[PushIndex]->ItemRenderer = _ItemRenderer;
	}
	else if (nullptr != Find)
	{
		Find->PlusItemCount(_Item->GetItemCount());
		_Item->Death();
	}

}

void ContentInventory::PopItem(int _Index)
{
	if (nullptr == AllItem[_Index]->Item)
	{
		return;
	}

	AllItem[_Index]->ItemCountRenderer->SetText(" ");
	AllItem[_Index]->ItemRenderer->Death();
	AllItem[_Index]->Item->Death();
	AllItem[_Index]->ItemRenderer = nullptr;
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

		GameEngineCollision* _ItemCollision = CreateCollision(CollisionOrder::Inventory_Item);
		_ItemCollision->SetCollisionScale(TILESIZE);
		_ItemCollision->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + float4{ GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });

		GameEngineRenderer* _ItemCountRenderer = CreateUIRenderer(RenderOrder::Inventory_Item);
		_ItemCountRenderer->SetText(" ");
		_ItemCountRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.29f + 0.04f * x), GlobalValue::WinScale.Y * (0.955f - PosSettingValue) });

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


	// Default Item
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
}

void ContentInventory::Update(float _Delta)
{
	// Change CurIndex
	if (true == GameEngineInput::IsDown('Q'))
	{
		EffectPlayer = GameEngineSound::SoundPlay("toolSwap.wav");
		--CurIndex;
		if (-1 == CurIndex)
		{
			CurIndex = 11;
		}
	}
	else if (true == GameEngineInput::IsDown('E'))
	{
		EffectPlayer = GameEngineSound::SoundPlay("toolSwap.wav");
		++CurIndex;
		if (12 == CurIndex)
		{
			CurIndex = 0;
		}
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

			Player::MainPlayer->SetIsUpdate(false);
			Player::MainPlayer->ChangeState(PlayerState::Idle);
			Player::MainPlayer->EffectPlayer.Stop();
		}
	}

	// Mouse Interaction
	for (int x = 0; x < AllItem.size(); x++)
	{
		if (true == AllItem[x]->ItemCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect)
			&& true == GameEngineInput::IsDown(VK_LBUTTON))
		{
			if (nullptr != AllItem[x]->ItemRenderer && false == ContentMouse::MainMouse->GetItemRenderer()->IsUpdate())
			{
				ContentMouse::MainMouse->GetItemRenderer()->SetTexture("Inventory_" + AllItem[x]->Item->ItemName);
				ContentMouse::MainMouse->GetItemRenderer()->SetRenderScale(AllItem[x]->Item->Texture->GetScale() * RENDERRATIO);
				ContentMouse::MainMouse->GetItemRenderer()->On();
				ContentMouse::MainMouse->SetPickItem(AllItem[x]->Item);

				AllItem[x]->ItemCountRenderer->SetText(" ");
				AllItem[x]->ItemRenderer->Death();
				AllItem[x]->ItemRenderer = nullptr;
				AllItem[x]->Item = nullptr;
			}
			else if (nullptr != AllItem[x]->ItemRenderer && true == ContentMouse::MainMouse->GetItemRenderer()->IsUpdate())
			{
				ContentItem* TempValue = ContentMouse::MainMouse->GetPickItem();

				ContentMouse::MainMouse->GetItemRenderer()->SetTexture("Inventory_" + AllItem[x]->Item->ItemName);
				ContentMouse::MainMouse->GetItemRenderer()->SetRenderScale(AllItem[x]->Item->Texture->GetScale()* RENDERRATIO);
				ContentMouse::MainMouse->SetPickItem(AllItem[x]->Item);

				AllItem[x]->ItemRenderer->SetTexture("Inventory_" + TempValue->GetItemName());
				AllItem[x]->ItemRenderer->SetRenderScale(TempValue->Texture->GetScale() * RENDERRATIO);
				AllItem[x]->ItemRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });
				AllItem[x]->Item = TempValue;
			}
			else if (nullptr == AllItem[x]->ItemRenderer && true == ContentMouse::MainMouse->GetItemRenderer()->IsUpdate())
			{
				GameEngineRenderer* _ItemRenderer = CreateUIRenderer(RenderOrder::Inventory_Item);
				_ItemRenderer->SetTexture("Inventory_" + ContentMouse::MainMouse->GetPickItem()->GetItemName());
				_ItemRenderer->SetRenderScale(ContentMouse::MainMouse->GetPickItem()->Texture->GetScale()* RENDERRATIO);
				_ItemRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });
				AllItem[x]->ItemRenderer = _ItemRenderer;
				AllItem[x]->Item = ContentMouse::MainMouse->GetPickItem();

				ContentMouse::MainMouse->GetItemRenderer()->Off();
			}

		}
	}
}