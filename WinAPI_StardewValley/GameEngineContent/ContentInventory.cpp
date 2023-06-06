#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>

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
	//if (nullptr == FindItem(_Item->GetItemName()))
	//{

	//}
}

void ContentInventory::Start()
{
	InventoryRenderer = CreateRenderer(RenderOrder::UI);

	AllItem.resize(12);
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
	InventoryRenderer->SetRenderScaleToTexture();
	InventoryRenderer->Off();

	// "Sandoll 미생" 출력을 원하면 해당 컴퓨터에 폰트 깔아야함
	Name = CreateRenderer("Inventory.bmp", RenderOrder::UI);
	// Name->SetRenderScale({ 100, 40 });
	// Name->SetRenderPos({- Texture->GetScale().X * 0.33f, Texture->GetScale().Y * 0.35f});
	Name->Off();
}

void ContentInventory::Update(float _Delta)
{
	float4 MainCameraPos = GetLevel()->GetMainCamera()->GetPos();
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	if (true == GameEngineInput::IsDown('I') || true == GameEngineInput::IsDown(VK_ESCAPE))
	{
		if (true == InventoryRenderer->IsUpdate())
		{
			InventoryRenderer->Off();
			Name->Off();
			Player::MainPlayer->SetIsUpdate(true);
		}
		else
		{
			InventoryRenderer->On();
			Name->On();

			Player::MainPlayer->SetIsUpdate(false);
			Player::MainPlayer->ChangeState(PlayerState::Idle);
			Player::MainPlayer->EffectPlayer.Stop();

			// Name->SetText("Player", 40, "Sandoll 미생");
		}
	}

	for (int x = 0; x < AllItem.size(); x++)
	{

	}
}