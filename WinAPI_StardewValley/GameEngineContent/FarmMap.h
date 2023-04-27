#pragma once

class FarmMap
{
public:
	// constructer destructer
	FarmMap();
	~FarmMap();

	// delete function
	FarmMap(const FarmMap& _Ohter) = delete;
	FarmMap(FarmMap&& _Ohter) noexcept = delete;
	FarmMap& operator=(const FarmMap& _Other) = delete;
	FarmMap& operator=(FarmMap&& _Other) noexcept = delete;

protected:

private:

};

