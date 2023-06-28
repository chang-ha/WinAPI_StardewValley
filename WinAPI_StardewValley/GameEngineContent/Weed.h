#pragma once
#include "ContentResources.h"

class Weed : public ContentResources
{
public:
	// constructer destructer
	Weed();
	~Weed();

	// delete function
	Weed(const Weed& _Ohter) = delete;
	Weed(Weed&& _Ohter) noexcept = delete;
	Weed& operator=(const Weed& _Other) = delete;
	Weed& operator=(Weed&& _Other) noexcept = delete;

	void WeedDeath()
	{
		DeathValue = true;
	}
protected:
	void Start() override;
	void Update(float _Delta) override;

	void DeathAnimationUpdate();
private:
	bool DeathValue = false;
	int ItemCount = 1;

};

