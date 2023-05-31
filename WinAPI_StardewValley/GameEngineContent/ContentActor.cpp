#include <GameEngineBase/GameEngineDebug.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>

#include "ContentActor.h"
#include "ContentLevel.h"

ContentActor::ContentActor()
{

}

ContentActor::~ContentActor()
{

}

void ContentActor::SetCollisionTexture(const std::string& _CollisionTexture)
{
	CollisionTexture = ResourcesManager::GetInst().FindTexture(_CollisionTexture);
	if (nullptr == CollisionTexture)
	{
		MsgBoxAssert(_CollisionTexture + "는 존재하지 않는 CollisionTexture입니다.");
	}
}

int ContentActor::GetTileColor(unsigned int _Color, float4 _Pos /*= float4::ZERO*/)
{
	if (nullptr == CollisionTexture)
	{
		MsgBoxAssert("CollisionTexture가 세팅되어 있지 않습니다.");
	}
	float4 Pos = GetPos();
	Pos += _Pos;
	Pos *= 1.0f / RENDERRATIO;
	return CollisionTexture->GetColor(_Color, Pos);
}

float4 ContentActor::WindowActorPos()
{
	return GetPos() - GetLevel()->GetMainCamera()->GetPos();
}