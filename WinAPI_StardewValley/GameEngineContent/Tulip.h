#pragma once
#include "ContentCrops.h"

class Tulip : public ContentCrops
{
public:
	// constructer destructer
	Tulip();
	~Tulip();

	// delete function
	Tulip(const Tulip& _Ohter) = delete;
	Tulip(Tulip&& _Ohter) noexcept = delete;
	Tulip& operator=(const Tulip& _Other) = delete;
	Tulip& operator=(Tulip&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

