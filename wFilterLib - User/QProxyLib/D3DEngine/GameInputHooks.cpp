#include "GameInputHooks.h"
#include "D3DEngine.h"
#include "WndProc.h"

GameInputHooks::GameInputHooks()
{
	WndProc* hook = new WndProc();
}

GameInputHooks::~GameInputHooks()
{
}