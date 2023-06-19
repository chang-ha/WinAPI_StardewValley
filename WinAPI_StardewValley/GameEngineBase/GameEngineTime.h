#pragma once
#include <Windows.h>
#include <map>

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

	template<typename EnumType>
	float GetTimeScale(EnumType _Order)
	{
		return GetTimeScale(static_cast<int>(_Order));
	}

	float GetTimeScale(int _Order)
	{
		if (TimeScale.end() == TimeScale.find(_Order))
		{
			TimeScale[_Order] = 1.0f;
		}

		return TimeScale[_Order];
	}

	template<typename EnumType>
	void SetTimeScale(EnumType _Order, float _TimeScale)
	{
		SetTimeScale(static_cast<int>(_Order), _TimeScale);
	}

	void SetTimeScale(int _Order, float _TimeScale)
	{
		TimeScale[_Order] = _TimeScale;
	}

	void SetAllTimeScale(float _TimeScale)
	{
		for (std::pair<const int, float>& Order : TimeScale)
		{
			Order.second = _TimeScale;
		}
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

	// int == ObjrctOrder
	std::map<int, float> TimeScale;
};

