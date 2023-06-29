#pragma once
#include "ContentCrops.h"

class Kale : public ContentCrops
{
public:
	// constructer destructer
	Kale();
	~Kale();

	// delete function
	Kale(const Kale& _Ohter) = delete;
	Kale(Kale&& _Ohter) noexcept = delete;
	Kale& operator=(const Kale& _Other) = delete;
	Kale& operator=(Kale&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	bool Harvest() override;

private:

};

