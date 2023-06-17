#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>

#include "ResourcesManager.h"
#include "GameEngineSprite.h"

GameEngineSprite::GameEngineSprite()
{

}

GameEngineSprite::~GameEngineSprite()
{

}

void GameEngineSprite::CreateSpriteSheet(GameEngineWindowTexture* _Texture, int _XCount, int _YCount)
{
	float4 SpriteScale = _Texture->GetScale();
	AllSprite.resize(_XCount * _YCount);

	float4 StartPos = float4::ZERO;
	float4 ImageSize = { SpriteScale.X / _XCount, SpriteScale.Y / _YCount };

	for (size_t y = 0; y < _YCount; y++)
	{
		for (size_t x = 0; x < _XCount; x++)
		{
			size_t Index = (y * _XCount) + x;

			AllSprite[Index].BaseTexture = _Texture;

			AllSprite[Index].RenderPos.X = StartPos.X;
			AllSprite[Index].RenderPos.Y = StartPos.Y;
			// AllSprite[Index].RenderPos = StartPos;

			AllSprite[Index].RenderScale.X = ImageSize.X;
			AllSprite[Index].RenderScale.Y = ImageSize.Y;
			// AllSprite[Index].RenderScale = ImageSize;

			StartPos.X += ImageSize.X;
		}
		StartPos.X = 0;
		StartPos.Y += ImageSize.Y;
	}
}

void GameEngineSprite::CreateSpriteFolder(const std::string& _Path)
{
	GameEngineDirectory Dir = _Path;
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	AllSprite.resize(Files.size());
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().TextureLoad(Files[i].GetStringPath());
		AllSprite[i].BaseTexture = Texture;
		AllSprite[i].RenderPos = float4::ZERO;
		AllSprite[i].RenderScale = Texture->GetScale();
	}
}


const GameEngineSprite::Sprite& GameEngineSprite::GetSprite(size_t _Index)
{
	static GameEngineSprite::Sprite ReturnValue;
	if (0 > _Index)
	{
		MsgBoxAssert(_Index + "는 0보다 작은 인덱스값입니다.");
		return ReturnValue;
	}

	if (AllSprite.size() <= _Index)
	{
		MsgBoxAssert(_Index + "는 스프라이트의 범위를 초과했습니다.");
		return ReturnValue;
	}
	return AllSprite[_Index];
}

void GameEngineSprite::SetMaskTexture(const std::string& _MaskName)
{
	GameEngineWindowTexture* MaskTexture = ResourcesManager::GetInst().FindTexture(_MaskName);

	if (nullptr == MaskTexture)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 마스크로 사용하려고 했습니다.");
	}

	for (size_t i = 0; i < AllSprite.size(); i++)
	{
		AllSprite[i].MaskTexture = MaskTexture;
	}
}