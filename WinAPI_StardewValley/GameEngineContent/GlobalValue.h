#pragma once
#include <GameEnginePlatform/GameEngineWindow.h>

#define RENDERRATIO 3.0f
#define TILESIZE float4{16, 16}

class GlobalValue
{
public:
	// constructer destructer
	GlobalValue();
	~GlobalValue();

	// delete function
	GlobalValue(const GlobalValue& _Ohter) = delete;
	GlobalValue(GlobalValue&& _Ohter) noexcept = delete;
	GlobalValue& operator=(const GlobalValue& _Other) = delete;
	GlobalValue& operator=(GlobalValue&& _Other) noexcept = delete;

	static void Init();

	static float4 WinScale;
protected:

private:

};

