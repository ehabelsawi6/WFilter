#include "OldThreeJob.h"
#include "../../GameMain/GameMain.h"

const DWORD cdwOnCIFPlayerInfoLoad = 0x006B8700;
const DWORD cdwOnCIFPlayerInfoLoadJmpback = 0x006B8705;
const DWORD cdwOnDataLoadAddr = 0x8B51F0;

__declspec(naked) void ASM_OnCIFPlayerInfo()
{
	__asm
	{
		pushad;
		pushfd;
		PUSH ESI;
		CALL COldThreeJob::OnPlayerInfoCreate;
		popfd;
		popad;
		SUB ESP, 0x1C;
		MOV ECX, ESP;
		jmp cdwOnCIFPlayerInfoLoadJmpback;
	}
}


void COldThreeJob::Initialize()
{

}

void COldThreeJob::OnPlayerInfoCreate(DWORD esxi)
{
	__asm
	{
		PUSH 1;
		PUSH 0x5D;
	}
}
