#pragma once
#include <vector>

#include <GameEngineBase/GameEngineMath.h>

#include "GameEngineObject.h"
enum class CollisionType
{
	Point,
	Rect,
	Circle,
	Null
};

class GameEngineActor;
class GameEngineCollision : public GameEngineObject
{
	friend GameEngineActor;
public:
	// static bool PointToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right);
	// static bool PointToRect(GameEngineCollision* _Left, GameEngineCollision* _Right);
	// static bool PointToCirCle(GameEngineCollision* _Left, GameEngineCollision* _Right);
	// 
	// static bool RectToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right);
	// static bool RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right);
	// static bool RectToCirCle(GameEngineCollision* _Left, GameEngineCollision* _Right);
	// 
	// static bool CirCleToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right);
	// static bool CirCleToRect(GameEngineCollision* _Left, GameEngineCollision* _Right);
	// static bool CirCleToCirCle(GameEngineCollision* _Left, GameEngineCollision* _Right);
	// 
	// static bool (*CollisionFunction[static_cast<int>(CollisionType::Null)][static_cast<int>(CollisionType::Null)])(GameEngineCollision* _Left, GameEngineCollision* _Right);

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

	GameEngineActor* GetActor()
	{
		return Master;
	}

	// template <typename EnumType>
	// bool Collision(EnumType _Order, std::vector<GameEngineCollision*>& _Result, CollisionType _ThisType = CollisionType::Circle, CollisionType _OtherType = CollisionType::Circle)
	// {
	// 	return Collision(static_cast<int>(_Order), _Result, _ThisType, _OtherType);
	// }
	// 
	// bool Collision(int _Order, std::vector<GameEngineCollision*>& _Result, CollisionType _ThisType = CollisionType::Circle, CollisionType _OtherType = CollisionType::Circle);
	// 
	// bool CollisionCheck(GameEngineCollision* _Other, CollisionType _ThisType, CollisionType _OtherType);
protected:

private:
	GameEngineActor* Master = nullptr;
	float4 CollisionPos;
	float4 CollisionScale;
};

