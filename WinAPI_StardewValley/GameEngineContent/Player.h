#pragma once
#include <GameEngineCore/GameEngineActor.h>


enum class PlayerState
{
	Idle,
	Run,
	UseTool,
	Null, // StartValue
};

enum class PlayerDir
{
	Up,
	Down,
	Right,
	Left,
	Null, // StartValue
};

class GameEngineLevel;
class Player : public GameEngineActor
{
	friend GameEngineLevel;

public:
	static Player* MainPlayer;

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
	PlayerState State = PlayerState::Null;
	PlayerDir Dir = PlayerDir::Null;
	std::string CurState = "";

	void StateUpdate(float _DeltaTime);

	void IdleStart();
	void RunStart();
	void UseToolStart();

	void IdleUpdate(float _DeltaTime);
	void RunUpdate(float _DeltaTime);
	void UseToolUpdate(float _DeltaTime);

	void ChangeState(PlayerState State);

	void DirCheck();
	void ChangeAnimationState(const std::string& _AnimationName);

private:
	float Speed = 400.0f;
	void LevelStart() override;

	void Start() override;
	void Update(float _DeltaTime) override;
};

