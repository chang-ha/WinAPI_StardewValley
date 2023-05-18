#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Player;
class PelicanTown : public GameEngineLevel
{
	friend Player;
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
	BackGround* Back = nullptr;
	Player* Farmer = nullptr;
	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};

