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

	void InventoryUpRender();
	void InventoryDownRender();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* Clock = nullptr;
	GameEngineRenderer* ClockHand = nullptr;
	GameEngineRenderer* Energy = nullptr;
	// GameEngineRenderer* EnergyBar = nullptr;
	GameEngineRenderer* Inventory = nullptr;
};

