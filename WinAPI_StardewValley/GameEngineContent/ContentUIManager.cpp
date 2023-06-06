#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "ContentUIManager.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

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

		WinScale = GameEngineWindow::MainWindow.GetScale();

		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Clock.bmp"));
		Clock = CreateUIRenderer("Clock.bmp", RenderOrder::UI);
		Clock->SetRenderScale(Texture->GetScale() * RENDERRATIO);
		Clock->SetRenderPos({ WinScale.X - Texture->GetScale().Half().X * RENDERRATIO, Texture->GetScale().Half().Y * RENDERRATIO });

		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Clock_hand.bmp"));
		ClockHand = CreateUIRenderer("Clock_hand.bmp", RenderOrder::UI);
		ClockHand->SetRenderScale(Texture->GetScale() * RENDERRATIO);
		ClockHand->SetRenderPos({ WinScale.X - Texture->GetScale().Half().X * RENDERRATIO - 135, Texture->GetScale().Half().Y * RENDERRATIO + 10 });

		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Energy.bmp"));
		Energy = CreateUIRenderer("Energy.bmp", RenderOrder::UI);
		Energy->SetRenderScale(Texture->GetScale() * 3);
		Energy->SetRenderPos({ WinScale.X - Texture->GetScale().Half().X * RENDERRATIO, WinScale.Y - Texture->GetScale().Half().Y * RENDERRATIO });

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Inventory.bmp"));
		Inventory = CreateUIRenderer("UI_Inventory.bmp", RenderOrder::UI);
		Inventory->SetRenderScaleToTexture();
		InventoryDownRender();
	}
}

void ContentUIManager::Update(float _Delta)
{

}

void ContentUIManager::InventoryUpRender()
{
	Inventory->SetRenderPos({ WinScale.Half().X, 50 });
}

void ContentUIManager::InventoryDownRender()
{
	Inventory->SetRenderPos({ WinScale.Half().X, WinScale.Y - 50 });
}
