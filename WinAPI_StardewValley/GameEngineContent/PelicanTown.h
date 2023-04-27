#pragma once

class PelicanTown
{
public:
	// constructer destructer
	PelicanTown();
	~PelicanTown();

	// delete function
	PelicanTown(const PelicanTown& _Ohter) = delete;
	PelicanTown(PelicanTown&& _Ohter) noexcept = delete;
	PelicanTown& operator=(const PelicanTown& _Other) = delete;
	PelicanTown& operator=(PelicanTown&& _Other) noexcept = delete;

protected:

private:

};

