#pragma once
#include "ContentLevel.h"

class Player;
class PelicanTown : public ContentLevel
{
public:
	// constructer destructer
	PelicanTown();
	~PelicanTown();

	// delete function
	PelicanTown(const PelicanTown& _Ohter) = delete;
	PelicanTown(PelicanTown&& _Ohter) noexcept = delete;
	PelicanTown& operator=(const PelicanTown& _Other) = delete;
	PelicanTown& operator=(PelicanTown&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
};

