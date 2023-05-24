#pragma once
#include "ContentLevel.h"

class Player;
class Farm : public ContentLevel
{
public:
	// constructer destructer
	Farm();
	~Farm();

	// delete function
	Farm(const Farm& _Ohter) = delete;
	Farm(Farm&& _Ohter) noexcept = delete;
	Farm& operator=(const Farm& _Other) = delete;
	Farm& operator=(Farm&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	Player* Farmer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};

