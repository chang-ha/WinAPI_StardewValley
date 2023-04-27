#pragma once
#include "GameEngineCore.h"


// ���� : ȭ��ȿ� �����ϴ� �÷��̾� ���� �Ѿ� ��� �����Ѵٰ� ġ��
// ��ġ�� �ִٸ� �� �༮���� ǥ���ؾ� �մϴ�.
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

