#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentBuilding.h"
#include "GlobalValue.h"
#include "ContentsEnum.h"
#include "Player.h"

ContentBuilding::ContentBuilding()
{

}

ContentBuilding::~ContentBuilding()
{

}

void ContentBuilding::Init(const std::string& _FileName)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Building\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
	}
	Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	Renderer = CreateRenderer(RenderOrder::Play);
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
}

void ContentBuilding::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_F2))
	{
		if (true == Renderer->IsUpdate())
		{
			Renderer->Off();
		}
		else if (false == Renderer->IsUpdate())
		{
			Renderer->On();
		}
	}
}
