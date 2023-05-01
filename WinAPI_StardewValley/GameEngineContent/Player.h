#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Player : public GameEngineActor
{
public:
	// constructer destructer
	Player();
	~Player();

	// delete function
	Player(const Player& _Ohter) = delete;
	Player(Player&& _Ohter) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

