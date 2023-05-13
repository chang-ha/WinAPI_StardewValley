#include <GameEngineBase/GameEngineString.h>

#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include "ResourcesManager.h"

ResourcesManager ResourcesManager::Inst;

ResourcesManager::ResourcesManager()
{

}

ResourcesManager::~ResourcesManager()
{
	for (const std::pair<std::string, GameEngineWindowTexture*>& _Pair:AllTexture)
	{
		GameEngineWindowTexture* _Texture = _Pair.second;
		if (nullptr != _Texture)
		{
			delete _Texture;
			_Texture = nullptr;
		}
	}
}

bool ResourcesManager::IsLoadTexture(const std::string& _Name)
{
	return FindTexture(_Name) != nullptr;
}

GameEngineWindowTexture* ResourcesManager::FindTexture(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	std::map<std::string, GameEngineWindowTexture*>::iterator FindIter = AllTexture.find(UpperName);
	if (AllTexture.end() == FindIter)
	{
		return nullptr;
	}
	return FindIter->second;
}

GameEngineWindowTexture* ResourcesManager::TextureLoad(const std::string& _Name, const std::string& _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	GameEngineWindowTexture* LoadTexture = new GameEngineWindowTexture();
	LoadTexture->ResLoad(_Path);
	AllTexture.insert(std::make_pair(UpperName, LoadTexture));
	return LoadTexture;
}
