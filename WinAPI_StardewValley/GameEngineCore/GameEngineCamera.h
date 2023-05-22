#pragma once
#include <map>
#include <list>
#include <string>

#include <GameEngineBase/GameEngineMath.h>

#include "GameEngineRenderer.h"

class GameEngineActor;
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCamera
{
	friend GameEngineActor;
	friend GameEngineLevel;
	friend GameEngineRenderer;
public:
	// constructer destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete function
	GameEngineCamera(const GameEngineCamera& _Ohter) = delete;
	GameEngineCamera(GameEngineCamera&& _Ohter) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	float4 GetPos()
	{
		return Pos;
	}

	void SetPos(const float4& _Pos)
	{
		Pos = _Pos;
	}

	void AddPos(const float4& _Pos)
	{
		Pos += _Pos;
	}
protected:

private:
	float4 Pos = float4::ZERO;
	std::map<int, std::list<GameEngineRenderer*>> Renderers;
	void PushRenderer(GameEngineRenderer* _Renderer, int _Order);
	void Render(float _DeltaTime);
	void Release();
};

