#pragma once
#include "pch.h"
#include "IGObj.h"
#include "GObjChar.h"
#include "RefObjPC.h"
#include "CInstancePC.h"
#include "GameWorldContextEX.h"
#include "GameWorldContext.h"
#include "CClassLink_CGObjChar.h"
#include "CAsyncJobMgr.h"
#include "UnkHeap.h"
#include "Param.h"
#include "CRTNavCellQuad.h"
#include "CZoeZoeRnd.h"
#include "sGCharAbnormalStatus.h"
#include "CGCharAutoCommandActor.h"
#include "CGCharAutoNavigator.h"
#include "CGStorage.h"
#include "CAlchemyMagicOptionOP.h"
#include "CSetMagicOptionOP.h"
#include "CSocketOptionOP.h"
#include "CMessenger.h"
#include "CGObjPC_QuestManager.h"
#include "CGObjPC_SpotManager.h"
#include "CInstanceStaticAvatar.h"
#include "CInstanceCharTrijob.h"
#include "WMGR.h"
#include "CInstanceChestInfo.h"
#include "COpenMarketAgent.h"
#include "CInstanceClientConfig.h"
#include "CEventHandlers.h"
#include "CGObjPC_VTable.h"
#include "GString.h"

class CInstancePC;
class CMsgStreamBuffer;

struct E_VITAL_STATE_UPDATE_MASK
{
public:
	enum Enum : DWORD
	{
		PK_PENALTY = 1024,
	};
};

struct E_STORAGE_TYPE
{
	enum Enum : BYTE
	{
		PC_STORAGE = 0,
		NPC_INVENTORY = 1,
		COS_INVENTORY = 2,
		CHEST = 3,
		GUILD_CHEST = 4,
		AVATAR_INVENTORY = 5,
		MAGIC_CUBE_STORAGE = 6
	};
};

enum INTERACTMODE : BYTE
{
	INTERACTMODE_NONE = 0,
	INTERACTMODE_HANDSHAKING = 1,
	INTERACTMODE_P2P = 2,
	INTERACTMODE_MARKET_OWNER = 3,
	INTERACTMODE_P2N_TALK = 4,
	INTERACTMODE_P2N_DEAL = 5,
	INTERACTMODE_P2N_OPENMKT_DEAL = 6,
};

enum GROUPMODE : BYTE
{
	GROUPMODE_SOLO = 0,
	GROUPMODE_PARTY_SETUP = 1,
	GROUPMODE_PARTY = 2,
	GROUPMODE_SOLOPARTY_SETUP = 3,
	GROUPMODE_SOLOPARTY = 4,
};

enum BATTLESTATE : BYTE
{
	BATTLESTATE_IN_PEACE = 0,
	BATTLESTATE_IN_BATTLE = 1,
};


#pragma pack(push, 1)
struct SObjectStateFlags
{
	//Dunno exact count atm fck it
	BYTE first;
	BYTE second;
	BYTE third;
	BYTE fourth;
	BYTE btMsgBlockState;
};
#pragma pack(pop)

//TODO: Inheritence with VFT etc from IGObj, CGObj, CGObjChar etc
#pragma pack(push, 1)

class CGObjPC : public CGObjChar
{
private:
	typedef LPVOID(__thiscall* FN_ADD_ITEM_EXT)(
		CGObjPC*, DWORD dwStorageType, LPCSTR lpszCodename, int nItemCount,
		DWORD& dwResultCode, BYTE /* 0 */, bool bRandomizeStats, //not sure actually
		DWORD /* 0, maybe slot */, BYTE btPlusValue, DWORD /* 0 */, DWORD /* 1 */, DWORD /* 0 */, DWORD /* 0 */);

	typedef void(__thiscall* FN_UPDATE_VITAL_STATE)(
		const CGObjPC*, LPVOID pAttacker,
		int nDecreaseBy, int unkZero_1, DWORD dwUpdateReason, int unkZero_2);

	typedef void(__thiscall* FN_OFFSET_GOLD)(CGObjPC*, UINT64 lAmount, BYTE btReason, bool bSendUpdateMsg, bool bShowDeliveryMsg);
	typedef bool(__thiscall* FN_TELEPORT_TO)(CGObjPC*, SWorldID& stWorldID, STeleportPos pos, int unk1);
	typedef void(__thiscall* FN_OFFSET_SKILL_POINT)(CGObjPC*, int nAmount, DWORD dwUnknown1);
	typedef BOOL(__thiscall* FN_ENTER_PVP)(CGObjPC*, BYTE btState);

