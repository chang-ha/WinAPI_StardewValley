#pragma once
#include "ContentLevel.h"

class Player;
class PlayOver;
class FarmHouse : public ContentLevel
{
public:
	// constructer destructer
	FarmHouse();
	~FarmHouse();

	// delete function
	FarmHouse(const FarmHouse& _Ohter) = delete;
	FarmHouse(FarmHouse&& _Ohter) noexcept = delete;
	FarmHouse& operator=(const FarmHouse& _Other) = delete;
	FarmHouse& operator=(FarmHouse&& _Other) noexcept = delete;

	const bool GetIsSleep()
	{
		return IsSleepValue;
	}

	void SetIsSleep(const bool _SleepValue)
	{
		IsSleepValue = _SleepValue;
	}

protected:


private:
	bool IsSleepValue = false;
	PlayOver* BedDie = nullptr;
	PlayOver* TutorialRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
};

