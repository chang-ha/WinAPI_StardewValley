#pragma once
#include "ContentCrops.h"

class Cauliflower : public ContentCrops
{
public:
	// constructer destructer
	Cauliflower();
	~Cauliflower();

	// delete function
	Cauliflower(const Cauliflower& _Ohter) = delete;
	Cauliflower(Cauliflower&& _Ohter) noexcept = delete;
	Cauliflower& operator=(const Cauliflower& _Other) = delete;
	Cauliflower& operator=(Cauliflower&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

