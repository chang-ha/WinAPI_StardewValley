#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"
#include <string>
#include <list>

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

	void SetScale(const float4& _Scale)
	{
		Scale = _Scale;
	}
	
	void AddPos(const float4& _Pos)
	{
		Pos += _Pos;
	}

	float4 GetPos()
	{
		return Pos;
	}

	float4 GetScale()
	{
		return Scale;
	}

	GameEngineRenderer* CreateRenderer(const std::string& _ImageName);

	GameEngineLevel* GetLevel()
	{
		return Level;
	}
protected:

private:
	GameEngineLevel* Level;
	float4 Pos = float4::ZERO;
	float4 Scale = float4::ZERO;
	std::list<GameEngineRenderer*> AllRenderer;
};
