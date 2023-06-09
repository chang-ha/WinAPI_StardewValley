﻿#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDirectory.h>

#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineSprite.h>

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

	for (const std::pair<std::string, GameEngineSprite*>& Pair : AllSprite)
	{
		GameEngineSprite* Sprite = Pair.second;

		if (nullptr != Sprite)
		{
			delete Sprite;
			Sprite = nullptr;
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

GameEngineWindowTexture* ResourcesManager::TextureCreate(const std::string& _Name, float4 _Scale)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	if (AllTexture.find(UpperName) != AllTexture.end())
	{
		MsgBoxAssert("같은 이름의 텍스처가 이미 존재합니다.");
		return nullptr;
	}
	GameEngineWindowTexture* CreateTexture = new GameEngineWindowTexture();
	CreateTexture->ResCreate(_Scale);
	AllTexture.insert(std::make_pair(UpperName, CreateTexture));
	return CreateTexture;
}

GameEngineWindowTexture* ResourcesManager::TextureLoad(const std::string& _Name, const std::string& _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	if (AllTexture.find(UpperName) != AllTexture.end())
	{
		MsgBoxAssert("같은 이름의 텍스처가 이미 존재합니다.");
		return nullptr;
	}
	GameEngineWindowTexture* LoadTexture = new GameEngineWindowTexture();
	LoadTexture->ResLoad(_Path);
	AllTexture.insert(std::make_pair(UpperName, LoadTexture));
	return LoadTexture;
}



GameEngineSprite* ResourcesManager::FindSprite(const std::string& _SpriteName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SpriteName);

	std::map<std::string, GameEngineSprite*>::iterator FindIter = AllSprite.find(UpperName);

	if (AllSprite.end() == FindIter)
	{
		return nullptr;
	}
	return FindIter->second;
}

GameEngineSprite* ResourcesManager::CreateSpriteSheet(const std::string& _SpriteName, const std::string& _Path, int _XCount, int _YCount)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SpriteName);

	if (nullptr != FindSprite(UpperName))
	{
		MsgBoxAssert(UpperName + "이미 생성된 스프라이트시트를 다시 만들려고 했습니다.");
	}

	GameEnginePath Path = _Path;
	GameEngineWindowTexture* Texture = ResourcesManager::FindTexture(Path.GetFileName());
	if (nullptr == Texture)
	{
		Texture = ResourcesManager::TextureLoad(_Path);
	}

	float4 Scale = Texture->GetScale();
	GameEngineSprite* NewSprite = new GameEngineSprite();
	NewSprite->CreateSpriteSheet(Texture, _XCount, _YCount);
	AllSprite.insert(std::make_pair(UpperName, NewSprite));
	return NewSprite;
}

GameEngineSprite* ResourcesManager::CreateSpriteFolder(const std::string& _SpriteName, const std::string& _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SpriteName);

	if (nullptr != FindSprite(UpperName))
	{
		MsgBoxAssert(UpperName + "이미 로드한 스프라이트 입니다.");
	}

	GameEngineSprite* NewSprite = new GameEngineSprite();

	NewSprite->CreateSpriteFolder(_Path);

	AllSprite.insert(std::make_pair(UpperName, NewSprite));

	return NewSprite;
}