#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class PlayOver : public GameEngineActor
{
public:
	// constructer destructer
	PlayOver();
	~PlayOver();

	// delete function
	PlayOver(const PlayOver& _Ohter) = delete;
	PlayOver(PlayOver&& _Ohter) noexcept = delete;
	PlayOver& operator=(const PlayOver& _Other) = delete;
	PlayOver& operator=(PlayOver&& _Other) noexcept = delete;

	GameEngineRenderer* Renderer;
	void Init(const std::string& _FileName);
protected:

private:
	std::string FileName;
	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
};

