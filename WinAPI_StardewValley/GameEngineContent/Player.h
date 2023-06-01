#pragma once
#include "ContentActor.h"
#define TOOL1SPEED 0.065f
#define TOOL2SPEED 0.05f

enum class PlayerState
{
	Idle,
	Run,
	Tool,
	Tool2,
	Null, // StartValue
};

enum Tile
{
	Wood = RGB(155, 75, 0),
	Grass = RGB(0, 255, 0),
	Sand = RGB(255, 200, 0),
	Stone = RGB(211, 211, 211),
	Floor = RGB(255, 255, 0),
};

enum PlayerDir
{
	Up = 0b0001,
	Down = 0b0010,
	Right = 0b0100,
	Left = 0b1000,
	Null = 0b0000, // StartValue
};

class TileMap;
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

	void SetDir(const PlayerDir _Dir)
	{
		Dir = _Dir;
		ChangeAnimationState(CurState);
	}

	void SetPlayLevel(ContentLevel* _ContentLevel) override
	{
		ContentActor::SetPlayLevel(_ContentLevel);
		if (true == CollisionDebug)
		{
			CollisionDebug = false;
		}
	}

	float4 TileLimit(TileMap* _CurTile);

protected:

private:
	float Speed = 350.0f;
	PlayerState State = PlayerState::Null;
	int Dir = PlayerDir::Null;
	std::string CurState = "";
	int PrevTileColor = 0;
	int CurTileColor = 0;
	bool FPS = false;

	void StateUpdate(float _Delta);

	void IdleStart();
	void RunStart();
	void ToolStart();
	void Tool2Start();

	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void ToolUpdate(float _Delta);
	void Tool2Update(float _Delta);

	void DirCheck();
	void ToolDirCheck();

	void ChangeState(PlayerState State);
	void ChangeAnimationState(const std::string& _AnimationName);

	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	// PlayerCollision Value
	bool CollisionDebug = false;
	float4 UpCollision = { };
	float4 LeftCollision = { };
	float4 RightCollision = { };
	float4 DownCollision = { };
};

