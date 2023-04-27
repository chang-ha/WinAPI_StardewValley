#pragma once

class CindersapForest
{
public:
	// constructer destructer
	CindersapForest();
	~CindersapForest();

	// delete function
	CindersapForest(const CindersapForest& _Ohter) = delete;
	CindersapForest(CindersapForest&& _Ohter) noexcept = delete;
	CindersapForest& operator=(const CindersapForest& _Other) = delete;
	CindersapForest& operator=(CindersapForest&& _Other) noexcept = delete;

protected:

private:

};

