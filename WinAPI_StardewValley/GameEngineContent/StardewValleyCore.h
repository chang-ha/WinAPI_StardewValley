#pragma once
#include <GameEngineCore/GameEngineCore.h>

class StardewValleyCore : public CoreProcess
{
public:
	// constructer destructer
	StardewValleyCore();
	~StardewValleyCore();

	// delete function
	StardewValleyCore(const StardewValleyCore& _Ohter) = delete;
	StardewValleyCore(StardewValleyCore&& _Ohter) noexcept = delete;
	StardewValleyCore& operator=(const StardewValleyCore& _Other) = delete;
	StardewValleyCore& operator=(StardewValleyCore&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

