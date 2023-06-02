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

ContentInventory* ContentInventory::MainInventory = nullptr;

ContentInventory::ContentInventory()
{

}

ContentInventory::~ContentInventory()
{

}

void ContentInventory::Start()
{
	InventoryRenderer = CreateRenderer(RenderOrder::UI);
	// InventoryCollision = CreateCollision(CollisionOrder::UI);
	if (false == ResourcesManager::GetInst().IsLoadTexture("map.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\UI\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("map.bmp"));
	}
	Texture = ResourcesManager::GetInst().FindTexture("map.bmp");
	InventoryRenderer->SetTexture("map.bmp");
	InventoryRenderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	InventoryRenderer->Off();
}

void ContentInventory::Update(float _Delta)
{
	InventoryRenderer->SetRenderPos(GetLevel()->GetMainCamera()->GetPos() + GameEngineWindow::MainWindow.GetScale().Half());

	if (true == GameEngineInput::IsDown('I'))
	{
		if (true == InventoryRenderer->IsUpdate())
		{
			InventoryRenderer->Off();
		}
		else
		{
			InventoryRenderer->On();
		}
	}
}