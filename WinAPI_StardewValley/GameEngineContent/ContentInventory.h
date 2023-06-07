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

	bool IsFull()
	{
		return Full;
	}

	void PushItem(ContentItem* _Item);

	ContentItem* FindItem(const ContentItem* _Item, int _ResultIndex);

	int BlankSpace();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineRenderer* InventoryRenderer = nullptr;
	GameEngineRenderer* NameText = nullptr;
	bool Full = false;

	std::vector<ContentItem*> AllItem;
	std::vector<GameEngineRenderer*> ItemRenderer;

	// std::vector<GameEngineRenderer*> ItemCountRenderer;
};

