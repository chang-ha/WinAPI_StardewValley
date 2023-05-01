#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

class GameEngineActor : public GameEngineObject
{
public:
	// constructer destructer
	GameEngineActor();
	~GameEngineActor();

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
protected:

private:
	float4 Pos;
	float4 Scale;
};

