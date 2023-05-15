#pragma once
#include <string>
#include <map>

#include <GameEngineBase/GameEnginePath.h>

class GameEngineSprite;
class GameEngineWindowTexture;
class ResourcesManager
{
public:
	// delete function
	ResourcesManager(const ResourcesManager& _Ohter) = delete;
	ResourcesManager(ResourcesManager&& _Ohter) noexcept = delete;
	ResourcesManager& operator=(const ResourcesManager& _Other) = delete;
	ResourcesManager& operator=(ResourcesManager&& _Other) noexcept = delete;

	static ResourcesManager& GetInst()
	{
		return Inst;
	}

	GameEngineWindowTexture* TextureLoad(const std::string& _Path)
	{
		GameEnginePath LoadPath = _Path;
		return TextureLoad(LoadPath.GetFileName(), _Path);
	}	

	GameEngineWindowTexture* TextureLoad(const std::string& _Name, const std::string& _Path);

	GameEngineWindowTexture* FindTexture(const std::string& _Name);

	bool IsLoadTexture(const std::string& _Name);

public:
	GameEngineSprite* FindSprite(const std::string& _SpriteName);

	GameEngineSprite* CreateSpriteFolder(const std::string& _SpriteName,const std::string& _Path);

	GameEngineSprite* CreateSpriteFolder(const std::string& _Path)
	{
		GameEnginePath FolderPath = _Path;
		return CreateSpriteFolder(FolderPath.GetFileName(), _Path);
	}

	GameEngineSprite* CreateSpriteSheet(const std::string& _SpriteName, const std::string& _Path, int _XCount, int _YCount);

	GameEngineSprite* CreateSpriteSheet(const std::string& _Path, int _XCount, int _YCount)
	{
		GameEnginePath SheetPath = _Path;
		return CreateSpriteSheet(SheetPath.GetFileName(), _Path, _XCount, _YCount);
	}

protected:

private:
	static ResourcesManager Inst;
	std::map<std::string, GameEngineWindowTexture*> AllTexture;
	std::map<std::string, GameEngineSprite*> AllSprite;

	// constructer destructer
	ResourcesManager();
	~ResourcesManager();
};

