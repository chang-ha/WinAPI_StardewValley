#pragma once
// #include <string>
#include <GameEngineCore/GameEngineActor.h>

class BackGround : public GameEngineActor
{
public:
	// constructer destructer
	BackGround();
	~BackGround();

	// delete function
	BackGround(const BackGround& _Ohter) = delete;
	BackGround(BackGround&& _Ohter) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	void Init(const std::string& _FileName);
protected:

private:
	// std::string FileName = "";

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};

