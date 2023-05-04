#pragma once
#include <Windows.h>

class GameEngineTime
{
public:
	static GameEngineTime MainTimer;

	// constructer destructer
	GameEngineTime();
	~GameEngineTime();

	// delete function
	GameEngineTime(const GameEngineTime& _Ohter) = delete;
	GameEngineTime(GameEngineTime&& _Ohter) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

	float GetDeltaTime()
	{
		return FloatDelta;
	}

	void Reset();

	void Update();

protected:

private:
	LARGE_INTEGER Count = { 0 };
	LARGE_INTEGER Cur = { 0 };
	LARGE_INTEGER Prev = { 0 };
	float FloatDelta;
	double DoubleDelta;
	__int64 Tick;
};

