#define MAXSIZE 12

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>

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

ContentInventory* ContentInventory::MainInventory = nullptr;

ContentInventory::ContentInventory()
{

}

ContentInventory::~ContentInventory()
{

}

void ContentInventory::PushItem(ContentItem* _Item)
{
	int Index = 0;
	ContentItem* Find = FindItem(_Item, Index);
	if (nullptr == Find)
	{
		int PushIndex = BlankSpace();

		// Item Off
		_Item->Off();
		_Item->Collision->Off();
		_Item->Renderer->Off();
		
		// Inventory Item & ItemCount Renderer
		GameEngineRenderer* _ItemRenderer = CreateUIRenderer(RenderOrder::Inventory_Item);
		_ItemRenderer->SetTexture("Inventory_" + _Item->GetItemName());
		_ItemRenderer->SetRenderScale(_Item->Texture->GetScale() * RENDERRATIO);

		GameEngineCollision* _ItemCollision = CreateCollision(CollisionOrder::Inventory_Item);
		_ItemCollision->SetCollisionScale(_Item->Texture->GetScale() * RENDERRATIO);

		GameEngineRenderer* _ItemCountRenderer = CreateUIRenderer(RenderOrder::Inventory_Item);
		_ItemCountRenderer->SetText(std::to_string(_Item->GetItemCount()), 20, "Sandoll 미생");
		_ItemRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.28f + 0.04f * PushIndex), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });
		_ItemCountRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.29f + 0.04f * PushIndex), GlobalValue::WinScale.Y * (0.955f - PosSettingValue) });
		_ItemCollision->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + float4{ GlobalValue::WinScale.X * (0.28f + 0.04f * PushIndex), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });

		AllItem[PushIndex] = _Item;
		ItemRenderer[PushIndex] = _ItemRenderer;
		ItemCollision[PushIndex] = _ItemCollision;
		ItemCountRenderer[PushIndex] = _ItemCountRenderer;
	}
	else if (nullptr != Find)
	{
		Find->PlusItemCount(_Item->GetItemCount());
		_Item->Death();
	}

}
	
bool ContentInventory::IsFull(const ContentItem* _Item)
{
	int Index = BlankSpace();

	if (-1 == Index)
	{
		if (nullptr != FindItem(_Item, Index))
		{
			return false;
		}
		return true;
	}

	return false;
}

ContentItem* ContentInventory::FindItem(const ContentItem* _Item, int _ResultIndex)
{
	for (int x = 0; x < AllItem.size(); x++)
	{
		if (nullptr == AllItem[x])
		{
			continue;
		}

		if (AllItem[x]->GetItemName() == _Item->GetItemName())
		{
			_ResultIndex = x;
			return  AllItem[x];
		}
	}
	_ResultIndex = -1;
	return nullptr;
}

int ContentInventory::BlankSpace()
{
	for (int x = 0; x < AllItem.size(); x++)
	{
		if (nullptr == AllItem[x])
		{
			return x;
		}
	}
	return -1;
}

void ContentInventory::SetPosInventoryItem()
{
	for (int x = 0; x < ItemRenderer.size(); x++)
	{
		if (nullptr == ItemRenderer[x])
		{
			continue;
		}
		ItemRenderer[x]->SetRenderPos({ GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });
		ItemCollision[x]->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + float4{GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * (0.945f - PosSettingValue )});
		ItemCountRenderer[x]->SetRenderPos({ GlobalValue::WinScale.X * (0.29f + 0.04f * x), GlobalValue::WinScale.Y * (0.955f - PosSettingValue) });
	}
}

void ContentInventory::Start()
{
	// Resize Vector
	AllItem.resize(MAXSIZE);
	ItemRenderer.resize(MAXSIZE);
	ItemCollision.resize(MAXSIZE);
	ItemCountRenderer.resize(MAXSIZE);

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
	// "Sandoll 미생" 출력을 원하면 해당 컴퓨터에 폰트 깔아야함
	NameText = CreateUIRenderer(RenderOrder::UI);
	NameText->SetText("Player", 40, "Sandoll 미생");
	NameText->SetRenderScale({ 100, 40 });
	NameText->SetRenderPos({GlobalValue::WinScale.X * 0.325f, GlobalValue::WinScale.Y * 0.72f});
	NameText->Off();

	for (int x = 0; x < AllItem.size(); x++)
	{
		AllItem[x] = nullptr;
		ItemRenderer[x] = nullptr;
		ItemCollision[x] = nullptr;
		ItemCountRenderer[x] = nullptr;
	}

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
	if (true == GameEngineInput::IsDown(VK_LEFT))
	{
		--CurIndex;
		if (-1 == CurIndex)
		{
			CurIndex = 11;
		}
	}
	else if (true == GameEngineInput::IsDown(VK_RIGHT))
	{
		++CurIndex;
		if (12 == CurIndex)
		{
			CurIndex = 0;
		}
	}

	// CurIndexRenderer
	CurIndexRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.28f + 0.04f * CurIndex), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });

	// CollisionPos Update
	for (int x = 0; x < ItemCollision.size(); x++)
	{
		if (nullptr == ItemCollision[x])
		{
			continue;
		}
		ItemCollision[x]->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + float4{ GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * (0.945f - PosSettingValue) });
	}

	// ItemCountRenderer Update
	for (int x = 0; x < ItemCountRenderer.size(); x++)
	{
		if (nullptr == ItemCountRenderer[x])
		{
			continue;
		}

		ItemCountRenderer[x]->SetText(std::to_string(AllItem[x]->GetItemCount()), 20, "Sandoll 미생");
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
}