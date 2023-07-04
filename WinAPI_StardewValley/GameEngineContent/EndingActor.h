#pragma once
#include <GameEngineCore/GameEngineActor.h>

class EndingActor : public GameEngineActor
{
public:
	// constructer destructer
	EndingActor();
	~EndingActor();

	// delete function
	EndingActor(const EndingActor& _Ohter) = delete;
	EndingActor(EndingActor&& _Ohter) noexcept = delete;
	EndingActor& operator=(const EndingActor& _Other) = delete;
	EndingActor& operator=(EndingActor&& _Other) noexcept = delete;

	void Init(const std::string& _ActorName);
	void InitAnimation(const std::string& _ActorName, float _AniSpeed = 0.08f, float _Speed = 85.0f, int _FramCount = 4);
	void InitAnimation(const std::string& _ActorName, const std::string& _TextName, float _AniSpeed = 0.08f, float _Speed = 85.0f);
protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	float Speed = 85.0f;
};

