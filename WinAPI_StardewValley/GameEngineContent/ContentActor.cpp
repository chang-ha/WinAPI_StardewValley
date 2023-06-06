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
	Collision = CreateCollision(CollisionOrder::Actor);
	Collision->SetCollisionScale(TILESIZE * RENDERRATIO);
}

float4 ContentActor::WindowActorPos()
{
	return GetPos() - GetLevel()->GetMainCamera()->GetPos();
}