#pragma once
#include "ContentActor.h"

enum class PlayerState
{
	Idle,
	Run,
	Tool,
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

class Player : public ContentActor
{
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

	void SetDir(PlayerDir _Dir)
	{
		Dir = _Dir;
		ChangeAnimationState(CurState);
	}

protected:

private:
	float Speed = 1000.0f;
	PlayerState State = PlayerState::Null;
	PlayerDir Dir = PlayerDir::Null;
	std::string CurState = "";

	void StateUpdate(float _DeltaTime);

	void IdleStart();
	void RunStart();
	void ToolStart();

	void IdleUpdate(float _DeltaTime);
	void RunUpdate(float _DeltaTime);
	void ToolUpdate(float _DeltaTime);

	void DirCheck();
	void ChangeState(PlayerState State);
	void ChangeAnimationState(const std::string& _AnimationName);

	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	// PlayerCollision Value
	// TopCollision = Player¿« GetPos()
	float4 LeftCollision = { -32, 32 };
	float4 RightCollision = { 32, 32 };
	float4 DownCollision = { 0 , 48 };
};

