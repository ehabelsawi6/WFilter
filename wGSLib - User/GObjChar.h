#pragma once
#include "pch.h"
#include "IGObj.h"
#include "RemodelUtility.h"

class CGObjChar : public IGObj
{
public:
	REMODEL_DECLARE_VIRTUAL_NOIMPL_DCTOR(CGObjChar);

	void SetBodyMode(BYTE bodymode);

};