#pragma once
#include <random>

// Ό³Έν :
class GameEngineRandom
{
public:
	static GameEngineRandom MainRandom;

	// constrcuter destructer
	GameEngineRandom();
	GameEngineRandom(int _Seed);
	~GameEngineRandom();

	// delete Function
	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;

	int RandomInt(int _Min, int _Max);

	float RandomFloat(float _Min, float _Max);

	void SetSeed(__int64 _Seed)
	{
		MtGen = std::mt19937_64(_Seed);
	}

protected:

private:
	std::mt19937_64 MtGen = std::mt19937_64(time(nullptr));
};

