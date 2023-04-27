#pragma once
#include "GameEngineCore.h"

class GameEngineObject : public GameEngineCore
{
public:
	// constructer destructer
	GameEngineObject();
	~GameEngineObject();

	// delete function
	GameEngineObject(const GameEngineObject& _Ohter) = delete;
	GameEngineObject(GameEngineObject&& _Ohter) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	// �����Ѵ�.
	virtual void Start() {}

	// �ൿ�Ѵ�.
	virtual void Update() {}

	// �׷�����
	virtual void Render() {}

	// �����ȴ�
	virtual void Release() {}

	void On()
	{
		IsUpdateValue = true;
	}

	void Off()
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

	bool IsDeath()
	{
		return IsDeathValue;
	}

protected:

private:
	bool IsUpdateValue = true; 
	bool IsDeathValue = false; 
};

