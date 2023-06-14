#pragma once
#include "ContentActor.h"

class ContentCrops : public ContentActor
{
public:
	// constructer destructer
	ContentCrops();
	~ContentCrops();

	// delete function
	ContentCrops(const ContentCrops& _Ohter) = delete;
	ContentCrops(ContentCrops&& _Ohter) noexcept = delete;
	ContentCrops& operator=(const ContentCrops& _Other) = delete;
	ContentCrops& operator=(ContentCrops&& _Other) noexcept = delete;

	void Harvest();

protected:

	void Start() override;
	void Update(float _Delta) override;
	void Grow();
	bool IsGrownUp();

	GameEngineRenderer* CropsRenderer = nullptr;
	GameEngineCollision* CropsCollision = nullptr;
	int GrowStep = 0;
	int MaxGrowStep = 5;
private:

};

