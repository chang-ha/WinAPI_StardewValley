#pragma once
#include <vector>

#include <GameEngineBase/GameEngineMath.h>

#include "GameEngineActorSubObject.h"

enum class CollisionType
{
	Point,
	Rect,
	CirCle,
	Null
};

class CollisionData
{
public:
	float4 Pos;
	float4 Scale;

	float Left()
	{
		return Pos.X - Scale.hX();
	}
	float Right()
	{
		return Pos.X + Scale.hX();
	}
	float Top()
	{
		return Pos.Y - Scale.hY();
	}
	float Bot()
	{
		return Pos.Y + Scale.hY();
	}

	int iLeft()
	{
		return static_cast<int>(Left());
	}
	int iRight()
	{
		return static_cast<int>(Right());
	}
	int iTop()
	{
		return static_cast<int>(Top());
	}
	int iBot()
	{
		return static_cast<int>(Bot());
	}
};

class GameEngineActor;
class CollisionInitClass;
class GameEngineCollision : public GameEngineActorSubObject
{
	friend CollisionInitClass;
	friend GameEngineActor;
	friend GameEngineLevel;

	static bool (*CollisionFunction[static_cast<int>(CollisionType::Null)][static_cast<int>(CollisionType::Null)])(GameEngineCollision* _Left, GameEngineCollision* _Right);

public:
	static bool PointToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool PointToRect(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool PointToCirCle(GameEngineCollision* _Left, GameEngineCollision* _Right);

	static bool RectToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool RectToCirCle(GameEngineCollision* _Left, GameEngineCollision* _Right);

	static bool CirCleToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool CirCleToRect(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool CirCleToCirCle(GameEngineCollision* _Left, GameEngineCollision* _Right);

public:
	// constructer destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete function
	GameEngineCollision(const GameEngineCollision& _Ohter) = delete;
	GameEngineCollision(GameEngineCollision&& _Ohter) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	void SetCollisionScale(const float4& _Scale)
	{
		CollisionScale = _Scale;
	}

	void SetCollisionPos(const float4& _Pos)
	{
		CollisionPos = _Pos;
	}

	void SetOrder(int _Order) override;

	void SetCollisionType(CollisionType _ColType)
	{
		ColType = _ColType;
	}

	void On() override
	{
		GameEngineActorSubObject::On();
		CollisionRenderValue = true;
	}

	void Off() override
	{
		GameEngineActorSubObject::Off();
		CollisionRenderValue = false;
	}

	float4 GetActorScale()
	{
		return CollisionScale;
	}

	CollisionData GetCollisionData()
	{
		CollisionData Data;
		Data.Pos = GetActorPivotPos();
		Data.Scale = GetActorScale();
		return Data;
	}

	template <typename EnumType>
	bool Collision(EnumType _Order, std::vector<GameEngineCollision*>& _Result, CollisionType _ThisType = CollisionType::Circle, CollisionType _OtherType = CollisionType::Circle)
	{
		return Collision(static_cast<int>(_Order), _Result, _ThisType, _OtherType);
	}
	
	bool Collision(int _Order, std::vector<GameEngineCollision*>& _Result, CollisionType _ThisType = CollisionType::CirCle, CollisionType _OtherType = CollisionType::CirCle);
	
	bool CollisionCheck(GameEngineCollision* _Other, CollisionType _ThisType, CollisionType _OtherType);

	float4 GetActorPivotPos();

protected:

private:
	CollisionType ColType = CollisionType::Rect;
	float4 CollisionPos;
	float4 CollisionScale;
	bool CollisionRenderValue = true;

	void DebugRender();
};

