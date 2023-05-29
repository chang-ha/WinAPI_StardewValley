#pragma once
#include <GameEnginePlatform/GameEngineSound.h>

#include <GameEngineCore/GameEngineActor.h>

class GameEngineWindowTexture;
class ContentLevel;
class ContentActor : public GameEngineActor
{
public:
	// constructer destructer
	ContentActor();
	~ContentActor();

	// delete function
	ContentActor(const ContentActor& _Ohter) = delete;
	ContentActor(ContentActor&& _Ohter) noexcept = delete;
	ContentActor& operator=(const ContentActor& _Other) = delete;
	ContentActor& operator=(ContentActor&& _Other) noexcept = delete;

	void SetCollisionTexture(const std::string& _CollisionTexture);

	int GetFrontColor(unsigned int _Color, float4 _Pos = float4::ZERO);

	void SetPlayLevel(ContentLevel* _ContentLevel)
	{
		PlayLevel = _ContentLevel;
	}

	float4 WindowActorPos();

	GameEngineSoundPlayer EffectPlayer;

protected:
	ContentLevel* PlayLevel = nullptr;

private:
	GameEngineWindowTexture* CollisionTexture = nullptr;
};

