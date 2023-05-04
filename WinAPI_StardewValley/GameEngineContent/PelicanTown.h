#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class PelicanTown : public GameEngineLevel
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

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
protected:

private:

};

