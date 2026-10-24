#pragma once
#include "GameStuff/CGInterface/CSOItem.h"
#include "GameStuff/CGInterface/CGInterface.h"

class CIFItemComparison
{
	char pad_0000[912]; //0x0000
	CSOItem* _CSOItem; //0x0390

public:
	void AppendAdvancedInfo(class CIFHelperBubbleWindow* window);
};
