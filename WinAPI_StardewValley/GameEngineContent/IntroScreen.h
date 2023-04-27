#pragma once

class IntroScreen
{
public:
	// constructer destructer
	IntroScreen();
	~IntroScreen();

	// delete function
	IntroScreen(const IntroScreen& _Ohter) = delete;
	IntroScreen(IntroScreen&& _Ohter) noexcept = delete;
	IntroScreen& operator=(const IntroScreen& _Other) = delete;
	IntroScreen& operator=(IntroScreen&& _Other) noexcept = delete;

protected:

private:

};

