﻿#include <GameEngineBase/GameEnginePath.h>

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

		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Clock.bmp"));
		Clock = CreateUIRenderer("Clock.bmp", RenderOrder::UI);
		Clock->SetRenderScale(Texture->GetScale() * RENDERRATIO);
		Clock->SetRenderPos({ GlobalValue::WinScale.X - Texture->GetScale().Half().X * RENDERRATIO, Texture->GetScale().Half().Y * RENDERRATIO });

		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Clock_hand.bmp"));
		ClockHand = CreateUIRenderer("Clock_hand.bmp", RenderOrder::UI);
		ClockHand->SetRenderScale(Texture->GetScale() * RENDERRATIO);
		ClockHand->SetRenderPos({ GlobalValue::WinScale.X - Texture->GetScale().Half().X * RENDERRATIO - 135, Texture->GetScale().Half().Y * RENDERRATIO + 10 });

		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Energy.bmp"));
		Energy = CreateUIRenderer("Energy.bmp", RenderOrder::UI);
		Energy->SetRenderScale(Texture->GetScale() * 3);
		Energy->SetRenderPos({ GlobalValue::WinScale.X - Texture->GetScale().Half().X * RENDERRATIO, GlobalValue::WinScale.Y - Texture->GetScale().Half().Y * RENDERRATIO });

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Inventory.bmp"));
		Inventory = CreateUIRenderer("UI_Inventory.bmp", RenderOrder::UI);
		Inventory->SetRenderScaleToTexture();
		InventoryDownRender();
	}

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

}

void ContentUIManager::InventoryUpRender()
{
	Inventory->SetRenderPos({ GlobalValue::WinScale.Half().X, 50 });
}

void ContentUIManager::InventoryDownRender()
{
	Inventory->SetRenderPos({ GlobalValue::WinScale.Half().X, GlobalValue::WinScale.Y - 50 });
}
