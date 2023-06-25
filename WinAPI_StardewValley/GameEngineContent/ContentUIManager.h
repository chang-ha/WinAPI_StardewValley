#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEnginePlatform/GameEngineSound.h>

class ContentUIManager;
class ContentItem;
class GameEngineRenderer;
class ContentLevel;
class ContentInventory;
class MoneyData;

enum MoneyEnum
{
	PlayerMoney,
	ShopPlayerMoney,
	// SleepLevel
	CropsMoney,
	ResourcesMoney,
	FishingMoney,
	MiningMoney,
	EtcMoney,
	TotalMoney
};
class ShopItemData
{
	friend ContentUIManager;
private:
	int ItemBuyPrice = 0;
	GameEngineRenderer* ItemRenderer = nullptr;
	GameEngineRenderer* ItemPriceTextRenderer = nullptr;
	GameEngineRenderer* ItemNameTextRenderer = nullptr;
	GameEngineCollision* ItemCollision = nullptr;
};

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

	void BasicUIOn();
	void BasicUIOff();

	// void ResetCurTextMoney();

	void InventoryUpRender();
	void InventoryDownRender();
	void SleepUIOn();

	void ShopUIOn();
	void ShopUIOff();
	void ShopItemSetting();

	void SellCurItem();
	void ShippingUIOn();
	void ShippingUIOff();

	void SetSellItem(ContentItem* _SellItem)
	{
		SellItem = _SellItem;
	}

	ContentItem* GetSellItem()
	{
		return SellItem;
	}

	void PlusDayValue()
	{
		++DayValue;
		DayChange = true;
	}

protected:

private:
	GameEngineSoundPlayer EffectPlayer;

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
	GameEngineWindowTexture* SleepUITexture = nullptr;
	GameEngineRenderer* SleepUIRenderer = nullptr;
	GameEngineCollision* SleepYesCollision = nullptr;
	GameEngineCollision* SleepNoCollision = nullptr;
	float UIRenderRatio = 0.1f;

	// Pierre's Shop UI
	int ItemSelectIndex = -1;
	GameEngineRenderer* ShopRenderer = nullptr;
	GameEngineRenderer* ItemSelectRenderer = nullptr;
	GameEngineRenderer* CancelRenderer = nullptr;
	GameEngineCollision* CancelCollision = nullptr;
	// GameEngineRenderer* PrevSelectRenderer = nullptr;
	// GameEngineRenderer* NextSelectRenderer = nullptr;
	std::vector<ShopItemData*> ShopItem;

	// ShippingBox UI
	ContentItem* SellItem = nullptr;
	GameEngineRenderer* ShipInventoryRenderer = nullptr;
	GameEngineRenderer* SellItemRenderer = nullptr;
	GameEngineRenderer* SellInventoryRenderer = nullptr;
	GameEngineRenderer* OkButtonRenderer = nullptr;
	GameEngineCollision* SellItemCollision = nullptr;
	GameEngineCollision* OkButtonCollision = nullptr;


	// Debug Value
	GameEngineRenderer* Text1Renderer = nullptr;
	GameEngineRenderer* Text2Renderer = nullptr;
	GameEngineRenderer* Text3Renderer = nullptr;
	GameEngineRenderer* Text4Renderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void SleepUIUpdate(float _Delta);
	void ShopUIUpdate(float _Delta);
	void ShippingUIUpdate(float _Delta);

//////////////// Money Renderer
public:
	class MoneyData
	{
		friend ContentUIManager;
	public:
		MoneyData() {}

		bool MoneyIsUpdate()
		{
			return IsUpdate;
		}

		void SetUpdate(bool _IsUpdate)
		{
			IsUpdate = _IsUpdate;
		}

		void SetCurMoney(int _CurMoney)
		{
			CurMoney = _CurMoney;
		}

		bool IsUpdateEnd() const
		{
			return CurMoney == CurTextMoney;
		}

	private:
		void Init(const float4& _StartRenderRatio, const float _XDistance, const float4& _RenderScale);

		void MoneyRendererOff();

	private:
		bool IsUpdate = false;
		int CurMoney = 0;
		int CurTextMoney = 0;
		std::vector<GameEngineRenderer*> MoneyRenderer;
	};

	MoneyData* GetMoneyData(MoneyEnum _Index)
	{
		return &AllMoney[_Index];
	}

	void SleepMoneyRenderOff();

private:
	void MoneyUIUpdate(MoneyData* _CurMoney, float _Delta);

	// MoneyUI 
	int PlayerMoney = 1000;
	float MoneyUpSpeed = 300.0f;
	std::map<MoneyEnum, MoneyData> AllMoney;
};

