#include <GameEngineBase/GameEngineDebug.h>

#include "GameEngineLevel.h"
#include "GameEngineCamera.h"

GameEngineLevel::GameEngineLevel()
{
	MainCamera = new GameEngineCamera();
	UICamera = new GameEngineCamera();
}

GameEngineLevel::~GameEngineLevel()
{
	if (nullptr != MainCamera)
	{
		delete MainCamera;
		MainCamera = nullptr;
	}

	if (nullptr != UICamera)
	{
		delete UICamera;
		UICamera = nullptr;
	}

	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;
		for (GameEngineActor* _Actor : Group)
		{
			if (nullptr != _Actor)
			{
				delete _Actor;
				_Actor = nullptr;
			}
		}
	}
}

void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;
		for (GameEngineActor* _Actor : Group)
		{
			if (false == _Actor->IsUpdate())
			{
				continue;
			}
			_Actor->AddLiveTime(_DeltaTime);
			_Actor->Update(_DeltaTime);
		}
	}
}
void GameEngineLevel::ActorRender(float _DeltaTime)
{
	MainCamera->Render(_DeltaTime);
	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;
		for (GameEngineActor* _Actor : Group)
		{
			if (false == _Actor->IsUpdate())
			{
				continue;
			}
			_Actor->Render();
		}
	}
}

void GameEngineLevel::ActorInit(GameEngineActor* _Actor, int _Order)
{
	_Actor->Level = this;
	_Actor->SetOrder(_Order);
	_Actor->Start();
}

void GameEngineLevel::ActorRelease()
{
	// MainCamera->Release();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = AllActors.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = AllActors.end();
	std::list<GameEngineActor*>::iterator ObjectStartIter;
	std::list<GameEngineActor*>::iterator ObjectEndIter;
	for ( ; GroupStartIter != GroupEndIter ; ++GroupStartIter)
	{
		std::list<GameEngineActor*>& Group = GroupStartIter->second;
		ObjectStartIter = Group.begin();
		ObjectEndIter = Group.end();
		for (; ObjectStartIter != ObjectEndIter; )
		{
			GameEngineActor* Object = *ObjectStartIter;
			if (false == Object->IsDeath())
			{
				Object->ActorRelease();
				++ObjectStartIter;
				continue;
			}

			if (nullptr == Object)
			{
				MsgBoxAssert("null인 Object는 Release할 수 없습니다.");
			}
			delete Object;
			Object = nullptr;
			ObjectStartIter = Group.erase(ObjectStartIter);
		}
	}
}
