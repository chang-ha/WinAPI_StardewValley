#pragma once
#include "GameEngineCore.h"


// 설명 : 화면안에 존재하는 플레이어 몬스터 총알 등등 존재한다고 치고
// 위치가 있다면 이 녀석으로 표현해야 합니다.
class GameEngineActor : public GameEngineCore
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

protected:

private:

};

