#pragma once
#include <string>

#include <GameEngineCore/GameEngineActor.h>

#include "GlobalValue.h"

class GameEngineWindowTexture;
class ContentLevel;
class ContentItem;
class ContentMouse : public GameEngineActor
{
	friend ContentLevel;
public:
	static ContentMouse* MainMouse;
	// constructer destructer
	ContentMouse();
	~ContentMouse();

	// delete function
	ContentMouse(const ContentMouse& _Ohter) = delete;
	ContentMouse(ContentMouse&& _Ohter) noexcept = delete;
	ContentMouse& operator=(const ContentMouse& _Other) = delete;
	ContentMouse& operator=(ContentMouse&& _Other) noexcept = delete;

	void Start();

	void Update(float _Delta) override;

	float4 GetMousePos();

	GameEngineRenderer* GetMouseRenderer()
	{
		return MouseRenderer;
	}

	GameEngineCollision* GetMouseCollision()
	{
		return MouseCollision;
	}

	GameEngineRenderer* GetItemRenderer()
	{
		return ItemRenderer;
	}
	
	void SetItemRenderer(GameEngineRenderer* _ItemRenderer)
	{
		ItemRenderer = _ItemRenderer;
	}

	GameEngineRenderer* GetItemCountRenderer()
	{
		return ItemCountRenderer;
	}

	void SetItemCountRenderer(int _ItemCountRenderer);

	ContentItem* GetPickItem()
	{
		return PickItem;
	}

	void SetPickItem(ContentItem* _PickItem)
	{
		PickItem = _PickItem;
	}

	void SetItemPrice(int _ItemPrice);

	void ItemPriceOn();

	void ItemPriceOff();
protected:

private:
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineRenderer* MouseRenderer = nullptr;
	GameEngineCollision* MouseCollision = nullptr;

	GameEngineRenderer* ItemRenderer = nullptr;
	GameEngineRenderer* ItemCountRenderer = nullptr;
	ContentItem* PickItem = nullptr;

	GameEngineRenderer* ItemPriceRenderer = nullptr;
	GameEngineRenderer* ItemPriceTextRenderer = nullptr;
};

