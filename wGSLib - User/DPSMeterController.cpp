#pragma once


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include "detours.h"
#pragma comment(lib, "detours.lib")

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;


#define GS_NS_START namespace SR_GAMESERVER {
#define GS_NS_END } 
//#define GS_DEBUG 



#include "DPSMeterController.h"
#include <set>
GS_NS_START
//main definitions


// Declaring the type of Predicate that accepts 2 pairs and return a bool
typedef std::function<bool(std::pair<unsigned int, int>, std::pair<unsigned int, int>)> Comparator;

const DWORD cdwOnMonsterDeath = 0x004C44AD;
const DWORD cdwOnMonsterDeathJmpback = 0x004C44B3;

std::map<int, int> map;

void __fastcall IterateMyMap(int *piParm2)
{
	char cVar1;
	int iVar2;
	int **ppiVar3;
	int **ppiVar4;

	iVar2 = *reinterpret_cast<int*>(piParm2);

	if (*(char *)(iVar2 + 0x19) == '\0') {
		ppiVar3 = *(int ***)(iVar2 + 8);
		if (*(char *)((int)ppiVar3 + 0x19) != '\0') {
			iVar2 = *(int *)(iVar2 + 4);
			cVar1 = *(char *)(iVar2 + 0x19);
			while ((cVar1 == '\0' && (*reinterpret_cast<int*>(piParm2) == *(int *)(iVar2 + 8)))) {
				*piParm2 = iVar2;
				iVar2 = *(int *)(iVar2 + 4);
				cVar1 = *(char *)(iVar2 + 0x19);
			}
			*piParm2 = iVar2;
			return;
		}
		cVar1 = *(char *)((int)*ppiVar3 + 0x19);
		ppiVar4 = (int **)*ppiVar3;
		while (cVar1 == '\0') {
			cVar1 = *(char *)((int)*ppiVar4 + 0x19);
			ppiVar3 = ppiVar4;
			ppiVar4 = (int **)*ppiVar4;
		}
		*(int ***)(piParm2) = ppiVar3;
		return;
	}

	return;
}
__declspec(naked) void ASM_OnMonsterDeath()
{
	__asm
	{
		pushad;
		pushfd;
		PUSH ECX;
		PUSH EBX;
		CALL CDpsMeterController::OnMonsterDeath;
		popfd;
		popad;
		mov eax, dword ptr fs : [0x00000000];
		jmp cdwOnMonsterDeathJmpback;
	}
}
void CDpsMeterController::OnMonsterDeath(CGObjPC* player, CGObjMob* monster)
{
	try
	{
		if (player && monster && *(DWORD*)monster == 0x00AEDDAC)
		{
			if (monster->CInstance)
			{
				if (monster->CInstance->GetObjCommon())
				{
					if (monster->CInstance->GetObjCommon()->Rarity != 3) return;
					std::map<unsigned int, int> DamageList;

					std::map<int, int>::iterator begin_iterator = monster->m_AggroMap.begin();

					int *currentIterator = ((int*)&begin_iterator);

					for (int i = 0; i < monster->m_AggroMap.size(); i++)
					{
						int addr = *currentIterator;
						unsigned int UniqueID = *reinterpret_cast<unsigned int*>(addr + 0x10);
						int Damage = *reinterpret_cast<int*>(addr + 0x14);

						DamageList[UniqueID] = Damage;

						if (i + 1 < monster->m_AggroMap.size())
						{
							IterateMyMap(currentIterator);
						}
					}
					Comparator compFunctor =
						[](std::pair<unsigned int, int> elem1, std::pair<unsigned int, int> elem2)
					{
						return elem1.second > elem2.second;
					};

					std::set<std::pair<unsigned int, int>, Comparator> DamagesInTotal(
						DamageList.begin(), DamageList.end(), compFunctor);
					std::vector<std::pair<unsigned int, int>> TotalValueForPeer;
					int8_t counter = 0;
					for (auto& damage : DamagesInTotal)
					{
						if (counter < 8)
						{
							TotalValueForPeer.push_back({ damage.first, damage.second });
							counter++;
						}
						else
							break;
					}
					auto Message = player->AllocMsgForPeer(0x1338);
					Message->Write<int8_t>(0x42);
					Message->Write<int32_t>(monster->CInstance->RefObjID);
					Message->Write<int32_t>(counter);
					for (auto& value : TotalValueForPeer)
					{
						Message->Write<int32_t>(value.first);
						Message->Write<int32_t>(value.second);
					}
					player->SendMsgToPeer(Message);

				}
			}
		}
	}
	catch (const std::exception& ex)
	{
		printf("%s error reason %s\n", __FUNCTION__, ex.what());
	}
	catch (...)
	{
		printf("%s error reason unk\n", __FUNCTION__);
	}
}
void CDpsMeterController::Initialize()
{
	MemoryHelper::SetNop(cdwOnMonsterDeath, 6);
	MemoryHelper::Detour(false, reinterpret_cast<void*>(cdwOnMonsterDeath), ASM_OnMonsterDeath);
}
GS_NS_END