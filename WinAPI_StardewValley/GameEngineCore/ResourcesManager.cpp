#include "ResourcesManager.h"
#include "GameEngineTexture.h"
#include <GameEngineBase/GameEngineString.h>

ResourcesManager ResourcesManager::Inst;

ResourcesManager::ResourcesManager()
{

}

ResourcesManager::~ResourcesManager()
{

}

bool ResourcesManager::IsLoadTexture(const std::string& _Name)
{
	return FindTexture(_Name) != nullptr;
}

GameEngineTexture* ResourcesManager::FindTexture(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	std::map<std::string, GameEngineTexture*>::iterator FindIter = AllTexture.find(UpperName);
	if (AllTexture.end() == FindIter)
	{
		return nullptr;
	}
	return FindIter->second;
}

void ResourcesManager::TextureLoad(const std::string& _Name, const std::string& _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	GameEngineTexture* LoadTexture = new GameEngineTexture();
	LoadTexture->ResLoad(_Path);
	AllTexture.insert(std::make_pair(UpperName, LoadTexture));
}
