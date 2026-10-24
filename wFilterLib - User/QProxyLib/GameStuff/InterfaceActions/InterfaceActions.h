#pragma once
#ifndef INTERFACE_ACTIONS_H
#define INTERFACE_ACTIONS_H

#include <functional>
#include "../../includes.h"

//fuck my life man srsly ill do a new lib :D this really needs improvements

//those both are by me :(


typedef void(__stdcall* fnSimpleHandler)();
typedef void(__stdcall* fnActionFunc)();

typedef std::pair<uint32_t, fnSimpleHandler> tActionIdFuncPair;
typedef std::pair<uint32_t, fnActionFunc> tUiClickActionPair;

//typedef std::function<void(uint32_t)> tUiPressFlagActionFunc;
typedef void(__stdcall* tUiPressFlagActionFunc)(uint32_t a);//fucked by me tho xD
typedef std::pair<uint32_t, tUiPressFlagActionFunc> tUiPressActionFlagPair;
typedef std::vector<tUiClickActionPair> vUiClickInjs;
typedef std::vector<tUiPressActionFlagPair> vUiPressInjs;

class InterfaceActions
{
public:
	InterfaceActions();
	~InterfaceActions();

	void AddInterfaceAction(tActionIdFuncPair action);

	void RegisterUiPreProcessFunc(tUiClickActionPair sig);
	void RegisterUiPreProcessFunc(tUiPressActionFlagPair sig);

	static fnActionFunc GetPreProcessClickFunc(uint32_t offset);
	static tUiPressFlagActionFunc GetPreProcessPressFunc(uint32_t offset);

	static void PrintTargetFuncOffset();
};

#endif