	//unique id - maybe used for animation (flying exp bubbles)
	typedef void(__thiscall* FN_OFFSET_EXP_POINT)(CGObjPC*, DWORD dwExpSourceObjUniqueID, DWORD64 qwLevelExp, DWORD64 qwSkillExp, DWORD& dwUnk);

	//004E0830
	typedef CMsgStreamBuffer* (__thiscall* FN_ALLOC_MSG_FOR_PEER)(CGObjPC*, WORD wMsgID);

	//004E0860
	typedef DWORD(__thiscall* FN_SEND_MSG_TO_PEER)(CGObjPC*, CMsgStreamBuffer* pMsg);

	static FN_ADD_ITEM_EXT s_pfnAddItem_EXT;
	static FN_UPDATE_VITAL_STATE s_pfnUpdateVitalState;
	static FN_OFFSET_GOLD s_pfnOffsetGold;
	static FN_TELEPORT_TO s_pfnTeleportTo;
	static FN_OFFSET_SKILL_POINT s_pfnOffsetSkillPoint;
	static FN_OFFSET_EXP_POINT s_pfnOffsetExpPoint;
	static FN_ENTER_PVP s_pfnEnterPvp;
	static FN_ALLOC_MSG_FOR_PEER s_pfnAllocMsgForPeer;
	static FN_SEND_MSG_TO_PEER s_pfnSendMsgToPeer;
public:
	static void SetupFunctionPointers();

	//Begin customs & funcs not yet propertly organized in VFT
	CInstancePC* GetInstance() const;
	CGStorage GetStorage() const;
	RefObjPC* GetRefObj() const;
	BOOL CanSendMessage();

	WORD GetCurFreeStatPoints();
	void SetCurFreeStatPoints(WORD wAmount);
	void AddStrInt(WORD wStr, WORD wInt);
	int GetDBID() const;

	void inquire_same_item(const char* codename);

