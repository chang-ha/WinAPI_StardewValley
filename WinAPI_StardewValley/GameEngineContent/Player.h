#pragma once
#include "ContentActor.h"
#include "ContentsEnum.h"

enum class PlayerState
{
	Null, // StartValue
	Idle,
	Run,
	Tool,
	Tool2,
	Tool3,
	Harvest,
	OpenBox,
	Die,
};

enum Tile
{
	Wood = RGB(155, 75, 0),
	Grass = RGB(0, 255, 0),
	Sand = RGB(255, 200, 0),
	Stone = RGB(211, 211, 211),
	Floor = RGB(255, 255, 0),
	PrevMap = RGB(0, 0, 255),
	NextMap = RGB(255, 0, 0),
	Building = RGB(0, 255, 255),
	SleepTile = RGB(255, 0, 255)
};

enum PlayerDir
{
	Null = 0b0000, // StartValue
	Up = 0b0001,
	Down = 0b0010,
	Right = 0b0100,
	Left = 0b1000,
};

class TileMap;
class ContentItem;
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

	void SetIsUpdate(bool _Value)
	{
		IsUpdate = _Value;
	}

	bool GetIsUpdate()
	{
		return IsUpdate;
	}

	GameEngineCollision* GetBodyCollision()
	{
		return BodyCollision;
	}

	int GetDir()
	{
		return Dir;
	}

	float4 TileLimit();

	void ChangeState(PlayerState State);

	void SetCollisionTexture(const std::string& _CollisionTexture);

	int GetTileColor(unsigned int _Color, float4 _Pos = float4::ZERO);

	void StopPlayer();

	void ChangeMap();

	GameEngineRenderer* BodyRenderer = nullptr;
	GameEngineRenderer* ArmRenderer = nullptr;
	GameEngineRenderer* HairRenderer = nullptr;
	GameEngineRenderer* ShirtRenderer = nullptr;
	GameEngineRenderer* PantsRenderer = nullptr;
	GameEngineRenderer* ToolRenderer = nullptr;
	GameEngineRenderer* ShadowRenderer = nullptr;
	GameEngineRenderer* WaterRenderer = nullptr;
	GameEngineRenderer* EmoteRenderer = nullptr;

	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* ToolCollision = nullptr;
protected:

private:
	bool IsUpdate = true;
	bool IsCheatOn = false;
	bool CreateFade = false;
	float Speed = 350.0f;
	int PrevTileColor = 0;
	int CurTileColor = 0;
	int MapColor = 0;
	std::string CurState = "";
	std::string ToolDir = "";
	ContentItem* CurItem = nullptr;
	GameEngineRenderer* CurItemRenderer = nullptr;

	PlayerState State = PlayerState::Null;
	int Dir = PlayerDir::Null;

	GameEngineWindowTexture* CollisionTexture = nullptr;

	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void ToolCollisionCreate(CollisionOrder _CollisionType);

	// State Start
	void IdleStart();
	void RunStart();
	void ToolStart();
	void Tool2Start();
	void Tool3Start();
	void HarvestStart();
	void OpenBoxStart();
	void DieStart();

	// State Update
	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void ToolUpdate(float _Delta);
	void Tool2Update(float _Delta);
	void Tool3Update(float _Delta);
	void HarvestUpdate(float _Delta);
	void OpenBoxUpdate(float _Delta);
	void DieUpdate(float _Delta);

	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _AnimationName);

	// DirCheck
	void DirCheck();
	void ToolDirCheck();

	// PlayerCollision Value
	bool CollisionDebug = false;
	float4 UpCollision = { };
	float4 LeftCollision = { };
	float4 RightCollision = { };
	float4 DownCollision = { };
};

