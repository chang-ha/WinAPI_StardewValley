#pragma once
#include <GameEngineBase/GameEngineDebug.h>

#include "ContentActor.h"

enum ItemType
{
	NotItem,
	Axe,
	PickAxe,
	Hoe,
	WateringCan,
	Resources,
	Seed,
};

class GameEngineWindowTexture;
class GameEngineRenderer;
class ContentInventory;
class ContentItem : public ContentActor
{
	friend ContentInventory;
public:
	// constructer destructer
	ContentItem();
	~ContentItem();

	// delete function
	ContentItem(const ContentItem& _Ohter) = delete;
	ContentItem(ContentItem&& _Ohter) noexcept = delete;
	ContentItem& operator=(const ContentItem& _Other) = delete;
	ContentItem& operator=(ContentItem&& _Other) noexcept = delete;

	std::string GetItemName() const
	{
		return ItemName;
	}

	void PlusItemCount(int _ItemCount)
	{
		ItemCount += _ItemCount;
	}

	void MinusItemCount(int _ItemCount)
	{
		if ( 0 >= ItemCount - _ItemCount)
		{
			MsgBoxAssert("아이템 갯수는 0 이하일 수 없습니다.");
		}
		ItemCount -= _ItemCount;
	}

	void SetItemCount(int _ItemCount)
	{
		ItemCount = _ItemCount;
	}

	int GetItemCount()
	{
		return ItemCount;
	}

	ItemType GetItemType()
	{
		return Type;
	}

	void RandomVector();

	void Init(const std::string& _FileName, ItemType _Type);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart() override;
	void LevelEnd() override;

private:
	float MoveTime = 1.0f;
	float4 StartDir= {};

	GameEngineRenderer* Renderer = nullptr;
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineCollision* Collision = nullptr;	
	std::vector<GameEngineCollision*> _CollisionResult;
	std::string ItemName = "";
	int ItemCount = 1;
	ItemType Type = ItemType::NotItem;
};

