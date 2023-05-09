#pragma once
#include <map>
#include <list>
#include "GameEngineObject.h"
#include "GameEngineActor.h"

class GameEngineCamera;
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCore;
	friend GameEngineActor;
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
	ActorType* CreateActor(int _Order = 0)
	{
		std::list<GameEngineActor*>& GroupList = AllActors[_Order];
		GameEngineActor* NewActor = new ActorType();
		ActorInit(NewActor);
		GroupList.push_back(NewActor);
		return dynamic_cast<ActorType*>(NewActor);
	}
protected:

private:
	std::map<int, std::list<GameEngineActor*>> AllActors;

	void ActorUpdate(float _Delta);
	void ActorRender();
	void ActorInit(GameEngineActor* _Actor);
};

