#include <GameEngineCore/ResourcesManager.h>

#include "ContentSeed.h"

ContentSeed::ContentSeed()
{

}

ContentSeed::~ContentSeed()
{

}

void ContentSeed::Init(const std::string& _FileName)
{
	//if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("Resources");
	//	FilePath.MoveChild("Resources\\Textures\\Item\\");
	//	Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
	//	ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Inventory_" + _FileName));
	//}
	//Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	//Renderer->SetTexture(_FileName);
	//Renderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	//Collision->SetCollisionScale(Texture->GetScale() * RENDERRATIO * 3);
	//ItemName = _FileName;
	//Type = _Type;
	ContentItem::Init(_FileName, ItemType::Seed);
	//if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("Resources");
	//	FilePath.MoveChild("Resources\\Textures\\Item\\");
	//	Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
	//	ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Inventory_" + _FileName));
	//}
	//Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	//Renderer->SetTexture(_FileName);
	//Renderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	//Collision->SetCollisionScale(Texture->GetScale() * RENDERRATIO * 3);
	//ItemName = _FileName;
	//Type = _Type;
}
