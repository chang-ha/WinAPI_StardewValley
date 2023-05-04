#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class FarmMap : public GameEngineLevel
{
public:
	// constructer destructer
	FarmMap();
	~FarmMap();

	// delete function
	FarmMap(const FarmMap& _Ohter) = delete;
	FarmMap(FarmMap&& _Ohter) noexcept = delete;
	FarmMap& operator=(const FarmMap& _Other) = delete;
	FarmMap& operator=(FarmMap&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
protected:

private:

};

