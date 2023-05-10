#include "GameEngineCamera.h"
#include <GameEngineBase/GameEngineDebug.h>

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
	Renderers[_Order].push_back(_Renderer);
}

void GameEngineCamera::Render()
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
			Renderer->Render(this);
		}
	}
}