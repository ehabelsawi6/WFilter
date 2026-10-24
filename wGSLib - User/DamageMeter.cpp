#include "pch.h"
#include "DamageMeter.h"
#include "MemoryUtility.h"
#include "MsgStreamBuffer.h"
#include "Game.h"
#include "GObjPC.h"
#include "RefDataManager.h"
#include "ObjMgr.h"


#define CGOBJNPC_AGGRO_MAP_FN_OFFSET		            0x004C44A0
#define FN_CGOBJPC_HANDLE_DMG_SPECIAL_WORLD_FN_OFFSET	0x0052D860

#define __CGOBJNPC_AGGRO_LIST_MAP_SECOND_ELEM_PAIR      std::pair<DWORD, SAggroMapSecondPairItem>
#define MAX_RECORDS_IN_PACKET                           8

CDamageMeter::FN_CGOBJNPC_AGGRO_MAP CDamageMeter::s_pfnCGObjNpcAggroMap;
CDamageMeter::FN_CGOBJ_HANDLE_DMG CDamageMeter::s_pfnCGObjPC_HandleDmg_SpecialWorld;

void CDamageMeter::Initialize()
{
    s_pfnCGObjNpcAggroMap = reinterpret_cast<FN_CGOBJNPC_AGGRO_MAP>(
        CGOBJNPC_AGGRO_MAP_FN_OFFSET
        );

    DetourTransactionBegin();
    DetourAttach(&(PVOID&)s_pfnCGObjNpcAggroMap, CDamageMeter::MyCGObjNPC_HandleAggroMap);
    DetourTransactionCommit();

    std::cout << __FUNCTION__ << " - DPS meter hooked" << std::endl;
}

//void __fastcall CDamageMeter::MyCGObjPC_SpecialWorld_HandleDmg(CGObjPC* pTarget, void* /* dummy edx*/, IGObj* pAttacker, int nHpConsumption, int nMpConsumption, int unk1, int unk2)
//{
//    if (!pTarget || !pAttacker)
//        return s_pfnCGObjPC_HandleDmg_SpecialWorld(pTarget, pAttacker, nHpConsumption, nMpConsumption, unk1, unk2);
//
//    if (!pTarget->IsPC() || !pAttacker->IsPC())
//        return s_pfnCGObjPC_HandleDmg_SpecialWorld(pTarget, pAttacker, nHpConsumption, nMpConsumption, unk1, unk2);
//
//    bool bIsFatalHit = (pTarget->GetHealth() - nHpConsumption) <= 0;
//
//    //This is not the final hit, we don't really care about it.
//    if (!bIsFatalHit)
//        return s_pfnCGObjPC_HandleDmg_SpecialWorld(pTarget, pAttacker, nHpConsumption, nMpConsumption, unk1, unk2);
//
//    try
//    {
//        const char* szVictimName = pTarget->GetCharName();
//        int KilledCharID = pTarget->GetDBID();
//        const char* szKillerName = pAttacker->GetCharName();
//
//      /*  CMsgStreamBuffer* pMsg = pTarget->AllocMsgForPeer(0x5011);
//        pMsg->WriteStringA(szVictimName);
//        pMsg->WriteStringA(szKillerName);
//        pTarget->SendMsgToPeer(pMsg);*/
//    }
//    catch (...)
//    {
//
//    }
//    return s_pfnCGObjPC_HandleDmg_SpecialWorld(pTarget, pAttacker, nHpConsumption, nMpConsumption, unk1, unk2);
//}

void* __fastcall CDamageMeter::MyCGObjNPC_HandleAggroMap(IGObj* pObj, void* /* dummy edx */, int a2)
{
    void* res = s_pfnCGObjNpcAggroMap(pObj, a2);

    try
    {
        if (!pObj)
            return res;

        bool isUniqueMonster = CRefDataManager::IsUniqueMonster(pObj->GetRefObjID());
        if (!isUniqueMonster)
            return res;

        __CGOBJNPC_AGGRO_LIST_MAP* aggro_map = &MEMUTIL_READ_BY_PTR_OFFSET(pObj, 0x1CA0, __CGOBJNPC_AGGRO_LIST_MAP);
        __CGOBJNPC_AGGRO_LIST_MAP_IT itCur = aggro_map->begin();
        __CGOBJNPC_AGGRO_LIST_MAP_IT itEnd = aggro_map->end();

        if (itCur == itEnd)
            return res;

        CGObjPC* pObjForSendingFilterMsg = NULL;
        while (itCur != itEnd)
        {
            SAggroMapSecondPairItem gid_dmg_pair = itCur->second;
            IGObj* pTmpObj = CGame::GetObjByGameID(gid_dmg_pair.dwPlayerGID);
            if (pTmpObj != NULL && pTmpObj->IsPC())
            {
                pObjForSendingFilterMsg = reinterpret_cast<CGObjPC*>(pTmpObj);
                break;
            }
            ++itCur;
        }

        if (pObjForSendingFilterMsg == NULL)
            return res;

        itCur = aggro_map->begin();
        CMsgStreamBuffer* pMsg = pObjForSendingFilterMsg->AllocMsgForPeer(0x5010);
        pMsg->Write<int>(pObj->GetRefObjID());
        pMsg->Write<int>(std::min<int>((int)aggro_map->size(), MAX_RECORDS_IN_PACKET));

        int idx = 0;
        while (itCur != itEnd && idx != MAX_RECORDS_IN_PACKET)
        {
            SAggroMapSecondPairItem gid_dmg_pair = itCur->second;
            pMsg->Write<UINT>(gid_dmg_pair.dwPlayerGID);
            pMsg->Write<int>(gid_dmg_pair.dwDamage);
            ++itCur;
            ++idx;
        }

        pObjForSendingFilterMsg->SendMsgToPeer(pMsg);
    }
    catch (...)
    {
    }

    return res;
}
