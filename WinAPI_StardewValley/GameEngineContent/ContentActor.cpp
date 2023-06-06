#include <GameEngineCore/GameEngineCamera.h>

#include "ContentActor.h"
#include "ContentLevel.h"

ContentActor::ContentActor()
{

}

ContentActor::~ContentActor()
{

}


float4 ContentActor::WindowActorPos()
{
	return GetPos() - GetLevel()->GetMainCamera()->GetPos();
}