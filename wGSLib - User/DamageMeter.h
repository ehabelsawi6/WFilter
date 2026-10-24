#pragma once
#include "pch.h"
#include "IGObj.h"
#include "FilterContentDBSet.h"
#include "GObjPC.h"

#define __CGOBJNPC_AGGRO_LIST_MAP                       std::map<DWORD, SAggroMapSecondPairItem>
#define __CGOBJNPC_AGGRO_LIST_MAP_IT                    __CGOBJNPC_AGGRO_LIST_MAP::iterator
#define __CGOBJ_AGGRO_LIST_MAP_SECOND_ELEM_PAIR      std::pair<DWORD, SAggroMapSecondPairItem>

#pragma pack(push, 4)
typedef struct SAggroMapSecondPairItem
{
    DWORD dwPlayerGID;
    DWORD dwDamage;
};
#pragma pack(pop)

class CDamageMeter
{
private:
    typedef void* (__thiscall* FN_CGOBJNPC_AGGRO_MAP)(IGObj*, int a2);
    //CGameWorldContextController (CDefaultGameWorldContextController, CSiegeWorldContextController etc).
    typedef void(__thiscall* FN_CGOBJ_HANDLE_DMG)(CGObjPC* pTarget, IGObj* pAttacker, int nHpConsumption, int nMpConsumption, int unk1, int unk2);

    static FN_CGOBJNPC_AGGRO_MAP s_pfnCGObjNpcAggroMap;
    static FN_CGOBJ_HANDLE_DMG s_pfnCGObjPC_HandleDmg_SpecialWorld;

    static void* __fastcall MyCGObjNPC_HandleAggroMap(IGObj* pObj, void* /* dummy edx */, int a2);
    static void __fastcall MyCGObjPC_SpecialWorld_HandleDmg(CGObjPC* pTarget, void* /* dummy edx*/, IGObj* pAttacker, int nHpConsumption, int nMpConsumption, int unk1, int unk2);

public:

    static void Initialize();
};