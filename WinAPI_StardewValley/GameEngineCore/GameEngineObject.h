#pragma once

class GameEngineLevel;
class GameEngineCore;
class GameEngineObject
{
	friend GameEngineLevel;
	friend GameEngineCore;
public:
	// constructer destructer
	GameEngineObject();
	virtual ~GameEngineObject();

	// delete function
	GameEngineObject(const GameEngineObject& _Ohter) = delete;
	GameEngineObject(GameEngineObject&& _Ohter) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	virtual void Start() {}
	virtual void Update(float _Delta) {}
	virtual void Render(float _Delta) {}
	virtual void Release() {}

	virtual void On()
	{
		IsUpdateValue = true;
	}

	virtual void Off()
	{
		IsUpdateValue = false;
	}

	void Death()
	{
		IsDeathValue = true;
	}

	bool IsUpdate()
	{
		return true == IsUpdateValue && false == IsDeathValue;
	}

	virtual bool IsDeath()
	{
		return IsDeathValue;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	int GetOrder()
	{
		return Order;
	}

	float GetLiveTime()
	{
		return LiveTime;
	}

	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}
protected:

private:
	int Order = 0;
	bool IsUpdateValue = true; 
	bool IsDeathValue = false; 
	float LiveTime = 0.0f;
	void AddLiveTime(float _DeltaTime)
	{
		LiveTime += _DeltaTime;
	}
};

