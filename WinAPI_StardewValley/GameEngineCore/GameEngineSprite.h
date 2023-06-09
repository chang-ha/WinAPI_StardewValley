#pragma once
#include <vector>

#include <GameEnginePlatform/GameEngineWindowTexture.h>

class GameEngineSprite
{
public:
	class Sprite
	{
	public:
		GameEngineWindowTexture* BaseTexture = nullptr;
		GameEngineWindowTexture* MaskTexture = nullptr;
		float4 RenderPos = float4::ZERO;
		float4 RenderScale = float4::ZERO;
	};

public:
	// constructer destructer
	GameEngineSprite();
	~GameEngineSprite();

	// delete function
	GameEngineSprite(const GameEngineSprite& _Ohter) = delete;
	GameEngineSprite(GameEngineSprite&& _Ohter) noexcept = delete;
	GameEngineSprite& operator=(const GameEngineSprite& _Other) = delete;
	GameEngineSprite& operator=(GameEngineSprite&& _Other) noexcept = delete;

	void CreateSpriteSheet(GameEngineWindowTexture* _Texture, int _XCount, int _YCount);

	void CreateSpriteFolder(const std::string& _Path);

	const Sprite& GetSprite(size_t _Index);

	size_t GetSpriteCount()
	{
		return AllSprite.size();
	}

	void SetMaskTexture(const std::string& _MaskName);

protected:
	
private:
	std::vector<Sprite> AllSprite;
};

