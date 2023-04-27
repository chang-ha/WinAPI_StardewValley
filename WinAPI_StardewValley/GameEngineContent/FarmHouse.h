#pragma once

class FarmHouse
{
public:
	// constructer destructer
	FarmHouse();
	~FarmHouse();

	// delete function
	FarmHouse(const FarmHouse& _Ohter) = delete;
	FarmHouse(FarmHouse&& _Ohter) noexcept = delete;
	FarmHouse& operator=(const FarmHouse& _Other) = delete;
	FarmHouse& operator=(FarmHouse&& _Other) noexcept = delete;

protected:

private:

};

