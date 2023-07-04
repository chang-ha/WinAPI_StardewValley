#pragma once
#include "ContentLevel.h"

class ContentActor;
class PlayOver;
class EndingLevel : public ContentLevel
{
public:
	// constructer destructer
	EndingLevel();
	~EndingLevel();

	// delete function
	EndingLevel(const EndingLevel& _Ohter) = delete;
	EndingLevel(EndingLevel&& _Ohter) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	PlayOver* CatrgoryActor = nullptr;
	GameEngineCollision* SkipButtonCollision = nullptr;
};

