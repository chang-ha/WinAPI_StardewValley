#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class ContentUIManager : public GameEngineActor
{
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

	GameEngineRenderer* Clock = nullptr;
	GameEngineRenderer* ClockHand = nullptr;
	GameEngineRenderer* EnergyBar = nullptr;
	GameEngineRenderer* ContentMouse = nullptr;
protected:
	void Start() override;

private:
};

