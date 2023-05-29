#define RENDERRATIO 4

#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

class BackGround;
class Player;
class ContentLevel : public GameEngineLevel
{
public:
	// constructer destructer
	ContentLevel();
	~ContentLevel();

	// delete function
	ContentLevel(const ContentLevel& _Ohter) = delete;
	ContentLevel(ContentLevel&& _Ohter) noexcept = delete;
	ContentLevel& operator=(const ContentLevel& _Other) = delete;
	ContentLevel& operator=(ContentLevel&& _Other) noexcept = delete;

	float4 GetRenderScale();

	GameEngineSoundPlayer BGMPlayer;
protected:
	BackGround* Back = nullptr;
	Player* Farmer = nullptr;
private:

};

