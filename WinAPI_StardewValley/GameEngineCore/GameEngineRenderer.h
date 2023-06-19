#pragma once
#include <string>
#include <map>
#include <vector>

#include <GameEngineBase/GameEngineMath.h>

#include "GameEngineActorSubObject.h"

enum class CameraType
{
	MAIN,
	UI,
};

class GameEngineWindowTexture;
class GameEngineActor;
class GameEngineCamera;
class GameEngineSprite;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineCamera;
	friend GameEngineActor;
public:
	// constructer destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete function
	GameEngineRenderer(const GameEngineRenderer& _Ohter) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Ohter) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void SetTexture(const std::string& _Name);

	void SetSprite(const std::string& _Name, size_t _Index = 0);

	void SetAngle(float _Angle);

	void SetRenderPos(const float4& _Pos)
	{
		RenderPos = _Pos;
	}

	void SetRenderScale(const float4& _Scale)
	{
		RenderScale = _Scale;
		ScaleCheck = true;
	}

	void SetCopyPos(const float4& _Pos)
	{
		CopyPos = _Pos;
	}

	void SetCopyScale(const float4& _Scale)
	{
		CopyScale = _Scale;
	}

	void SetScaleRatio(const float _Ratio)
	{
		ScaleRatio = _Ratio;
	}

	CameraType GetCameraType()
	{
		return CameraTypeValue;
	}

	void SetRenderScaleToTexture();

	void SetOrder(int _Order) override;

protected:
	void Start() override;

private:
	GameEngineCamera* Camera = nullptr;
	CameraType CameraTypeValue = CameraType::MAIN;
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineWindowTexture* MaskTexture = nullptr;
	GameEngineSprite* Sprite = nullptr;
	bool ScaleCheck = false;
	float ScaleRatio = 1.0f;
	std::string Text = "";
	float Angle = 0.0f;

	void TextRender(float _Delta);
	float4 RenderPos = {};
	float4 RenderScale = {};

	float4 CopyPos = {};
	float4 CopyScale = {};
	void Render(float _Delta);

/////////// Animation
private:
	class Animation
	{
	public:
		std::string Name = "";
		GameEngineSprite* Sprite = nullptr;
		size_t CurFrame = 0;
		size_t StartFrame = -1;
		size_t EndFrame = -1;
		float CurInter = 0.0f;
		std::vector<size_t> Frames;
		std::vector<float> Inters;
		bool Loop = true;
		bool IsEnd = false;
	};

public:
	std::map<std::string, Animation> AllAnimation;
	Animation* CurAnimation = nullptr;

	Animation* FindAnimation(const std::string& _AnimationName);

	void CreateAnimation(
		const std::string& _AnimationName,
		const std::string& _SpriteName,
		size_t _Start = -1, size_t _End = -1,
		float _Inter = 0.1f,
		bool _Loop = true);

	void CreateAnimationToFrame(
		const std::string& _AnimationName,
		const std::string& _SpriteName,
		const std::vector<size_t>& _Frame,
		float _Inter = 0.1f,
		bool _Loop = true);

	size_t GetCurFrame()
	{
		return CurAnimation->CurFrame;
	}

	bool IsAnimationEnd()
	{
		return CurAnimation->IsEnd;
	}

	bool IsAnimation(const std::string& _Name)
	{
		return CurAnimation->Name == _Name;
	}

	void ChangeAnimation(const std::string& _AnimationName, int _StartFrame = 0, bool _ForceChange = false);
	void MainCameraSetting();
	void UICameraSetting();
	void Update(float _Delta) override;

/////////// TextRender
	public:
		void SetText(const std::string& _Text, int _TextScale = 20, const std::string& _Face = "±¼¸²")
		{
			Text = _Text;
			TextScale = _TextScale;
			Face = _Face;
		}

private:
	std::string Face = "";
	int TextScale = 0;
};

