#include "ContentUIManager.h"

ContentUIManager* ContentUIManager::MainUI = nullptr;

ContentUIManager::ContentUIManager()
{
	MainUI = this;
}

ContentUIManager::~ContentUIManager()
{

}

void ContentUIManager::Start()
{

}