#pragma once
#include <string>

class GameEngineTexture;
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

	void TextureLoad(const std::string& Path)
	{

	}

	GameEngineTexture* FindTexture(const std::string& _Image);

	bool IsLoadTexture(const std::string& _Name);
protected:

private:
	static ResourcesManager Inst;
	
	// constructer destructer
	ResourcesManager();
	~ResourcesManager();
};

