#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ContentInventory : public GameEngineActor
{
public:
	// constructer destructer
	ContentInventory();
	~ContentInventory();

	// delete function
	ContentInventory(const ContentInventory& _Ohter) = delete;
	ContentInventory(ContentInventory&& _Ohter) noexcept = delete;
	ContentInventory& operator=(const ContentInventory& _Other) = delete;
	ContentInventory& operator=(ContentInventory&& _Other) noexcept = delete;

protected:

private:

};