	void DealDamage(int nReasonMask, int nAmount);
	DWORD AddItem(DWORD dwStorageType, LPCSTR lpszCodename, int nCount, BYTE btPlusValue);
	void SetLiveItem(int slot, const char* itemcode);
	void AddGold(int nAmount, bool bShowDeliveryMsg);
	void TeleportTo(SWorldID stWorldID, STeleportPos pos);
	void AddSkillPoints(int nAmount);
	void LiveSkill(int SilkID);
	void AddExpPoints(DWORD64 qwLevelExp, DWORD64 qwSpExp);
	void SetPvpState(BYTE btState);
	void TeleportToOwnPos();
	//void UpdateHwanLevel(BYTE btNewLevel);
	//btUnk1 usually 0
	void UpdateZerkLevel(int nAmount);
	void UpdateSilk(int nSilk, int nSilkGift, int nSilkPoint, bool bSendPacket);
	void DropItem(char* szCodename, int ItemCount, int& plus);
	void SetGrantName(std::n_string* grantname);
	void UpdateHwan(char hwanLevel);
	void SetCharState(char a2);
	void UpdateSP(int amount);
	static CGObjPC* GetObjPCByCharName(const char* charname);
	CMsgStreamBuffer* AllocMsgForPeer(WORD wMsgID);
	void SendMsgToPeer(CMsgStreamBuffer* pMsg);

public:
	CGObjPC_VTable* vft; //0x0004
	uintptr_t UniqueID; //0x0008
	char pad_000C[12]; //0x000C
	BYTE N00004F79; //0x0018
	char pad_0019[3]; //0x0019
	BYTE N00004F7A; //0x001C
	BYTE N000042C6; //0x001D
	BYTE UnkPvpRelated; //0x001E
	BYTE N000042C7; //0x001F
	BYTE N00004F7B; //0x0020
	char pad_0021[15]; //0x0021
	UnkHeap* UnkHeapPtr; //0x0030
	CInstancePC* iCInstancePC; //0x0034
	char pad_0038[8]; //0x0038
	CEventHandlers iCEventHandlers; //0x0040
	GameWorldContextEX iGameWorldContextEX; //0x0074
	GameWorldContext iGameWorldContext; //0x00B4
	CClassLink_CGObjChar iCGObjChar_ClassLink; //0x0178
	char pad_01C4[20]; //0x01C4
	CAsyncJobMgr iCAsyncJobMgr; //0x01D8
	CParam* Param1; //0x025C
	CParam* Param2; //0x0260
	CParam* iCParam; //0x0264
	CParam* Param4; //0x0268
	CParam* Param5; //0x026C
	CParam* Param6; //0x0270
	CParam* Param7; //0x0274
	CParam* Param8; //0x0278
	CParam* Param9; //0x027C
	CParam* iCParam4; //0x0280
	CParam* iCParam5; //0x0284
	CParam* iCParam6; //0x0288
	CParam* iCParam7; //0x028C
	CParam* iCParam8; //0x0290
	CParam* iCParam9; //0x0294
	CParam* iCParam10; //0x0298
	CParam* iCParam11; //0x029C
	CParam* iCParam12; //0x02A0
	CParam* iCParam13; //0x02A4
	CParam* iCParam14; //0x02A8
	CParam* iCParam15; //0x02AC
	CParam* iCParam16; //0x02B0
	CParam* iCParam17; //0x02B4
	CParam* iCParam18; //0x02B8
	CParam* iCParam19; //0x02BC
	CParam* iCParam20; //0x02C0
	CParam* iCParam21; //0x02C4
	CParam* iCParam22; //0x02C8
	CParam* iCParam23; //0x02CC
	CParam* iCParam40; //0x02D0
	CParam* iCParam41; //0x02D4
	CParam* iCParam24; //0x02D8
	CParam* iCParam25; //0x02DC
	CParam* iCParam26; //0x02E0
	CParam* N000054F6; //0x02E4
	CParam* N000054F7; //0x02E8
	CParam* N000054F8; //0x02EC
	CParam* N000054F9; //0x02F0
	CParam* N000054FA; //0x02F4
	CParam* N000054FB; //0x02F8
	CParam* N000056EA; //0x02FC
	CParam* N000056EB; //0x0300
	CParam* N000056EC; //0x0304
	CParam* N000056ED; //0x0308
	CParam* N000056EE; //0x030C
	CParam* N000056EF; //0x0310
	CParam* N000056F0; //0x0314
	CParam* N000056F1; //0x0318
	CParam* N000056F2; //0x031C
	CParam* N000056F3; //0x0320
	CParam* N000056F4; //0x0324
	CParam* N000056F5; //0x0328
	CParam* N000056F6; //0x032C
	CParam* N000056F7; //0x0330
	CParam* N000056F8; //0x0334
	CParam* N000056F9; //0x0338
	CParam* N000056FA; //0x033C
	CParam* N000056FB; //0x0340
	CParam* N000056FC; //0x0344
	CParam* N000056FD; //0x0348
	CParam* N000056FE; //0x034C
	CParam* N000056FF; //0x0350
	CParam* N00005700; //0x0354
	CParam* N00005701; //0x0358
	CParam* N00005702; //0x035C
	CParam* N00005703; //0x0360
	CParam* N00005704; //0x0364
	CParam* N00005705; //0x0368
	CParam* N00005706; //0x036C
	CParam* N00005707; //0x0370
	CParam* N00005708; //0x0374
	CParam* N00005709; //0x0378
	CParam* N0000570A; //0x037C
	CParam* N0000570B; //0x0380
	CParam* N0000570C; //0x0384
	CParam* N0000570D; //0x0388
	CParam* N0000570E; //0x038C
	CParam* N0000570F; //0x0390
	CParam* N00005710; //0x0394
	CParam* N00005711; //0x0398
	CParam* N00005712; //0x039C
	CParam* N00005713; //0x03A0
	CParam* N00005714; //0x03A4
	CParam* N00005715; //0x03A8
	CParam* N00005716; //0x03AC
	CParam* N00005717; //0x03B0
	CParam* N00005718; //0x03B4
	CParam* N00005719; //0x03B8
	CParam* N0000571A; //0x03BC
	CParam* N0000571B; //0x03C0
	CParam* N0000571C; //0x03C4
	CParam* N0000571D; //0x03C8
	CParam* N0000571E; //0x03CC
	CParam* N0000571F; //0x03D0
	CParam* N00005720; //0x03D4
	CParam* N00005721; //0x03D8
	CParam* N00005722; //0x03DC
	CParam* N00005723; //0x03E0
	CParam* N00005724; //0x03E4
	CParam* N00005725; //0x03E8
	CParam* Param41; //0x03EC
	CParam* CParam41; //0x03F0
	CParam* N00005728; //0x03F4
	CParam* N00005729; //0x03F8
	CParam* N0000572A; //0x03FC
	CParam* N0000572B; //0x0400
	CParam* N0000572C; //0x0404
	CParam* N0000572D; //0x0408
	CParam* N0000572E; //0x040C
	CParam* CParam39; //0x0410
	CParam* N00005730; //0x0414
	CParam* N00005731; //0x0418
	CParam* N00005732; //0x041C
	CParam* CParam27; //0x0420
	CParam* CParam28; //0x0424
	CParam* N00005735; //0x0428
	CParam* N00005736; //0x042C
	CParam* N00005737; //0x0430
	CParam* N00005738; //0x0434
	CParam* N00005739; //0x0438
	CParam* N0000573A; //0x043C
	CParam* N0000573B; //0x0440
	CParam* N0000573C; //0x0444
	CParam* N0000573D; //0x0448
	CParam* N0000573E; //0x044C
	CParam* N0000573F; //0x0450
	CParam* N00005740; //0x0454
	CParam* N00005741; //0x0458
	CParam* N00005742; //0x045C
	CParam* N00005743; //0x0460
	CParam* N00005744; //0x0464
	CParam* N00005745; //0x0468
	CParam* N00005746; //0x046C
	CParam* N00005747; //0x0470
	CParam* N00005748; //0x0474
	CParam* N00005749; //0x0478
	CParam* N0000574A; //0x047C
	CParam* N0000574B; //0x0480
	CParam* N0000574C; //0x0484
	CParam* N0000574D; //0x0488
	CParam* N0000574E; //0x048C
	CParam* N0000574F; //0x0490
	CParam* N00005750; //0x0494
	CParam* N00005751; //0x0498
	CParam* N00005752; //0x049C
	CParam* N00005753; //0x04A0
	CParam* N00005754; //0x04A4
	CParam* N00005755; //0x04A8
	CParam* N00005756; //0x04AC
	CParam* N00005757; //0x04B0
	CParam* N00005758; //0x04B4
	CParam* N00005759; //0x04B8
	CParam* N0000575A; //0x04BC
	CParam* N0000575B; //0x04C0
	CParam* N0000575C; //0x04C4
	CParam* N0000575D; //0x04C8
	CParam* N0000575E; //0x04CC
	CParam* N0000575F; //0x04D0
	CParam* N00005760; //0x04D4
	CParam* N00005761; //0x04D8
	CParam* N00005762; //0x04DC
	CParam* N00005763; //0x04E0
	CParam* N00005764; //0x04E4
	CParam* CParam29; //0x04E8
	CParam* CParam30; //0x04EC
	CParam* CParam31; //0x04F0
	CParam* CParam32; //0x04F4
	CParam* CParam33; //0x04F8
	CParam* CParam34; //0x04FC
	CParam* CParam35; //0x0500
	CParam* CParam36; //0x0504
	CParam* CParam37; //0x0508
	CParam* CParam38; //0x050C
	CParam* CParam395; //0x0510
	CParam* N00005770; //0x0514
	CParam* N00005771; //0x0518
	CParam* N00005772; //0x051C
	CParam* N00005773; //0x0520
	CParam* N00005774; //0x0524
	CParam* N00005775; //0x0528
	CParam* N00005776; //0x052C
	CParam* N00005777; //0x0530
	CParam* N00005778; //0x0534
	CParam* N00005779; //0x0538
	CParam* N0000577A; //0x053C
	CParam* N0000577B; //0x0540
	CParam* N0000577C; //0x0544
	CParam* N0000577D; //0x0548
	CParam* N0000577E; //0x054C
	CParam* N0000577F; //0x0550
	CParam* N00005780; //0x0554
	CParam* N00005781; //0x0558
	CParam* N00005782; //0x055C
	CParam* N00005783; //0x0560
	CParam* N00005784; //0x0564
	CParam* N00005785; //0x0568
	CParam* N00005786; //0x056C
	CParam* N00005787; //0x0570
	CParam* N00005788; //0x0574
	CParam* N00005789; //0x0578
	CParam* N0000578A; //0x057C
	CParam* N0000578B; //0x0580
	CParam* N0000578C; //0x0584
	CParam* N0000578D; //0x0588
	CParam* N0000578E; //0x058C
	CParam* N0000578F; //0x0590
	CParam* N00005790; //0x0594
	CParam* N00005791; //0x0598
	CParam* N00005792; //0x059C
	CParam* N00005793; //0x05A0
	CParam* N00005794; //0x05A4
	CParam* N00005795; //0x05A8
	CParam* N00005796; //0x05AC
	CParam* N00005797; //0x05B0
	CParam* N00005798; //0x05B4
	CParam* N00005799; //0x05B8
	CParam* N0000579A; //0x05BC
	CParam* N0000579B; //0x05C0
	CParam* N0000579C; //0x05C4
	CParam* N0000579D; //0x05C8
	CParam* N0000579E; //0x05CC
	CParam* N0000579F; //0x05D0
	CParam* N000057A0; //0x05D4
	CParam* N000057A1; //0x05D8
	CParam* N000057A2; //0x05DC
	CParam* N000057A3; //0x05E0
	CParam* N000057A4; //0x05E4
	CParam* N000057A5; //0x05E8
	CParam* N000057A6; //0x05EC
	CParam* N000057A7; //0x05F0
	CParam* N000057A8; //0x05F4
	CParam* N000057A9; //0x05F8
	CParam* N000057AA; //0x05FC
	CParam* N000057AB; //0x0600
	CParam* N000057AC; //0x0604
	CParam* N000057AD; //0x0608
	CParam* N000057AE; //0x060C
	CParam* N000057AF; //0x0610
	CParam* N000057B0; //0x0614
	CParam* N000057B1; //0x0618
	CParam* N000057B2; //0x061C
	CParam* N000057B3; //0x0620
	CParam* N000057B4; //0x0624
	CParam* N000057B5; //0x0628
	CParam* N000057B6; //0x062C
	CParam* N000057B7; //0x0630
	CParam* N000057B8; //0x0634
	CParam* N000057B9; //0x0638
	CParam* N000057BA; //0x063C
	CParam* N000057BB; //0x0640
	CParam* N000057BC; //0x0644
	CParam* N000057BD; //0x0648
	CParam* N000057BE; //0x064C
	CParam* N000057BF; //0x0650
	CParam* N000057C0; //0x0654
	CParam* N000057C1; //0x0658
	CParam* N000057C2; //0x065C
	CParam* N000057C3; //0x0660
	CParam* N000057C4; //0x0664
	CParam* N000057C5; //0x0668
	CParam* N000057C6; //0x066C
	CParam* N000057C7; //0x0670
	CParam* N000057C8; //0x0674
	CParam* N000057C9; //0x0678
	CParam* N000057CA; //0x067C
	CParam* N000057CB; //0x0680
	CParam* N000057CC; //0x0684
	CParam* N000057CD; //0x0688
	CParam* N000057CE; //0x068C
	CParam* N000057CF; //0x0690
	CParam* N000057D0; //0x0694
	CParam* N000057D1; //0x0698
	CParam* N000057D2; //0x069C
	CParam* N000057D3; //0x06A0
	CParam* N000057D4; //0x06A4
	CParam* N000057D5; //0x06A8
	CParam* N000057D6; //0x06AC
	CParam* N000057D7; //0x06B0
	CParam* N000057D8; //0x06B4
	CParam* N000057D9; //0x06B8
	CParam* N000057DA; //0x06BC
	CParam* N000057DB; //0x06C0
	CParam* N000057DC; //0x06C4
	CParam* N000057DD; //0x06C8
	CParam* N000057DE; //0x06CC
	CParam* N000057DF; //0x06D0
	CParam* N000057E0; //0x06D4
	CParam* N000057E1; //0x06D8
	CParam* N000057E2; //0x06DC
	CParam* N000057E3; //0x06E0
	CParam* N000057E4; //0x06E4
	CParam* N000057E5; //0x06E8
	CParam* N000057E6; //0x06EC
	CParam* N000057E7; //0x06F0
	CParam* N000057E8; //0x06F4
	CParam* N000057E9; //0x06F8
	CParam* N000057EA; //0x06FC
	CParam* N000057EB; //0x0700
	CParam* N000057EC; //0x0704
	CParam* N000057ED; //0x0708
	CParam* N000057EE; //0x070C
	CParam* N000057EF; //0x0710
	CParam* N000057F0; //0x0714
	CParam* N000057F1; //0x0718
	CParam* N000057F2; //0x071C
	CParam* N000057F3; //0x0720
	CParam* N000057F4; //0x0724
	CParam* N000057F5; //0x0728
	CParam* N000057F6; //0x072C
	CParam* N000057F7; //0x0730
	CParam* N000057F8; //0x0734
	CParam* N000057F9; //0x0738
	CParam* N000057FA; //0x073C
	CParam* N000057FB; //0x0740
	CParam* N000057FC; //0x0744
	CParam* N000057FD; //0x0748
	CParam* N000057FE; //0x074C
	CParam* N000057FF; //0x0750
	CParam* N00005800; //0x0754
	CParam* N00005801; //0x0758
	CParam* N00005802; //0x075C
	CParam* N00005803; //0x0760
	CParam* N00005804; //0x0764
	CParam* N00005805; //0x0768
	CParam* N00005806; //0x076C
	CParam* N00005807; //0x0770
	CParam* N00005808; //0x0774
	CParam* N00005809; //0x0778
	CParam* N0000580A; //0x077C
	CParam* N0000580B; //0x0780
	CParam* N0000580C; //0x0784
	CParam* N0000580D; //0x0788
	CParam* N0000580E; //0x078C
	CParam* N0000580F; //0x0790
	CParam* N00005810; //0x0794
	CParam* N00005811; //0x0798
	CParam* N00005812; //0x079C
	CParam* N00005813; //0x07A0
	CParam* N00005814; //0x07A4
	CParam* N00005815; //0x07A8
	CParam* N00005816; //0x07AC
	CParam* N00005817; //0x07B0
	CParam* N00005818; //0x07B4
	CParam* N00005819; //0x07B8
	CParam* N0000581A; //0x07BC
	CParam* N0000581B; //0x07C0
	CParam* N0000581C; //0x07C4
	CParam* N0000581D; //0x07C8
	CParam* N0000581E; //0x07CC
	CParam* N0000581F; //0x07D0
	CParam* N00005820; //0x07D4
	CParam* N00005821; //0x07D8
	CParam* N00005822; //0x07DC
	CParam* N00005823; //0x07E0
	CParam* N00005824; //0x07E4
	CParam* N00005825; //0x07E8
	CParam* N00005826; //0x07EC
	CParam* N00005827; //0x07F0
	CParam* N00005828; //0x07F4
	CParam* N00005829; //0x07F8
	CParam* N0000582A; //0x07FC
	CParam* N0000582B; //0x0800
	CParam* N0000582C; //0x0804
	CParam* N0000582D; //0x0808
	CParam* N0000582E; //0x080C
	CParam* N0000582F; //0x0810
	CParam* N00005830; //0x0814
	CParam* N00005831; //0x0818
	CParam* N00005832; //0x081C
	CParam* N00005833; //0x0820
	CParam* N00005834; //0x0824
	CParam* N00005835; //0x0828
	CParam* N00005836; //0x082C
	CParam* N00005837; //0x0830
	CParam* N00005838; //0x0834
	CParam* N00005839; //0x0838
	CParam* N0000583A; //0x083C
	CParam* N0000583B; //0x0840
	CParam* N0000583C; //0x0844
	CParam* N0000583D; //0x0848
	CParam* N0000583E; //0x084C
	CParam* N0000583F; //0x0850
	CParam* N00005840; //0x0854
	CParam* N00005841; //0x0858
	CParam* N00005842; //0x085C
	CParam* N00005843; //0x0860
	CParam* N00005844; //0x0864
	CParam* N00005845; //0x0868
	CParam* N00005846; //0x086C
	CParam* N00005847; //0x0870
	CParam* N00005848; //0x0874
	CParam* N00005849; //0x0878
	CParam* N0000584A; //0x087C
	CParam* N0000584B; //0x0880
	CParam* N0000584C; //0x0884
	CParam* N0000584D; //0x0888
	CParam* N0000584E; //0x088C
	CParam* N0000584F; //0x0890
	CParam* N00005850; //0x0894
	CParam* N00005851; //0x0898
	CParam* N00005852; //0x089C
	CParam* N00005853; //0x08A0
	CParam* N00005854; //0x08A4
	CParam* N00005855; //0x08A8
	CParam* N00005856; //0x08AC
	CParam* N00005857; //0x08B0
	CParam* N00005858; //0x08B4
	CParam* N00005859; //0x08B8
	CParam* N0000585A; //0x08BC
	CParam* N0000585B; //0x08C0
	CParam* N0000585C; //0x08C4
	CParam* N0000585D; //0x08C8
	CParam* N0000585E; //0x08CC
	CParam* N0000585F; //0x08D0
	CParam* N00005860; //0x08D4
	CParam* N00005861; //0x08D8
	CParam* N00005862; //0x08DC
	CParam* N00005863; //0x08E0
	CParam* N00005864; //0x08E4
	CParam* N00005865; //0x08E8
	CParam* N00005866; //0x08EC
	CParam* N00005867; //0x08F0
	CParam* N00005868; //0x08F4
	CParam* N00005869; //0x08F8
	CParam* N0000586A; //0x08FC
	CParam* N0000586B; //0x0900
	CParam* N0000586C; //0x0904
	CParam* N0000586D; //0x0908
	CParam* N0000586E; //0x090C
	CParam* N0000586F; //0x0910
	CParam* N00005870; //0x0914
	CParam* N00005871; //0x0918
	CParam* N00005872; //0x091C
	CParam* N00005873; //0x0920
	CParam* N00005874; //0x0924
	CParam* N00005875; //0x0928
	CParam* N00005876; //0x092C
	CParam* N00005877; //0x0930
	CParam* N00005878; //0x0934
	CParam* N00005879; //0x0938
	CParam* N0000587A; //0x093C
	CParam* N0000587B; //0x0940
	CParam* N0000587C; //0x0944
	CParam* N0000587D; //0x0948
	CParam* N0000587E; //0x094C
	CParam* N0000587F; //0x0950
	CParam* N00005880; //0x0954
	CParam* N00005881; //0x0958
	CParam* N00005882; //0x095C
	CParam* N00005883; //0x0960
	CParam* N00005884; //0x0964
	CParam* N00005885; //0x0968
	CParam* N00005886; //0x096C
	CParam* N00005887; //0x0970
	CParam* N00005888; //0x0974
	CParam* N00005889; //0x0978
	CParam* N0000588A; //0x097C
	CParam* N0000588B; //0x0980
	CParam* N0000588C; //0x0984
	CParam* N0000588D; //0x0988
	CParam* N0000588E; //0x098C
	CParam* N0000588F; //0x0990
	CParam* N00005890; //0x0994
	CParam* N00005891; //0x0998
	CParam* N00005892; //0x099C
	CParam* N00005893; //0x09A0
	CParam* N00005894; //0x09A4
	CParam* N00005895; //0x09A8
	CParam* N00005896; //0x09AC
	CParam* N00005897; //0x09B0
	CParam* N00005898; //0x09B4
	CParam* N00005899; //0x09B8
	CParam* N0000589A; //0x09BC
	CParam* N0000589B; //0x09C0
	CParam* N0000589C; //0x09C4
	CParam* N0000589D; //0x09C8
	CParam* N0000589E; //0x09CC
	CParam* N0000589F; //0x09D0
	CParam* N000058A0; //0x09D4
	CParam* N000058A1; //0x09D8
	CParam* N000058A2; //0x09DC
	CParam* N000058A3; //0x09E0
	CParam* N000058A4; //0x09E4
	CParam* N000058A5; //0x09E8
	CParam* N000058A6; //0x09EC
	CParam* N000058A7; //0x09F0
	char pad_09F4[12]; //0x09F4
	uintptr_t CurHealth; //0x0A00
	uintptr_t CurMana; //0x0A04
	char pad_0A08[8]; //0x0A08
	CRTNavCellQuad* iCRTNavCellQuad; //0x0A10
	char pad_0A14[4]; //0x0A14
	uintptr_t RegionID; //0x0A18
	float PosX; //0x0A1C
	float PosY; //0x0A20
	float PosZ; //0x0A24
	char pad_0A28[8]; //0x0A28
	CGObjPC* CGObjPC1; //0x0A30
	CZoeZoeRnd iCZoeZoeRnd; //0x0A34
	sGCharAbnormalStatus isGCharAbnormalStatus1; //0x0D3C
	sGCharAbnormalStatus isGCharAbnormalStatus2; //0x0DAC
	sGCharAbnormalStatus isGCharAbnormalStatus3; //0x0E1C
	sGCharAbnormalStatus isGCharAbnormalStatus4; //0x0E8C
	sGCharAbnormalStatus isGCharAbnormalStatus5; //0x0EFC
	sGCharAbnormalStatus isGCharAbnormalStatus6; //0x0F6C
	sGCharAbnormalStatus isGCharAbnormalStatus7; //0x0FDC
	sGCharAbnormalStatus isGCharAbnormalStatus8; //0x104C
	sGCharAbnormalStatus isGCharAbnormalStatus9; //0x10BC
	sGCharAbnormalStatus isGCharAbnormalStatus10; //0x112C
	sGCharAbnormalStatus isGCharAbnormalStatus11; //0x119C
	sGCharAbnormalStatus isGCharAbnormalStatus12; //0x120C
	sGCharAbnormalStatus isGCharAbnormalStatus13; //0x127C
	sGCharAbnormalStatus isGCharAbnormalStatus14; //0x12EC
	sGCharAbnormalStatus isGCharAbnormalStatus15; //0x135C
	sGCharAbnormalStatus isGCharAbnormalStatus16; //0x13CC
	sGCharAbnormalStatus isGCharAbnormalStatus17; //0x143C
	sGCharAbnormalStatus isGCharAbnormalStatus18; //0x14AC
	sGCharAbnormalStatus isGCharAbnormalStatus19; //0x151C
	sGCharAbnormalStatus isGCharAbnormalStatus20; //0x158C
	sGCharAbnormalStatus isGCharAbnormalStatus21; //0x15FC
	sGCharAbnormalStatus isGCharAbnormalStatus23; //0x166C
	sGCharAbnormalStatus isGCharAbnormalStatus24; //0x16DC
	sGCharAbnormalStatus isGCharAbnormalStatus25; //0x174C
	sGCharAbnormalStatus isGCharAbnormalStatus26; //0x17BC
	sGCharAbnormalStatus isGCharAbnormalStatus27; //0x182C
	sGCharAbnormalStatus isGCharAbnormalStatus28; //0x189C
	sGCharAbnormalStatus isGCharAbnormalStatus29; //0x190C
	sGCharAbnormalStatus isGCharAbnormalStatus30; //0x197C
	sGCharAbnormalStatus isGCharAbnormalStatus31; //0x19EC
	sGCharAbnormalStatus isGCharAbnormalStatus32; //0x1A5C
	sGCharAbnormalStatus isGCharAbnormalStatus33; //0x1ACC
	char pad_1B3C[132]; //0x1B3C
	CGCharAutoCommandActor iCGCharAutoCommandActor; //0x1BC0
	CGCharAutoNavigator iCGCharAutoNavigator; //0x1BF4
	CGStorage iCGStorage_Normal; //0x1C10
	CGStorage iCGStorage_Avatar; //0x1C34
	char pad_1C58[8]; //0x1C58
	CAlchemyMagicOptionOP* iCAlchemyMagicOptionOP; //0x1C60
	CSetMagicOptionOP* iCSetMagicOptionOP; //0x1C64
	CSocketOptionOP* iCSocketOptionOP; //0x1C68
	char pad_1C6C[92]; //0x1C6C
	class CMessenger* iCMessenger; //0x1CC8
	char pad_1CCC[12]; //0x1CCC
	uintptr_t UnkJobAndPvpRelated; //0x1CD8
	char pad_1CDC[56]; //0x1CDC
	void* pSelf15; //0x1D14
	char pad_1D18[88]; //0x1D18
	void* pSelf3; //0x1D70
	CGStorage iCGStorage_Unk1; //0x1D74 type 3
	CGObjPC_QuestManager iCGObjPC_QuestManager; //0x1D98
	CGObjPC_SpotManager iCGObjPC_SpotManager; //0x1DE8
	char pad_1E0C[276]; //0x1E0C
	void* pSelf4; //0x1F20
	CInstanceStaticAvatar* iCInstanceStaticAvatar; //0x1F24
	char pad_1F28[24]; //0x1F28
	void* pSelf16; //0x1F40
	char pad_1F44[68]; //0x1F44
	uintptr_t N0000594F; //0x1F88
	uintptr_t N00005950; //0x1F8C
	uintptr_t N00005951; //0x1F90
	char pad_1F94[32]; //0x1F94
	void* pSelf18;; //0x1FB4
	CInstanceCharTrijob* iCInstanceCharTrijob; //0x1FB8
	char pad_1FBC[4]; //0x1FBC
	WMGR iWMGR; //0x1FC0
	CGStorage iCGStorage_Unk; //0x1FD8
	char pad_1FFC[16]; //0x1FFC
	CGStorage CGStorage_Unk1; //0x200C
	char pad_2030[324]; //0x2030
	uintptr_t N000059B5; //0x2174
	char pad_2178[32]; //0x2178
	CCInstanceChestInfo* CInstanceChestInfo; //0x2198
	COpenMarketAgent iCOpenMarketAgent; //0x219C
	char pad_21A0[12]; //0x21A0
	int FRPvpModeId; //0x21AC
	char pad_21B0[288]; //0x21B0
	uintptr_t N00005A0C; //0x22D0
	CInstanceClientConfig* iCInstanceClientConfig1; //0x22D4
	char pad_22D8[20]; //0x22D8
	CInstanceClientConfig* iCInstanceClientConfig2; //0x22EC
	char pad_22F0[28]; //0x22F0

	//actual size 0x2308


};

#pragma pack(pop)