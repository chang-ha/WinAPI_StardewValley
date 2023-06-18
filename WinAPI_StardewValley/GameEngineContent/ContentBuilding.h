#pragma once
#include "ContentActor.h"

class ContentBuilding : public ContentActor
{
public:
	// constructer destructer
	ContentBuilding();
	~ContentBuilding();

	// delete function
	ContentBuilding(const ContentBuilding& _Ohter) = delete;
	ContentBuilding(ContentBuilding&& _Ohter) noexcept = delete;
	ContentBuilding& operator=(const ContentBuilding& _Other) = delete;
	ContentBuilding& operator=(ContentBuilding&& _Other) noexcept = delete;

	void Init(const std::string& _FileName);

protected:
	void Update(float _Delta) override;

private:
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineRenderer* Renderer = nullptr;

};

