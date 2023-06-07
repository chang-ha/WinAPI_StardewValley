#pragma once
#include <vector>

#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class ContentItem;
class ContentInventory : public GameEngineActor
{
public:
	static ContentInventory* MainInventory;

	// constructer destructer
	ContentInventory();
	~ContentInventory();

	// delete function
	ContentInventory(const ContentInventory& _Ohter) = delete;
	ContentInventory(ContentInventory&& _Ohter) noexcept = delete;
	ContentInventory& operator=(const ContentInventory& _Other) = delete;
	ContentInventory& operator=(ContentInventory&& _Other) noexcept = delete;

	bool IsFull(const ContentItem* _Item);

	void PushItem(ContentItem* _Item);

	ContentItem* FindItem(const ContentItem* _Item, int _ResultIndex);

	int BlankSpace();

	void SetPosInventoryItem();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* InventoryRenderer = nullptr;
	GameEngineRenderer* NameText = nullptr;
	GameEngineRenderer* CurIndexRenderer = nullptr;
	int CurIndex = 0;
	float PosSettingValue = 0.0f;

	std::vector<ContentItem*> AllItem;
	std::vector<GameEngineRenderer*> ItemRenderer;
	std::vector<GameEngineCollision*> ItemCollision;
	std::vector<GameEngineRenderer*> ItemCountRenderer;
};

