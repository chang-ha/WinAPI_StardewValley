#define MAXSIZE 12

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

ContentInventory* ContentInventory::MainInventory = nullptr;

ContentInventory::ContentInventory()
{

}

ContentInventory::~ContentInventory()
{

}

void ContentInventory::PushItem(ContentItem* _Item)
{
	if (true == Full)
	{
		MsgBoxAssert("인벤토리에 남은 공간이 없습니다.");
		return;
	}

	ContentItem* Find = FindItem(_Item);
	if (nullptr == Find && AllItem.capacity() > AllItem.size())
	{
		AllItem.push_back(_Item);
		if (AllItem.capacity() == AllItem.size())
		{
			Full = true;
		}
	}
	else if (nullptr != Find)
	{
		Find->PlusItemCount(_Item->GetItemCount());
	}

	_Item->Off();
	_Item->Collision->Off();
	_Item->Renderer->Off();
}

ContentItem* ContentInventory::FindItem(ContentItem* _Item)
{
	for (int x = 0; x < AllItem.size(); x++)
	{
		if (AllItem[x]->GetItemName() == _Item->GetItemName())
		{
			return  AllItem[x];
		}
	}
	return nullptr;
}

void ContentInventory::Start()
{
	InventoryRenderer = CreateUIRenderer(RenderOrder::UI);

	AllItem.reserve(MAXSIZE);
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
}

void ContentInventory::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('I') || true == GameEngineInput::IsDown(VK_ESCAPE))
	{
		if (true == InventoryRenderer->IsUpdate())
		{
			InventoryRenderer->Off();
			// NameText->Off();
			Player::MainPlayer->SetIsUpdate(true);
		}
		else
		{
			InventoryRenderer->On();
			// NameText->On();

			Player::MainPlayer->SetIsUpdate(false);
			Player::MainPlayer->ChangeState(PlayerState::Idle);
			Player::MainPlayer->EffectPlayer.Stop();
		}
	}

}