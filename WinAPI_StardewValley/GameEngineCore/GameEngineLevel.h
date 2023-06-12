#pragma once
#include <map>
#include <list>

#include "GameEngineObject.h"
#include "GameEngineActor.h"

class GameEngineCamera;
class GameEngineCore;
class GameEngineCollision;
class GameEngineLevel : public GameEngineObject
{
	friend GameEngineCore;
	friend GameEngineActor;
	friend GameEngineCollision;
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
		ActorInit(NewActor, _Order);
		GroupList.push_back(NewActor);
		return dynamic_cast<ActorType*>(NewActor);
	}

	template<typename ActorType, typename EnumType>
	ActorType* CreateActor(EnumType _Order)
	{
		return CreateActor<ActorType>(static_cast<int>(_Order));
	}

	GameEngineCamera* GetMainCamera()
	{
		return MainCamera;
	}

	GameEngineCamera* GetUICamera()
	{
		return UICamera;
	}

	static void CollisionDebugRenderSwitch()
	{
		IsCollisionDebugRender = !IsCollisionDebugRender;
	}

	void OverCheck(GameEngineLevel* _PrevLevel);

protected:
	virtual void LevelStart(GameEngineLevel* _PrevLevel) {}
	virtual void LevelEnd(GameEngineLevel* _NextLevel) {}

private:
	static bool IsCollisionDebugRender;

	GameEngineCamera* MainCamera;
	GameEngineCamera* UICamera;

	std::map<int, std::list<GameEngineActor*>> AllActors;
	std::map<int, std::list<GameEngineCollision*>> AllCollision;

	void ActorUpdate(float _Delta);
	void ActorRender(float _Delta);
	void ActorInit(GameEngineActor* _Actor, int _Order);
	void ActorRelease();
	void ActorLevelEnd();
	void ActorLevelStart();
	void CollisionOverRelease();
	void CollisionRelease();
};

