#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "ContentUIManager.h"
#include "ContentsEnum.h"
ContentUIManager* ContentUIManager::MainUI = nullptr;

ContentUIManager::ContentUIManager()
{
	MainUI = this;
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
		Clock = CreateUIRenderer("Clock.bmp", RenderOrder::PlayUI);
		Clock->SetRenderScale(Texture->GetScale()*4);

		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Clock_hand.bmp"));
		ClockHand = CreateUIRenderer("Clock_hand.bmp", RenderOrder::PlayUI);
		ClockHand->SetRenderScale(Texture->GetScale()*4);

		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Energy.bmp"));
		EnergyBar = CreateUIRenderer("Energy.bmp", RenderOrder::PlayUI);
		EnergyBar->SetRenderScale(Texture->GetScale()*4);

		Clock->SetRenderPos({ 1390, 115 });
		ClockHand->SetRenderPos({1335, 52});
		EnergyBar->SetRenderPos({1500, 785});

	}
}