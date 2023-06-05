#pragma once
#include <vector>

#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
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

	GameEngineRenderer* GetRenderer()
	{
		return InventoryRenderer;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineRenderer* InventoryRenderer = nullptr;
	GameEngineRenderer* UIRenderer = nullptr;
	GameEngineRenderer* Name = nullptr;

	std::vector<GameEngineActor*> AllItem;
};

