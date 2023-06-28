#pragma once
#include "ContentCrops.h"

class Rhubarb : public ContentCrops
{
public:
	// constructer destructer
	Rhubarb();
	~Rhubarb();

	// delete function
	Rhubarb(const Rhubarb& _Ohter) = delete;
	Rhubarb(Rhubarb&& _Ohter) noexcept = delete;
	Rhubarb& operator=(const Rhubarb& _Other) = delete;
	Rhubarb& operator=(Rhubarb&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

