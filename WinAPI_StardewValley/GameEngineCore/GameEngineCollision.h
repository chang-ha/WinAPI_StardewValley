#pragma once

class GameEngineCollision
{
public:
	// constructer destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete function
	GameEngineCollision(const GameEngineCollision& _Ohter) = delete;
	GameEngineCollision(GameEngineCollision&& _Ohter) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

protected:

private:

};

