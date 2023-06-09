#pragma once
#include "ContentResources.h"

class Rock : public ContentResources
{
public:
	// constructer destructer
	Rock();
	~Rock();

	// delete function
	Rock(const Rock& _Ohter) = delete;
	Rock(Rock&& _Ohter) noexcept = delete;
	Rock& operator=(const Rock& _Other) = delete;
	Rock& operator=(Rock&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	int ItemCount = 1;
};

