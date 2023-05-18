#pragma once
#include "ContentLevel.h"

class BackGround;
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

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	BackGround* Back = nullptr;
	Player* Farmer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};

