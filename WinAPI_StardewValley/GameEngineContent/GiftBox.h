#pragma once
#include "ContentActor.h"

class GiftBox : public ContentActor
{
public:
	// constructer destructer
	GiftBox();
	~GiftBox();

	// delete function
	GiftBox(const GiftBox& _Ohter) = delete;
	GiftBox(GiftBox&& _Ohter) noexcept = delete;
	GiftBox& operator=(const GiftBox& _Other) = delete;
	GiftBox& operator=(GiftBox&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineRenderer* Renderer = nullptr;
	GameEngineCollision* Collision = nullptr;
};

