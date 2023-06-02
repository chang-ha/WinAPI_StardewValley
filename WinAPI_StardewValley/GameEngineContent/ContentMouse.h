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

	GameEngineRenderer* GetMouseRenderer()
	{
		return MouseRenderer;
	}

	GameEngineCollision* GetMouseCollision()
	{
		return MouseCollision;
	}

protected:

private:
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineRenderer* MouseRenderer = nullptr;
	GameEngineCollision* MouseCollision = nullptr;
};

