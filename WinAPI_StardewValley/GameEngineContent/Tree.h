#pragma once
#include "ContentActor.h"

class Tree : public ContentActor
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

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

};

