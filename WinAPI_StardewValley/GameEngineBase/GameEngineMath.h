#pragma once

class GameEngineMath
{
};

class float4
{
public:
	float X;
	float Y;
	float Z;
	float W;

	inline int iX() const
	{
		return static_cast<int>(X);
	}
	inline int iY() const
	{
		return static_cast<int>(Y);
	}
	
	inline int ihX() const
	{
		return static_cast<int>(0.5f * X);
	}

	inline int ihY() const
	{
		return static_cast<int>(0.5f * Y);
	}

	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;
		return *this;
	}

protected:

private:

};

