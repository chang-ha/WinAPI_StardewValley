#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentsEnum.h"
#include "PlayOver.h"
#include "GlobalValue.h"

PlayOver::PlayOver()
{

}

PlayOver::~PlayOver()
{

}

void PlayOver::Start()
{
	Renderer = CreateRenderer(RenderOrder::PlayOver);
}

void PlayOver::Update(float _Delta)
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

void PlayOver::Init(const std::string& _FileName)
{
	FileName = _FileName;
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Over\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
	}
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	RenderScale = Texture->GetScale() * RENDERRATIO;
	Scale = Texture->GetScale();
}