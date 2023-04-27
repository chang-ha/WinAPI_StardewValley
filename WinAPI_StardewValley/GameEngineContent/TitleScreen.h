#pragma once

class TitleScreen
{
public:
	// constructer destructer
	TitleScreen();
	~TitleScreen();

	// delete function
	TitleScreen(const TitleScreen& _Ohter) = delete;
	TitleScreen(TitleScreen&& _Ohter) noexcept = delete;
	TitleScreen& operator=(const TitleScreen& _Other) = delete;
	TitleScreen& operator=(TitleScreen&& _Other) noexcept = delete;

protected:

private:

};

