#pragma once
#include <map>
#include <list>
#include "GameEngineRenderer.h"
class GameEngineCamera
{
public:
	// constructer destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete function
	GameEngineCamera(const GameEngineCamera& _Ohter) = delete;
	GameEngineCamera(GameEngineCamera&& _Ohter) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

protected:

private:
	std::map<int, std::list<GameEngineRenderer*>> Renderers;
};

