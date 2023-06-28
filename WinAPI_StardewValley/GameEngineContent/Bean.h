#pragma once
#include "ContentCrops.h"

class Bean : public ContentCrops
{
public:
	// constructer destructer
	Bean();
	~Bean();

	// delete function
	Bean(const Bean& _Ohter) = delete;
	Bean(Bean&& _Ohter) noexcept = delete;
	Bean& operator=(const Bean& _Other) = delete;
	Bean& operator=(Bean&& _Other) noexcept = delete;

	bool Harvest() override;
	void Grow() override;
protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};

