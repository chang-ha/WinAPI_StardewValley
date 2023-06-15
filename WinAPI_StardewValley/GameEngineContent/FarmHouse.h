#pragma once
#include "ContentLevel.h"

class Player;
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

	bool GetIsSleep()
	{
		return IsSleepValue;
	}

	void SetIsSleep(bool _SleepValue)
	{
		IsSleepValue = _SleepValue;
	}

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
	bool IsSleepValue = false;
};

