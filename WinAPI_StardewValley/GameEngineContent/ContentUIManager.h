#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class ContentLevel;
class ContentUIManager : public GameEngineActor
{
	friend ContentLevel;
public:
	static ContentUIManager* MainUI;

	// constructer destructer
	ContentUIManager();
	~ContentUIManager();

	// delete function
	ContentUIManager(const ContentUIManager& _Ohter) = delete;
	ContentUIManager(ContentUIManager&& _Ohter) noexcept = delete;
	ContentUIManager& operator=(const ContentUIManager& _Other) = delete;
	ContentUIManager& operator=(ContentUIManager&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	GameEngineRenderer* Clock = nullptr;
	GameEngineRenderer* ClockHand = nullptr;
	GameEngineRenderer* Energy = nullptr;
	GameEngineRenderer* ContentMouse = nullptr;
	// GameEngineRenderer* EnergyBar = nullptr;
};

