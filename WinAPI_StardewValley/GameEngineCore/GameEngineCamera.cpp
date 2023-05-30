#include <GameEngineBase/GameEngineDebug.h>

#include "GameEngineCamera.h"
#include "GameEngineActor.h"

GameEngineCamera::GameEngineCamera()
{

}

GameEngineCamera::~GameEngineCamera()
{

}

void GameEngineCamera::PushRenderer(GameEngineRenderer* _Renderer, int _Order)
{
	if (nullptr == _Renderer)
	{
		MsgBoxAssert("nullptr인 Renderer를 그룹에 넣을순 없습니다.");
	}
	_Renderer->Camera = this;
	Renderers[_Order].push_back(_Renderer);
}

void GameEngineCamera::Render(float _DeltaTime)
{
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStartIter = Renderers.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEndIter = Renderers.end();
	for (;GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineRenderer*>& List = GroupStartIter->second;
		std::list<GameEngineRenderer*>::iterator RendererStartIter = List.begin();
		std::list<GameEngineRenderer*>::iterator RendererEndIter = List.end();
		for (; RendererStartIter != RendererEndIter ; ++RendererStartIter)
		{
			GameEngineRenderer* Renderer = *RendererStartIter;
			if (false == Renderer->IsUpdate())
			{
				continue;
			}
			Renderer->Render(_DeltaTime);
		}
	}
}

void GameEngineCamera::Release()
{
	std::map <int, std::list<GameEngineRenderer*>>::iterator GroupStartIter = Renderers.begin();
	std::map <int, std::list<GameEngineRenderer*>>::iterator GroupEndIter = Renderers.end();
	std::list<GameEngineRenderer*>::iterator ObjectStartIter;
	std::list<GameEngineRenderer*>::iterator ObjectEndIter;
	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineRenderer*>& Group = GroupStartIter->second;
		ObjectStartIter = Group.begin();
		ObjectEndIter = Group.end();
		for (; ObjectStartIter != ObjectEndIter; )
		{
			GameEngineRenderer* Object = *ObjectStartIter;
			if (false == Object->IsDeath())
			{
				++ObjectStartIter;
				continue;
			}

			if (nullptr == Object)
			{
				MsgBoxAssert("null인 Object는 Release할 수 없습니다.");
				continue;
			}
			ObjectStartIter = Group.erase(ObjectStartIter);
		}
	}
}

void GameEngineCamera::OverRelease()
{

	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStartIter = Renderers.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEndIter = Renderers.end();
	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineRenderer*>& Group = GroupStartIter->second;
		std::list<GameEngineRenderer*>::iterator ActorStartIter = Group.begin();
		std::list<GameEngineRenderer*>::iterator ActorEndIter = Group.end();
		for (; ActorStartIter != ActorEndIter; )
		{
			GameEngineRenderer* Object = *ActorStartIter;
			if (false == Object->GetActor()->IsLevelOver())
			{
				++ActorStartIter;
				continue;
			}

			if (nullptr == Object)
			{
				MsgBoxAssert("nullptr인 랜더러가 레벨의 리스트에 들어가 있었습니다.");
				continue;
			}
			// [s] [a] [a]     [a] [e]
			ActorStartIter = Group.erase(ActorStartIter);

		}
	}
}