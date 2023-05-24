#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "Creature.h"
#include "ContentsEnum.h"
Creature::Creature()
{

}

Creature::~Creature()
{

}

void Creature::Start()
{
	Renderer = CreateRenderer(RenderOrder::Creature);
}


void Creature::Update(float _Delta)
{
}

void Creature::Init(const std::string& _FileName)
{
	FileName = _FileName;
	if (false == ResourcesManager::GetInst().IsLoadTexture(FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Creature\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(FileName));
	}
	Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	Scale = Texture->GetScale();
}
