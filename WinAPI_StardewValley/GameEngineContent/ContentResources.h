#pragma once
#include "ContentActor.h"

enum class ResourcesType
{

};

class GameEngineWindowTexture;
class GameEngineCollision;
class GameEngineRenderer;
class ContentResources : public ContentActor
{
public:
	// constructer destructer
	ContentResources();
	~ContentResources();

	// delete function
	ContentResources(const ContentResources& _Ohter) = delete;
	ContentResources(ContentResources&& _Ohter) noexcept = delete;
	ContentResources& operator=(const ContentResources& _Other) = delete;
	ContentResources& operator=(ContentResources&& _Other) noexcept = delete;

	virtual void Init(const std::string& _FileName);

	GameEngineRenderer* Renderer = nullptr;
protected:
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineCollision* Collision = nullptr;

private:
};

