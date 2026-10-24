#ifndef Q_GAME_COMMON_HOOKS_H
#define Q_GAME_COMMON_HOOKS_H
#include "../stdafx.h"

class GameCommonHooks
{
public:
	GameCommonHooks();
	~GameCommonHooks();

	bool InstallResetFrameHook();
	bool InstallEndFrameHook();
private:

};

#endif