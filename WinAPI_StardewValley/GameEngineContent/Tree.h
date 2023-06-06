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

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	int ItemCount = 6;
	GameEngineRenderer* UpperPart = nullptr;
	std::vector<GameEngineCollision*> _CollisionResult;
};

