#pragma once
#include <GameEngineCore/GameEngineLevel.h>
class FarmHouse : public GameEngineLevel
{
public:
	// constructer destructer
	FarmHouse();
	~FarmHouse();

	// delete function
	FarmHouse(const FarmHouse& _Ohter) = delete;
	FarmHouse(FarmHouse&& _Ohter) noexcept = delete;
	FarmHouse& operator=(const FarmHouse& _Other) = delete;
	FarmHouse& operator=(FarmHouse&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};

