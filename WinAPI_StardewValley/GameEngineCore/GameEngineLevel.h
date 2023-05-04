#pragma once
#include <map>
#include <list>
#include "GameEngineObject.h"
#include "GameEngineActor.h"


class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCore;
public:
	// constructer destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete function
	GameEngineLevel(const GameEngineLevel& _Ohter) = delete;
	GameEngineLevel(GameEngineLevel&& _Ohter) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	template <typename ActorType>
	void CreateActor(int _Order = 0)
	{
		std::list<GameEngineActor*>& GroupList = AllActors[_Order];
		GameEngineActor* NewActor = new ActorType();
		ActorInit(NewActor);
		GroupList.push_back(NewActor);
	}
protected:

private:
	std::map<int, std::list<GameEngineActor*>> AllActors;

	void ActorUpdate(float _Delta);
	void ActorRender();
	void ActorInit(GameEngineActor* _Actor);
};

