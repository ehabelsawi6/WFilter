#ifndef GAMEWORLDCONTEXT_H
#define GAMEWORLDCONTEXT_H

#include "CDefaultWorldContextController.h"

class GameWorldContext
{
public:
	char pad_0000[36]; //0x0000
	CDefaultWorldContextController* iCDefaultWorldContextController; //0x0024
	char pad_0028[156]; //0x0028
}; //Size: 0x00C4

#endif