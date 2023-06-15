#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ContentNpc : public GameEngineActor
{
public:
	// constructer destructer
	ContentNpc();
	~ContentNpc();

	// delete function
	ContentNpc(const ContentNpc& _Ohter) = delete;
	ContentNpc(ContentNpc&& _Ohter) noexcept = delete;
	ContentNpc& operator=(const ContentNpc& _Other) = delete;
	ContentNpc& operator=(ContentNpc&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	GameEngineRenderer* NpcRenderer = nullptr;
	GameEngineCollision* NpcCollision = nullptr;
};

