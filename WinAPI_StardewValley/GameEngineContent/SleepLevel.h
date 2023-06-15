#pragma once
#include "ContentLevel.h"

class SleepLevel : public ContentLevel
{
public:
	// constructer destructer
	SleepLevel();
	~SleepLevel();

	// delete function
	SleepLevel(const SleepLevel& _Ohter) = delete;
	SleepLevel(SleepLevel&& _Ohter) noexcept = delete;
	SleepLevel& operator=(const SleepLevel& _Other) = delete;
	SleepLevel& operator=(SleepLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	GameEngineCollision* OK_Button_Collision = nullptr;
};

