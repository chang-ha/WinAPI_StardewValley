#pragma once
#include "ContentLevel.h"

class GeneralStore : public ContentLevel
{
public:
	// constructer destructer
	GeneralStore();
	~GeneralStore();

	// delete function
	GeneralStore(const GeneralStore& _Ohter) = delete;
	GeneralStore(GeneralStore&& _Ohter) noexcept = delete;
	GeneralStore& operator=(const GeneralStore& _Other) = delete;
	GeneralStore& operator=(GeneralStore&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel);
	void LevelEnd(GameEngineLevel* _NextLevel);
	void Start();
	void Update(float _Delta);

private:
	
};

