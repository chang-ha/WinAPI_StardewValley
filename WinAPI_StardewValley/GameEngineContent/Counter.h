#pragma once
#include "ContentActor.h"

class Counter : public ContentActor
{
public:
	// constructer destructer
	Counter();
	~Counter();

	// delete function
	Counter(const Counter& _Ohter) = delete;
	Counter(Counter&& _Ohter) noexcept = delete;
	Counter& operator=(const Counter& _Other) = delete;
	Counter& operator=(Counter&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	GameEngineRenderer* Renderer = nullptr;
	GameEngineCollision* Collision = nullptr;
};

