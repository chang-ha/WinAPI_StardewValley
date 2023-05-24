#pragma once
#include "ContentLevel.h"

class Player;
class BusStation : public ContentLevel
{
public:
	// constructer destructer
	BusStation();
	~BusStation();

	// delete function
	BusStation(const BusStation& _Ohter) = delete;
	BusStation(BusStation&& _Ohter) noexcept = delete;
	BusStation& operator=(const BusStation& _Other) = delete;
	BusStation& operator=(BusStation&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	Player* Farmer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};

