#include <list>

#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineCollision.h"

// bool (*GameEngineCollision::CollisionFunction[static_cast<int>(CollisionType::Null)][static_cast<int>(CollisionType::Null)])(GameEngineCollision* _Left, GameEngineCollision* _Right) = { nullptr };

GameEngineCollision::GameEngineCollision()
{

}

GameEngineCollision::~GameEngineCollision()
{

}

void GameEngineCollision::SetOrder(int _Order)
{
	std::list<GameEngineCollision*>& PrevCollisions = Master->GetLevel()->AllCollision[GetOrder()];
	PrevCollisions.remove(this);

	GameEngineObject::SetOrder(_Order);

	std::list<GameEngineCollision*>& NextCollisions = Master->GetLevel()->AllCollision[GetOrder()];
	NextCollisions.push_back(this);
}
