#pragma once

class Customize
{
public:
	// constructer destructer
	Customize();
	~Customize();

	// delete function
	Customize(const Customize& _Ohter) = delete;
	Customize(Customize&& _Ohter) noexcept = delete;
	Customize& operator=(const Customize& _Other) = delete;
	Customize& operator=(Customize&& _Other) noexcept = delete;

protected:

private:

};

