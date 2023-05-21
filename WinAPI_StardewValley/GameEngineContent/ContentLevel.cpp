#include "ContentLevel.h"
#include "BackGround.h"

ContentLevel::ContentLevel()
{

}

ContentLevel::~ContentLevel()
{

}

float4 ContentLevel::GetRenderScale()
{
	return Back->GetRenderScale();
}
