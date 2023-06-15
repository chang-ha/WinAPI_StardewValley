#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class ContentLevel;
class ContentInventory;
class ContentUIManager : public GameEngineActor
{
	friend ContentLevel;
	friend ContentInventory;
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

	void InventoryUpRender();
	void InventoryDownRender();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	// Main UI
	GameEngineRenderer* Clock = nullptr;
	GameEngineRenderer* ClockHand = nullptr;
	GameEngineRenderer* Energy = nullptr;
	// GameEngineRenderer* EnergyBar = nullptr;
	// Inventroy UI
	GameEngineRenderer* Inventory = nullptr;
	// Day UI
	GameEngineRenderer* DayRenderer = nullptr;
	int DayValue = 1;
	// FarmHouse's Sleep UI
	GameEngineRenderer* SleepUIRenderer = nullptr;
	GameEngineCollision* SleepYesCollision = nullptr;
	GameEngineCollision* SleepNoCollision = nullptr;


	// Debug Value
	GameEngineRenderer* Text1Renderer = nullptr;
	GameEngineRenderer* Text2Renderer = nullptr;
	GameEngineRenderer* Text3Renderer = nullptr;
	GameEngineRenderer* Text4Renderer = nullptr;
};

