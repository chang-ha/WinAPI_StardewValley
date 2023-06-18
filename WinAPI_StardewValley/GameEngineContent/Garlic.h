#pragma once
#include "ContentCrops.h"

class Garlic : public ContentCrops
{
public:
	// constructer destructer
	Garlic();
	~Garlic();

	// delete function
	Garlic(const Garlic& _Ohter) = delete;
	Garlic(Garlic&& _Ohter) noexcept = delete;
	Garlic& operator=(const Garlic& _Other) = delete;
	Garlic& operator=(Garlic&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

