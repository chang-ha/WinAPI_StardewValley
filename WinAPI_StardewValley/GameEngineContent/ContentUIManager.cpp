#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "ContentUIManager.h"
#include "ContentsEnum.h"

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

		float4 WinScale = GameEngineWindow::MainWindow.GetScale();

		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Clock.bmp"));
		Clock = CreateUIRenderer("Clock.bmp", RenderOrder::UI);
		Clock->SetRenderScale(Texture->GetScale()*4);
		Clock->SetRenderPos({ WinScale.X - Texture->GetScale().Half().X * 4, Texture->GetScale().Half().Y * 4});

		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Clock_hand.bmp"));
		ClockHand = CreateUIRenderer("Clock_hand.bmp", RenderOrder::UI);
		ClockHand->SetRenderScale(Texture->GetScale()*4);
		ClockHand->SetRenderPos({ WinScale.X - Texture->GetScale().Half().X * 4 - 180, Texture->GetScale().Half().Y * 4 + 10});

		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Energy.bmp"));
		Energy = CreateUIRenderer("Energy.bmp", RenderOrder::UI);
		Energy->SetRenderScale(Texture->GetScale()*4);
		Energy->SetRenderPos({ WinScale.X - Texture->GetScale().Half().X * 4, WinScale.Y - Texture->GetScale().Half().Y * 4 });

		// ContentMouse->Renderer->SetRenderPos(GameEngineWindow::MainWindow.GetMousePos());
	}
}