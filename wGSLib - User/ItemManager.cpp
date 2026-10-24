#include "pch.h"
#include "ItemManager.h"
#include "MemoryUtility.h"

// -----------------------------------------------------------------------
typedef BOOL(__thiscall* fnDropItem)(
	void* pGameObject,
	const char* codename, uintptr_t countOrPlus,
	uintptr_t unkZero1,
	uintptr_t* pCount,
	uintptr_t unkZero2,
	uintptr_t unkOne,
	uintptr_t unkZero3,
	uintptr_t unkZero4);

// -----------------------------------------------------------------------
const DWORD cdwDropItemAddr = 0x004AA680;
const DWORD cdwDropItemMaxPlusCmpCondAddr = 0x004AA74C;

// -----------------------------------------------------------------------
fnDropItem m_fnDropItem;

ItemManager::ItemManager()
{

}

ItemManager::~ItemManager()
{

}

// -----------------------------------------------------------------------
BOOL
ItemManager::Initialize()
{
	m_fnDropItem = reinterpret_cast<fnDropItem>(
		cdwDropItemAddr);

	return TRUE;
}

// -----------------------------------------------------------------------
//TODO: CGObj etc ?
BOOL
ItemManager::DropItem(void* pGameObject, const char* szCodename, BYTE plus)
{
	uintptr_t plusCopy = plus;
	return m_fnDropItem(pGameObject, szCodename, 0, 0, &plusCopy, 0, 1, 0, 0);
}

// -----------------------------------------------------------------------
void
ItemManager::DisableDropItemMaxPlusCheck()
{
	void* addr = reinterpret_cast<void*>(cdwDropItemMaxPlusCmpCondAddr);
	CMemoryUtility::UnProtect(addr, 1);
	*(BYTE*)(cdwDropItemMaxPlusCmpCondAddr) = MEMUTIL_ASM_OPCODE_SHORT_JUMP;
	std::cout << " - Drop item max plus check disabled\n" << std::endl;
	CMemoryUtility::ReProtect();
}

// -----------------------------------------------------------------------