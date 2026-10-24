#include "InterfaceActions.h"
#include "../../GameMain/GameMain.h"

const DWORD dwActionHookAddr = 0x00793B00;
const DWORD dwActionDispatchJmpback = (dwActionHookAddr + 6);


vUiClickInjs m_uiClickInjs;
vUiPressInjs m_uiPressInjs;

const DWORD dwHookClick = 0x00B9257D;
const DWORD dwHookClickJmpback = 0x00B92583; //retn

const DWORD dwHookKeypress = 0x00B925B5;
const DWORD dwHookKeypressJmpback = 0x00B925BD;


void DispatchActionMsg();


std::vector<tActionIdFuncPair> m_vInterfaceActions;
uint32_t m_actionId;
bool m_actionHandledByUser;

DWORD dwTargetFunc = 0;
DWORD dwIsKeypress = 0;
DWORD dwPressFlag = 0; //0x09 = ? 0x0D = login

//__declspec(naked) void
void IL_OnActionDispatch(void);
void IL_OnButtonClickDispatch(void);
void IL_OnButtonKeyDispatch(void);


InterfaceActions::InterfaceActions()
{
	void* actionHookAddr = reinterpret_cast<void*>(dwActionHookAddr);
	void* clickHookAddr = reinterpret_cast<void*>(dwHookClick);
	void* keypressHookAddr = reinterpret_cast<void*>(dwHookKeypress);

	//A action button hooks.
	//MemoryHelper::Nop(actionHookAddr, 6);
	g_MemoryHelper->Detour(false, actionHookAddr, IL_OnActionDispatch);

	//Click on UI control ingame.
	//MemoryHelper::Nop(clickHookAddr, 6);
	g_MemoryHelper->Detour(false, clickHookAddr, IL_OnButtonClickDispatch);

	//Keypress (for example, pressing enter when logging in).
	//MemoryHelper::Nop(keypressHookAddr, 6);
	g_MemoryHelper->Detour(false, keypressHookAddr, IL_OnButtonKeyDispatch);

	m_actionId = 0;
	m_actionHandledByUser = false;
}

InterfaceActions::~InterfaceActions()
{
	
}


void InterfaceActions::RegisterUiPreProcessFunc(tUiClickActionPair sig)
{
	m_uiClickInjs.push_back(sig);
}

void InterfaceActions::RegisterUiPreProcessFunc(tUiPressActionFlagPair sig)
{
	m_uiPressInjs.push_back(sig);
}


void InterfaceActions::AddInterfaceAction(tActionIdFuncPair action)
{
	m_vInterfaceActions.push_back(action);
}

tUiPressFlagActionFunc InterfaceActions::GetPreProcessPressFunc(uint32_t offset)
{
	for (std::vector<tUiPressActionFlagPair>::iterator item = m_uiPressInjs.begin(); item != m_uiPressInjs.end(); item++)
	{
		if (item->first == offset)
			return item->second;
	}
	return NULL;
}


void InterfaceActions::PrintTargetFuncOffset()
{

	printf("------------------------------------\n");
	if (dwIsKeypress) 
		std::cout << "KEYPRESS" << std::endl;
	else std::cout << "MOUSECLICK" << std::endl;

	std::cout << "UI func -> " << "-> 0x" << std::hex << dwTargetFunc << std::endl;

	if (!dwIsKeypress)
	{
		fnActionFunc func = GetPreProcessClickFunc(dwTargetFunc);
		if (func != NULL)
			func();
	}
	else
	{
		tUiPressFlagActionFunc func = GetPreProcessPressFunc(dwTargetFunc);
		if (func != NULL)
			func(dwPressFlag);
	}
}



fnActionFunc InterfaceActions::GetPreProcessClickFunc(uint32_t offset)
{
	for (std::vector<tUiClickActionPair>::iterator item = m_uiClickInjs.begin(); item != m_uiClickInjs.end(); item++)
	{
		if (item->first == offset)
			return item->second;
	}
	return NULL;
}


__declspec(naked) void IL_OnButtonClickDispatch()
{
	__asm mov dwTargetFunc, eax;
	__asm mov dwIsKeypress, 0; //click

	__asm pushad;

	InterfaceActions::PrintTargetFuncOffset();

	__asm popad;

	__asm call eax;
	__asm pop edi;
	__asm mov eax, esi;
	__asm pop esi;

	//back to client code !
	__asm jmp dwHookClickJmpback;
}


__declspec(naked) void IL_OnButtonKeyDispatch()
{
	__asm mov dwTargetFunc, eax;
	__asm mov dwIsKeypress, 1;	//press&normal
	__asm mov dwPressFlag, ecx;

	__asm pushad;
	InterfaceActions::PrintTargetFuncOffset();
	__asm popad;

	__asm mov ecx, dword ptr ss : [esp + 0x28];
	__asm add ecx, edx;
	__asm call eax;
	__asm jmp dwHookKeypressJmpback;
}



__declspec(naked) void IL_OnActionDispatch()
{
	__asm push eax;
	//The action ID from actionwnddata
	__asm mov eax, dword ptr[esp + 8 + 4];
	__asm mov m_actionId, eax;
	__asm pop eax;

	__asm pushad;
	__asm pushfd;
	__asm call DispatchActionMsg;
	__asm popfd;
	__asm popad;

	__asm cmp m_actionHandledByUser, TRUE
	__asm jne NOT_HANDLED_BY_USER;

	//Pass to code... heres a little trick :) - Make it use default case so the original action
	//does not get executed (default switchcase).
	__asm mov dword ptr[esp + 8], 0x0;
	__asm mov m_actionHandledByUser, FALSE;

	NOT_HANDLED_BY_USER:

	__asm push ebp;
	__asm mov ebp, esp;
	__asm and esp, 0xFFFFFFF8;
	__asm jmp dwActionDispatchJmpback;
}



void DispatchActionMsg()
{
	for(std::vector<tActionIdFuncPair>::iterator iter = m_vInterfaceActions.begin(); iter != m_vInterfaceActions.end(); ++iter)
	{
		if(iter->first == m_actionId)
		{

			std::cout << "Action " << m_actionId << " handler invocation start" << std::endl;
			iter->second();
			
			m_actionHandledByUser = true;
			break;
		}
	}
}