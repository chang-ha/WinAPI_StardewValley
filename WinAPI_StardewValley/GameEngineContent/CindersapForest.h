#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class CindersapForest : public GameEngineLevel
{
public:
	// constructer destructer
	CindersapForest();
	~CindersapForest();

	// delete function
	CindersapForest(const CindersapForest& _Ohter) = delete;
	CindersapForest(CindersapForest&& _Ohter) noexcept = delete;
	CindersapForest& operator=(const CindersapForest& _Other) = delete;
	CindersapForest& operator=(CindersapForest&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;
	void Release() override;

protected:

private:

};

