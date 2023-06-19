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
	void SleepUIOn();
	void ShopUIOn();
	void ShopUIOff();
	void PlusDayValue()
	{
		++DayValue;
		DayChange = true;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineWindowTexture* SleepUITexture = nullptr;

	// Main UI
	GameEngineRenderer* Clock = nullptr;
	GameEngineRenderer* ClockHand = nullptr;
	GameEngineRenderer* Energy = nullptr;
	// GameEngineRenderer* EnergyBar = nullptr;
	
	// Inventroy UI
	GameEngineRenderer* Inventory = nullptr;

	// Day UI
	GameEngineRenderer* DayTextRenderer = nullptr;
	int DayValue = 1;
	bool DayChange = false;

	// FarmHouse's Sleep UI
	GameEngineRenderer* SleepUIRenderer = nullptr;
	GameEngineCollision* SleepYesCollision = nullptr;
	GameEngineCollision* SleepNoCollision = nullptr;
	float UIRenderRatio = 0.1f;

	// Pierre's Shop UI
	GameEngineRenderer* ShopRenderer = nullptr;
	GameEngineRenderer* ItemSelectRenderer = nullptr;
	GameEngineRenderer* CancelRenderer = nullptr;
	GameEngineCollision* CancelCollision = nullptr;
	GameEngineRenderer* Item1PriceTextRenderer = nullptr;
	GameEngineRenderer* Item2PriceTextRenderer = nullptr;
	GameEngineRenderer* Item3PriceTextRenderer = nullptr;
	GameEngineRenderer* Item4PriceTextRenderer = nullptr;
	GameEngineCollision* Item1Collision = nullptr;
	GameEngineCollision* Item2Collision = nullptr;
	GameEngineCollision* Item3Collision = nullptr;
	GameEngineCollision* Item4Collision = nullptr;
	// GameEngineRenderer* PrevSelectRenderer = nullptr;
	// GameEngineRenderer* NextSelectRenderer = nullptr;

	// Debug Value
	GameEngineRenderer* Text1Renderer = nullptr;
	GameEngineRenderer* Text2Renderer = nullptr;
	GameEngineRenderer* Text3Renderer = nullptr;
	GameEngineRenderer* Text4Renderer = nullptr;

	void SleepUIUpdate(float _Delta);
	void ShopUIUpdate(float _Delta);
};

