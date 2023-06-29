#pragma once
#include "ContentCrops.h"

class WildCrops : public ContentCrops
{
public:
	// constructer destructer
	WildCrops();
	~WildCrops();

	// delete function
	WildCrops(const WildCrops& _Ohter) = delete;
	WildCrops(WildCrops&& _Ohter) noexcept = delete;
	WildCrops& operator=(const WildCrops& _Other) = delete;
	WildCrops& operator=(WildCrops&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

