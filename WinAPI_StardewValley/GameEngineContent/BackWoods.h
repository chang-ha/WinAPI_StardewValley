#pragma once
#include <GameEngineCore/GameEngineLevel.h>
class BackWoods : public GameEngineLevel
{
public:
	// constructer destructer
	BackWoods();
	~BackWoods();

	// delete function
	BackWoods(const BackWoods& _Ohter) = delete;
	BackWoods(BackWoods&& _Ohter) noexcept = delete;
	BackWoods& operator=(const BackWoods& _Other) = delete;
	BackWoods& operator=(BackWoods&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
protected:

private:

};

