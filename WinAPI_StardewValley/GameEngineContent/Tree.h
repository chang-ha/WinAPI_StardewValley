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

	void Hitten(float _Delta);

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
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	int ItemCount = 6;
	int Hp = 3;
	bool IsHitten = false;
	int HittenStep = 0;
	GameEngineRenderer* UpperPart = nullptr;
	GameEngineRenderer* UpperPartShadow = nullptr;
};

