#pragma once
#include <GameEngineCore/GameEngineActor.h>


enum class PlayerState
{
	Idle,
	Run,
	UseTool,
	Max, // StartValue
};

class GameEngineLevel;
class Player : public GameEngineActor
{
	friend GameEngineLevel;
public:
	// constructer destructer
	Player();
	~Player();

	// delete function
	Player(const Player& _Ohter) = delete;
	Player(Player&& _Ohter) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	GameEngineRenderer* BodyRenderer = nullptr;
	GameEngineRenderer* ArmRenderer = nullptr;
	GameEngineRenderer* HairRenderer = nullptr;

	GameEngineRenderer* ShirtRenderer = nullptr;
	GameEngineRenderer* PantsRenderer = nullptr;
	GameEngineRenderer* HatRenderer = nullptr;

protected:
	void StateUpdate(float _DeltaTime);

	void IdleStart();
	void RunStart();
	void UseToolStart();

	// 클래스로 만들어도 되고.
	void IdleUpdate(float _DeltaTime);
	void RunUpdate(float _DeltaTime);
	void UseToolUpdate(float _DeltaTime);

	void ChangeState(PlayerState State);

	PlayerState State = PlayerState::Max;

private:
	float Speed = 400.0f;

	void Start() override;
	void Update(float _DeltaTime) override;
};

