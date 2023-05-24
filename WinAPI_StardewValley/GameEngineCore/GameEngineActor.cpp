#include <GameEngineBase/GameEngineDebug.h>

#include "GameEngineCollision.h"
#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"

GameEngineActor::GameEngineActor()
{

}

GameEngineActor::~GameEngineActor()
{
	for (GameEngineRenderer* _Renderer : AllRenderer)
	{
		if (nullptr != _Renderer)
		{
			delete _Renderer;
			_Renderer = nullptr;
		}
	}

	for (GameEngineCollision* _Collision : AllCollision)
	{
		if (nullptr != _Collision)
		{
			delete _Collision;
			_Collision = nullptr;
		}
	}
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _ImageName, int _Order)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();
	NewRenderer->Master = this;
	NewRenderer->MainCameraSetting();
	NewRenderer->SetOrder(_Order);
	if ("" != _ImageName)
	{
		NewRenderer->SetTexture(_ImageName);
	}
	AllRenderer.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateUIRenderer(const std::string& _ImageName, int _Order)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();
	NewRenderer->Master = this;
	NewRenderer->UICameraSetting();
	NewRenderer->SetOrder(_Order);
	if (_ImageName != "")
	{
		NewRenderer->SetTexture(_ImageName);
	}
	AllRenderer.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineCollision* GameEngineActor::CreateCollision(int _Order/* = 0*/)
{
	GameEngineCollision* NewCollision = new GameEngineCollision();

	NewCollision->Master = this;
	NewCollision->Start();
	NewCollision->SetOrder(_Order);
	AllCollision.push_back(NewCollision);

	return NewCollision;
}

void GameEngineActor::ActorRelease()
{
	std::list<GameEngineRenderer*>::iterator ObjectStartIter = AllRenderer.begin();
	std::list<GameEngineRenderer*>::iterator ObjectEndIter = AllRenderer.end();
	for (; ObjectStartIter != ObjectEndIter; )
	{
		GameEngineRenderer* Renderer = *ObjectStartIter;
		if (false == Renderer->IsDeath())
		{
			++ObjectStartIter;
			continue;
		}

		if (nullptr == Renderer)
		{
			MsgBoxAssert("nullptr인 액터가 레벨의 리스트에 들어가 있었습니다.");
			continue;
		}

		delete Renderer;
		Renderer = nullptr;
		ObjectStartIter = AllRenderer.erase(ObjectStartIter);
	}
}
