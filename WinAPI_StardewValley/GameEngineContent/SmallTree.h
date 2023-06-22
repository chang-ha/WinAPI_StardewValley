#pragma once
#include "ContentResources.h"

class SmallTree : public ContentResources
{
public:
	// constructer destructer
	SmallTree();
	~SmallTree();

	// delete function
	SmallTree(const SmallTree& _Ohter) = delete;
	SmallTree(SmallTree&& _Ohter) noexcept = delete;
	SmallTree& operator=(const SmallTree& _Other) = delete;
	SmallTree& operator=(SmallTree&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	int ItemCount = 1;
};

