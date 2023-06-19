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

	float Left() const
	{
		return Pos.X - Scale.hX();
	}
	float Right() const
	{
		return Pos.X + Scale.hX();
	}
	float Top() const
	{
		return Pos.Y - Scale.hY();
	}
	float Bot() const
	{
		return Pos.Y + Scale.hY();
	}

	int iLeft() const
	{
		return static_cast<int>(Left());
	}
	int iRight() const
	{
		return static_cast<int>(Right());
	}
	int iTop() const
	{
		return static_cast<int>(Top());
	}
	int iBot() const
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

	static bool (*CollisionFunction[static_cast<int>(CollisionType::Null)][static_cast<int>(CollisionType::Null)])(const CollisionData& _LeftData, const CollisionData& _RightData);

public:
	static bool PointToPoint(const CollisionData& _LeftData, const CollisionData& _RightData);
	static bool PointToRect(const CollisionData& _LeftData, const CollisionData& _RightData);
	static bool PointToCirCle(const CollisionData& _LeftData, const CollisionData& _RightData);

	static bool RectToPoint(const CollisionData& _LeftData, const CollisionData& _RightData);
	static bool RectToRect(const CollisionData& _LeftData, const CollisionData& _RightData);
	static bool RectToCirCle(const CollisionData& _LeftData, const CollisionData& _RightData);

	static bool CirCleToPoint(const CollisionData& _LeftData, const CollisionData& _RightData);
	static bool CirCleToRect(const CollisionData& _LeftData, const CollisionData& _RightData);
	static bool CirCleToCirCle(const CollisionData& _LeftData, const CollisionData& _RightData);

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
	
	template<typename EnumType>
	bool CollisionNext(const float4& _NextPos, EnumType _Order, std::vector<GameEngineCollision*>& _Result, CollisionType _ThisType = CollisionType::CirCle, CollisionType _OtherType = CollisionType::CirCle)
	{
		return CollisionNext(_NextPos, static_cast<int>(_Order), _Result, _ThisType, _OtherType);
	}

	bool CollisionNext(const float4& _NextPos, int _Order, std::vector<GameEngineCollision*>& _Result, CollisionType _ThisType = CollisionType::CirCle, CollisionType _OtherType = CollisionType::CirCle);

	bool CollisionCheck(GameEngineCollision* _Other, CollisionType _ThisType, CollisionType _OtherType);

	bool CollisonCheckNext(const CollisionData& _Next, GameEngineCollision* _Other, CollisionType _ThisType, CollisionType _OtherType);

	float4 GetActorPivotPos();

protected:

private:
	CollisionType ColType = CollisionType::Rect;
	float4 CollisionPos;
	float4 CollisionScale;
	bool CollisionRenderValue = true;

	void DebugRender();
};

