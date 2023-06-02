#pragma once
#include <string>

#include <GameEngineCore/GameEngineActor.h>

#include "GlobalValue.h"

class GameEngineWindowTexture;
class ContentLevel;
class ContentMouse : public GameEngineActor
{
	friend ContentLevel;
public:
	// constructer destructer
	ContentMouse();
	~ContentMouse();

	// delete function
	ContentMouse(const ContentMouse& _Ohter) = delete;
	ContentMouse(ContentMouse&& _Ohter) noexcept = delete;
	ContentMouse& operator=(const ContentMouse& _Other) = delete;
	ContentMouse& operator=(ContentMouse&& _Other) noexcept = delete;

	void Start();

	void Update(float _Delta) override;

	void Init(const std::string& _FileName);

	float4 GetScale()
	{
		return Scale;
	}

	GameEngineRenderer* Renderer = nullptr;
	GameEngineCollision* MouseCollision = nullptr;
protected:

private:
	GameEngineWindowTexture* Texture = nullptr;
	float4 Scale = {};
};

