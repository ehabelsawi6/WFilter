#ifndef JETITEMMANAGER_H
#define JETITEMMANAGER_H
#include "pch.h"

class ItemManager
{
public:
	// -----------------------------------------------------------------------
	ItemManager();
	~ItemManager();

	// -----------------------------------------------------------------------
	BOOL
		DropItem(void* pGameObject, const char* szCodename, BYTE countOrPlus);

	// -----------------------------------------------------------------------
	void
		DisableDropItemMaxPlusCheck();

	// -----------------------------------------------------------------------
	BOOL
		Initialize();

	// -----------------------------------------------------------------------
};
#endif