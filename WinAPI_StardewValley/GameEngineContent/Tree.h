#pragma once
#include "ContentResources.h"

class Tree : public ContentResources
{
public:
	// constructer destructer
	Tree();
	~Tree();

	// delete function
	Tree(const Tree& _Ohter) = delete;
	Tree(Tree&& _Ohter) noexcept = delete;
	Tree& operator=(const Tree& _Other) = delete;
	Tree& operator=(Tree&& _Other) noexcept = delete;

	void Init(const std::string& _FileName) override;


	void SetIsHitten(bool _IsHitten)
	{
		IsHitten = _IsHitten;
	}

	int GetHp()
	{
		return Hp;
	}

	void PlusHp(int _Value)
	{
		Hp += _Value;
	}

	void SetIsFall(bool _IsFall)
	{
		IsFall = _IsFall;
	}
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Hitten(float _Delta);
	void FallDown(float _Delta);

private:
	bool IsHitten = false;
	bool IsFall = false;
	bool firstFall = false;
	int ItemCount = 6;
	int Hp = 9;
	int HittenStep = 0;
	float AngleValue = 0.0f;
	float CurAngle = 0.0f;
	float AngleSpeed = 0.0f;
	float ItemPos = 0.0f;

	GameEngineRenderer* UpperPart = nullptr;
	GameEngineRenderer* UpperPartShadow = nullptr;
};

