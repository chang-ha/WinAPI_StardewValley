#pragma once
#include <vector>

#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class ContentItem;
class InventoryItemData
{
public:
	ContentItem* Item = nullptr;
	GameEngineRenderer* ItemRenderer = nullptr;
	GameEngineCollision* ItemCollision = nullptr;
	GameEngineRenderer* ItemCountRenderer = nullptr;
};

class ContentInventory : public GameEngineActor
{
public:
	static ContentInventory* MainInventory;

	// constructer destructer
	ContentInventory();
	~ContentInventory() override;

	// delete function
	ContentInventory(const ContentInventory& _Ohter) = delete;
	ContentInventory(ContentInventory&& _Ohter) noexcept = delete;
	ContentInventory& operator=(const ContentInventory& _Other) = delete;
	ContentInventory& operator=(ContentInventory&& _Other) noexcept = delete;

	bool IsFull(const ContentItem* _Item);

	void PushItem(ContentItem* _Item);

	void PopItem(int _Index);

	ContentItem* FindItem(const ContentItem* _Item, int* _ResultIndex = nullptr);

	int BlankSpace();

	void SetPosInventoryItem();

	void UseItem(ContentItem* _Item);

	ContentItem* GetCurItem()
	{
		return AllItem[CurIndex]->Item;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineSoundPlayer EffectPlayer;
	int CurIndex = 0;
	float PosSettingValue = 0.0f;

	GameEngineRenderer* InventoryRenderer = nullptr;
	GameEngineRenderer* NameText = nullptr;
	GameEngineRenderer* CurIndexRenderer = nullptr;

	std::vector<InventoryItemData*> AllItem;
};

