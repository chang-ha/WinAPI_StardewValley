#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentActor.h"
#include "ContentLevel.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

ContentActor::ContentActor()
{
	
}

ContentActor::~ContentActor()
{

}

void ContentActor::Start()
{

}

float4 ContentActor::WindowActorPos()
{
	return GetPos() - GetLevel()->GetMainCamera()->GetPos();
}