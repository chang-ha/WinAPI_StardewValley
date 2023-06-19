#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Creature.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

Creature::Creature()
{

}

Creature::~Creature()
{

}

void Creature::Start()
{
	Renderer = CreateRenderer(RenderOrder::PlayOver);
}


void Creature::Update(float _Delta)
{
}

void Creature::Init(const std::string& _FileName)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Creature\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
	}
	Texture = ResourcesManager::GetInst().FindTexture(_FileName);
}
