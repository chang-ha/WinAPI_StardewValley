#pragma once
#include "ContentItem.h"

enum SeedType
{
	NotSeed,
	Cauliflower,
	Garlic,
	Parsnip
};

class ContentSeed : public ContentItem
{
public:
	// constructer destructer
	ContentSeed();
	~ContentSeed();

	// delete function
	ContentSeed(const ContentSeed& _Ohter) = delete;
	ContentSeed(ContentSeed&& _Ohter) noexcept = delete;
	ContentSeed& operator=(const ContentSeed& _Other) = delete;
	ContentSeed& operator=(ContentSeed&& _Other) noexcept = delete;

protected:
	void Init(const std::string& _FileName);

	SeedType ThisType = NotSeed;
private:

};

