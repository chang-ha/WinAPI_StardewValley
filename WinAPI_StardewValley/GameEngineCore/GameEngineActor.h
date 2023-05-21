#pragma once
#include <string>
#include <list>

#include <GameEngineBase/GameEngineMath.h>

#include "GameEngineObject.h"

class GameEngineLevel;
class GameEngineRenderer;
class GameEngineActor : public GameEngineObject
{
	friend GameEngineLevel;
public:
	// constructer destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete function
	GameEngineActor(const GameEngineActor& _Ohter) = delete;
	GameEngineActor(GameEngineActor&& _Ohter) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	void SetPos(const float4& _Pos)
	{
		Pos = _Pos;
	}
	
	void AddPos(const float4& _Pos)
	{
		Pos += _Pos;
	}

	float4 GetPos()
	{
		return Pos;
	}

	GameEngineRenderer* CreateRenderer(const std::string& _ImageName, int _Order);

	template <typename EnumType>
	GameEngineRenderer* CreateRenderer(const std::string& _ImageName, EnumType _Order)
	{
		return CreateRenderer(_ImageName, static_cast<int>(_Order));
	}

	template <typename EnumType>
	GameEngineRenderer* CreateRenderer(EnumType _Order)
	{
		return CreateRenderer("", static_cast<int>(_Order));
	}

	GameEngineRenderer* CreateRenderer(int _Order = 0)
	{
		return CreateRenderer("", _Order);
	}

	GameEngineRenderer* CreateCollision(int _Order = 0);

	GameEngineLevel* GetLevel()
	{
		return Level;
	}
protected:
	virtual void LevelStart() {}
	virtual void LevelEnd() {}

private:
	GameEngineLevel* Level;
	float4 Pos = float4::ZERO;
	std::list<GameEngineRenderer*> AllRenderer;
	void ActorRelease();
};

