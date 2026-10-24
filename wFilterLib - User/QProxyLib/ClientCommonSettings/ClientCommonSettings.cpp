#include "ClientCommonSettings.h"
#include "../GameMain/GameMain.h"
#include "../Defines.h"

const DWORD cdwPartyMatchingOffset_1 = 0x00739451;
const DWORD cdwPartyMatchingOffset_1_Jmpback = 0x00739457;
const DWORD cdwPartyMatchingOffset_2 = 0x0073AFAD;
const DWORD cdwPartyMatchingOffset_2_Jmpback = 0x0073AFB2;
const DWORD cdwPartyMatchingOffset_3 = 0x0073B011;
const DWORD cdwPartyMatchingOffset_3_Jmpback = 0x0073B017;
const DWORD cdwPartyMatchingOffset_4 = 0x0073B02E;
const DWORD cdwPartyMatchingOffset_4_Jmpback = 0x0073B037;
const DWORD cdwPartyMatchingOffset_5 = 0x0073FA4A;
const DWORD cdwPartyMatchingOffset_5_Jmpback = 0x0073FA50;
const DWORD cdwPartyMatchingOffset_6 = 0x0073FAAD;
const DWORD cdwPartyMatchingOffset_6_Jmpback = 0x0073FAB3;
const DWORD cdwPartyMatchingOffset_7 = 0x0073FACC;
const DWORD cdwPartyMatchingOffset_7_Jmpback = 0x0073FAD3;

__declspec (naked) void ASM_OnPartyMaxLevel_1()
{
	__asm
	{
		PUSH 1;
		PUSH PARTY_MAX_LEVEL;
		MOV ECX, ESI;
		JMP cdwPartyMatchingOffset_1_Jmpback;
	}
}
__declspec (naked) void ASM_OnPartyMaxLevel_2()
{
	__asm
	{
		PUSH EBX;
		PUSH PARTY_MAX_LEVEL;
		MOV ECX, EDI;
		JMP cdwPartyMatchingOffset_2_Jmpback;
	}
}
__declspec (naked) void ASM_OnPartyMaxLevel_3()
{
	__asm
	{
		PUSH 0;
		PUSH PARTY_MAX_LEVEL;
		MOV ECX, EDI;
		JMP cdwPartyMatchingOffset_3_Jmpback;
	}
}
__declspec (naked) void ASM_OnPartyMaxLevel_4()
{
	__asm
	{
		MOV EBX, DWORD PTR[EDI];
		PUSH PARTY_MAX_LEVEL;
		PUSH 0xE18B1C;
		JMP cdwPartyMatchingOffset_4_Jmpback;
	}
}
__declspec (naked) void ASM_OnPartyMaxLevel_5()
{
	__asm
	{
		PUSH 0;
		PUSH PARTY_MAX_LEVEL;
		MOV ECX, EDI;
		JMP cdwPartyMatchingOffset_5_Jmpback;
	}
}
__declspec (naked) void ASM_OnPartyMaxLevel_6()
{
	__asm
	{
		PUSH 0;
		PUSH PARTY_MAX_LEVEL;
		MOV ECX, EDI;
		JMP cdwPartyMatchingOffset_6_Jmpback;
	}
}
__declspec (naked) void ASM_OnPartyMaxLevel_7()
{
	__asm
	{
		MOV EBX, DWORD PTR[EDI];
		PUSH PARTY_MAX_LEVEL;
		PUSH 0xE18B1C;
		JMP cdwPartyMatchingOffset_7_Jmpback;
	}
}

void ClientCommonSettings::Initialize()
{
#ifdef Anoha
	g_MemoryHelper->JMPFunction(0x0077B4F6, 0x0077B500);
#endif 

	//quest max level
	/*g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x00955134 + 3), 1);
	*(int8_t*)(0x00955134 + 3) = MAX_LEVEL;
	g_MemoryHelper->ReProtect();*/

	//Item Mall Max Item Limit
	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0xBA215C), 2);
	*(int16_t*)(0xBA215C) = ITEM_MALL_LIMIT;
	g_MemoryHelper->ReProtect();

	//mastery
#ifdef AngelRoad
	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x006AA4C3 + 1), 2);
	*(uint16_t*)(0x006AA4C3 + 1) = CH_MASTERY_MAX_LEVEL;
	g_MemoryHelper->ReProtect();

	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x006A51BC + 1), 2);
	*(uint16_t*)(0x006A51BC + 1) = CH_MASTERY_MAX_LEVEL;
	g_MemoryHelper->ReProtect();
#endif
	
	//mastery end
	
	//eu mastery
	/*g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x006A5197 + 1), 2);
	*(uint16_t*)(0x006A5197 + 1) = EU_MASTERY_MAX_LEVEL;
	g_MemoryHelper->ReProtect();

	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x006A51A2 + 1), 2);
	*(uint16_t*)(0x006A51A2 + 1) = EU_MASTERY_MAX_LEVEL;
	g_MemoryHelper->ReProtect();

	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x006AA4A3 + 1), 2);
	*(uint16_t*)(0x006AA4A3 + 1) = EU_MASTERY_MAX_LEVEL;
	g_MemoryHelper->ReProtect();

	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x006AA498 + 1), 2);
	*(uint16_t*)(0x006AA498 + 1) = EU_MASTERY_MAX_LEVEL;
	g_MemoryHelper->ReProtect();

	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0069C7C8 + 1), 1);
	*(int8_t*)(0x0069C7C8 + 1) = EU_MASTERY_MAX_LEVEL / 2;
	g_MemoryHelper->ReProtect();

	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x8A99A2 + 1), 1);
	*(int8_t*)(0x8A99A2 + 1) = EU_MASTERY_MAX_LEVEL / 2;
	g_MemoryHelper->ReProtect();*/
	//eu mastery end

	// party max level
	//g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwPartyMatchingOffset_1), ASM_OnPartyMaxLevel_1);
	//g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwPartyMatchingOffset_2), ASM_OnPartyMaxLevel_2);
	//g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwPartyMatchingOffset_3), ASM_OnPartyMaxLevel_3);
	//g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwPartyMatchingOffset_4), ASM_OnPartyMaxLevel_4);
	//g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwPartyMatchingOffset_5), ASM_OnPartyMaxLevel_5);
	//g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwPartyMatchingOffset_6), ASM_OnPartyMaxLevel_6);
	//g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwPartyMatchingOffset_7), ASM_OnPartyMaxLevel_7);

	//g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x00955134 + 3), 1);
	//*(int8_t*)(0x00955134 + 3) = PARTY_MAX_LEVEL;
	//g_MemoryHelper->ReProtect();
	//party max level end
}
