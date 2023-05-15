#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Player;
class Beach : public GameEngineLevel
{
public:
	// constructer destructer
	Beach();
	~Beach();

	// delete function
	Beach(const Beach& _Ohter) = delete;
	Beach(Beach&& _Ohter) noexcept = delete;
	Beach& operator=(const Beach& _Other) = delete;
	Beach& operator=(Beach&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	Player* Farmer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};

