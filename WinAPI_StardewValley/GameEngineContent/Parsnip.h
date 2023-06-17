#pragma once
#include "ContentCrops.h"

class Parsnip : public ContentCrops
{
public:
	// constructer destructer
	Parsnip();
	~Parsnip();

	// delete function
	Parsnip(const Parsnip& _Ohter) = delete;
	Parsnip(Parsnip&& _Ohter) noexcept = delete;
	Parsnip& operator=(const Parsnip& _Other) = delete;
	Parsnip& operator=(Parsnip&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};

