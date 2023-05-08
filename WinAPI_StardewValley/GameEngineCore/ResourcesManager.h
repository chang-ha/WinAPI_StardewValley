#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEnginePath.h>

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
protected:

private:
	static ResourcesManager Inst;
	std::map<std::string, GameEngineWindowTexture*> AllTexture;
	
	// constructer destructer
	ResourcesManager();
	~ResourcesManager();
};

