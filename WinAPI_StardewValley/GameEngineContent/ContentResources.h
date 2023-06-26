#pragma once
#include "ContentActor.h"

class GameEngineRenderer;
class GameEngineCollision;
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

protected:
	void Start() override;

	GameEngineRenderer* Renderer = nullptr;
	GameEngineRenderer* ShadowRenderer = nullptr;
	GameEngineCollision* Collision = nullptr;

private:
};

