#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentItem.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

ContentItem::ContentItem()
{

}

ContentItem::~ContentItem()
{

}

void ContentItem::Init(const std::string& _FileName, ToolType _Type)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Item\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
	}
	Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	Type = _Type;
}

void ContentItem::Start()
{
	Renderer = CreateRenderer(RenderOrder::PlayOver);
}

void ContentItem::Update(float _Delta)
{
}
void ContentItem::LevelStart()
{
}
void ContentItem::LevelEnd()
{
}