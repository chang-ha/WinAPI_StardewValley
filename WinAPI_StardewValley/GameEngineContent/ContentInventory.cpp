﻿#define MAXSIZE 12

#include <GameEngineBase/GameEngineDebug.h>

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

		// Inventory Item Renderer
		GameEngineRenderer* _ItemRenderer = CreateUIRenderer(RenderOrder::UI);
		_ItemRenderer->SetTexture("Inventory_" + _Item->GetItemName());
		_ItemRenderer->SetRenderScale(_Item->Texture->GetScale() * RENDERRATIO);
		if (true == InventoryRenderer->IsUpdate())
		{
			_ItemRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.28f + 0.04f * PushIndex), GlobalValue::WinScale.Y * 0.245f });
		}
		else
		{
			_ItemRenderer->SetRenderPos({ GlobalValue::WinScale.X * (0.28f + 0.04f * PushIndex), GlobalValue::WinScale.Y * 0.945f });
		}

		AllItem[PushIndex] = _Item;
		ItemRenderer[PushIndex] = _ItemRenderer;
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

void ContentInventory::SetPostoUIInventory()
{
	for (int x = 0; x < ItemRenderer.size(); x++)
	{
		if (nullptr == ItemRenderer[x])
		{
			continue;
		}
		ItemRenderer[x]->SetRenderPos({ GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * 0.945f });
	}
}

void ContentInventory::SetPostoMainInventory()
{
	for (int x = 0; x < ItemRenderer.size(); x++)
	{
		if (nullptr == ItemRenderer[x])
		{
			continue;
		}
		ItemRenderer[x]->SetRenderPos({GlobalValue::WinScale.X * (0.28f + 0.04f * x), GlobalValue::WinScale.Y * 0.245f});
	}
}

void ContentInventory::Start()
{
	InventoryRenderer = CreateUIRenderer(RenderOrder::UI);

	AllItem.resize(MAXSIZE);
	ItemRenderer.resize(MAXSIZE);
	if (false == ResourcesManager::GetInst().IsLoadTexture("Inventory.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\UI\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Inventory.bmp"));
	}
	Texture = ResourcesManager::GetInst().FindTexture("Inventory.bmp");
	InventoryRenderer->SetTexture("Inventory.bmp");
	InventoryRenderer->SetRenderPos(GlobalValue::WinScale.Half());
	InventoryRenderer->SetRenderScaleToTexture();
	InventoryRenderer->Off();

	// Inventory Text
	// "Sandoll 미생" 출력을 원하면 해당 컴퓨터에 폰트 깔아야함
	// NameText = CreateUIRenderer("Inventory.bmp", RenderOrder::UI);
	// NameText->SetRenderScale({ 100, 40 });
	// NameText->SetRenderPos({- Texture->GetScale().X * 0.33f, Texture->GetScale().Y * 0.35f});
	// NameText->SetText("Player", 40, "Sandoll 미생");
	// NameText->Off();

	for (int x = 0; x < AllItem.size(); x++)
	{
		AllItem[x] = nullptr;
		ItemRenderer[x] = nullptr;
	}
}

void ContentInventory::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('I') || true == GameEngineInput::IsDown(VK_ESCAPE))
	{
		if (true == InventoryRenderer->IsUpdate())
		{
			// Inventory Off
			InventoryRenderer->Off();
			ContentUIManager::MainUI->Inventory->On();
			SetPostoUIInventory();

			Player::MainPlayer->SetIsUpdate(true);
		}
		else
		{
			// Inventory On
			InventoryRenderer->On();
			ContentUIManager::MainUI->Inventory->Off();
			SetPostoMainInventory();

			Player::MainPlayer->SetIsUpdate(false);
			Player::MainPlayer->ChangeState(PlayerState::Idle);
			Player::MainPlayer->EffectPlayer.Stop();
		}
	}

}