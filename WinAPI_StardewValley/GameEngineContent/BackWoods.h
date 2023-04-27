#pragma once

class BackWoods
{
public:
	// constructer destructer
	BackWoods();
	~BackWoods();

	// delete function
	BackWoods(const BackWoods& _Ohter) = delete;
	BackWoods(BackWoods&& _Ohter) noexcept = delete;
	BackWoods& operator=(const BackWoods& _Other) = delete;
	BackWoods& operator=(BackWoods&& _Other) noexcept = delete;

protected:

private:

};

