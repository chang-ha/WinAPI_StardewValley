#pragma once
#include "ContentCrops.h"

class Potato : public ContentCrops
{
public:
	// constructer destructer
	Potato();
	~Potato();

	// delete function
	Potato(const Potato& _Ohter) = delete;
	Potato(Potato&& _Ohter) noexcept = delete;
	Potato& operator=(const Potato& _Other) = delete;
	Potato& operator=(Potato&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

