#pragma once
#include "ContentActor.h"

enum class ItemType
{
	Null,
	Tool,
	Resources,
};

class GameEngineRenderer;
class ContentItem : public ContentActor
{
public:
	// constructer destructer
	ContentItem();
	~ContentItem();

	// delete function
	ContentItem(const ContentItem& _Ohter) = delete;
	ContentItem(ContentItem&& _Ohter) noexcept = delete;
	ContentItem& operator=(const ContentItem& _Other) = delete;
	ContentItem& operator=(ContentItem&& _Other) noexcept = delete;

	void Init(const std::string& _FileName, ItemType _Type);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart() override;
	void LevelEnd() override;

private:
	GameEngineRenderer* Renderer = nullptr;
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineCollision* Collision = nullptr;
	std::vector<GameEngineCollision*> _CollisionResult;
	ItemType Type = ItemType::Null;
};

