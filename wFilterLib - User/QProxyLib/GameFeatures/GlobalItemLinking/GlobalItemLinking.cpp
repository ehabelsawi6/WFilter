#include "GlobalItemLinking.h"
#include "../../GameMain/GameMain.h"
#include "../../GameStuff/CGInterface/CGInterface.h"
CIFEdit* g_CIFEdit;
// CIFEdit::GetText(void) .text 00653350 00000017   R . . . . . .
const wchar_t* CIFEdit::GetText()
{
	return reinterpret_cast<const wchar_t*(__thiscall*)(const CIFEdit*)>(0x00653350)(this);
}
// CIFEdit::SetText(void) .text 00653AC0 00000062 00000004 00000004 R . . . . T .
bool CIFEdit::SetText(const wchar_t* src)
{
	reinterpret_cast<void(__thiscall*)(CIFEdit*, const wchar_t*)>(0x00635EA0)(this, src);
	return true;
}

const DWORD cdwOnCIFEditWndProcHandleAddr = 0x00637A50;
const DWORD cdwOnCIFEditWndProcHandleJmpback = 0x00637A55; 

const DWORD callOrigAddr = 0x00636CD0;
__declspec (naked) void ASM_OnCIFEditWndProcHandle()
{
	__asm
	{
		pushad;
		pushfd;
		PUSH EAX;
		CALL GlobalItemLinking::FUN_00636cd0;
		popfd;
		popad;

		call callOrigAddr;
		jmp cdwOnCIFEditWndProcHandleJmpback;
	}
}
void GlobalItemLinking::FUN_00636cd0(CIFEdit* pCIFEdit)
{
	if (g_CIFEdit)
		g_CIFEdit = NULL;
	if (g_CGInterface)
	{
		CIFWholeChat* pWholeChat = reinterpret_cast<CIFWholeChat*>(g_CGInterface->field_36C.GetGUIObjectByID(56, 1));
		if (pWholeChat)
		{
			g_CIFEdit = pWholeChat->pCIFEdit;
		}
		else
		{
			g_GlobalDataMgr->m_LinkedGlobalItemEnd = 0;
			g_GlobalDataMgr->m_LinkedGlobalItemBegin = 0;
			g_GlobalDataMgr->m_CurrentLinkedItemName = std::wstring();
		}
	}
	if (pCIFEdit && pCIFEdit->GetInstance() && pCIFEdit->GetInstance()->GetPtr() == 0xDCDACC && !g_GlobalDataMgr->m_CurrentLinkedItemName.empty())
	{
		if (g_CIFEdit != NULL && g_CIFEdit == pCIFEdit) // if its equals to current global window
		{
			short backSpaceState = GetKeyState(VK_BACK);
			short deleteState = GetKeyState(VK_DELETE);
			short leftArrowKeyState = GetKeyState(VK_LEFT);
			short rightArrowKeyState = GetKeyState(VK_RIGHT);

			auto CurrIndex = pCIFEdit->GetCurrentIndex();
			auto CurrText = std::wstring(pCIFEdit->GetText());
			if (!CurrText.empty())
			{
				auto begin = CurrText.find(L"͟<");
				if (begin != std::wstring::npos)
					g_GlobalDataMgr->m_LinkedGlobalItemBegin = begin;
				auto end = CurrText.find(L"͟>");
				if (end != std::wstring::npos)
					g_GlobalDataMgr->m_LinkedGlobalItemEnd = end + 2;


				if (pCIFEdit->GetAreaSize() == 100 && g_GlobalDataMgr->m_LinkedGlobalItemEnd != 0)
					pCIFEdit->SetTextAreaSize(100 + g_GlobalDataMgr->m_CurrentLinkedItemName.length());
				if (pCIFEdit->GetAreaSize() != 100 && g_GlobalDataMgr->m_LinkedGlobalItemEnd == 0)
					pCIFEdit->SetTextAreaSize(100);
			}
			//if left
			if ((leftArrowKeyState == -127 || leftArrowKeyState == -128) && CurrIndex - 1 <= g_GlobalDataMgr->m_LinkedGlobalItemEnd && CurrIndex >= g_GlobalDataMgr->m_LinkedGlobalItemBegin)
			{
				//printf("left called %d\n", leftArrowKeyState);
				pCIFEdit->SetCurrentIndex(g_GlobalDataMgr->m_LinkedGlobalItemBegin);
				return;
			}
			//if right
			if ((rightArrowKeyState == -127 || rightArrowKeyState == -128) && CurrIndex + 1 >= g_GlobalDataMgr->m_LinkedGlobalItemBegin && CurrIndex <= g_GlobalDataMgr->m_LinkedGlobalItemEnd)
			{
				//printf("right called %d\n", rightArrowKeyState);
				pCIFEdit->SetCurrentIndex(g_GlobalDataMgr->m_LinkedGlobalItemEnd);
				return;
			}

			//printf("ChatIndex = %d - Size = %d\n", pCIFEdit->GetCurrentIndex(), pCIFEdit->GetAreaSize());


			if ((backSpaceState == -127 || backSpaceState == -128) && (CurrIndex >= g_GlobalDataMgr->m_LinkedGlobalItemBegin && CurrIndex - 1 <= g_GlobalDataMgr->m_LinkedGlobalItemEnd))
			{
				std::wstring new_str = CurrText.c_str();
				auto findedstring = CurrText.find(g_GlobalDataMgr->m_CurrentLinkedItemName.c_str());
				if (findedstring != std::wstring::npos)
				{
					CurrText.erase(g_GlobalDataMgr->m_LinkedGlobalItemBegin, g_GlobalDataMgr->m_CurrentLinkedItemName.size());

					pCIFEdit->SetText(CurrText.c_str());
					if (CurrText.length() > 0)
						pCIFEdit->SetCurrentIndex(g_GlobalDataMgr->m_LinkedGlobalItemBegin);
					else
						pCIFEdit->SetCurrentIndex(0);
					g_GlobalDataMgr->m_LinkedGlobalItemEnd = 0;
					g_GlobalDataMgr->m_LinkedGlobalItemBegin = 0;
					g_GlobalDataMgr->m_CurrentLinkedItemName = std::wstring();
					return;
				}
			}
			if ((deleteState == -127 || deleteState == -128) && (CurrIndex + 2 >= g_GlobalDataMgr->m_LinkedGlobalItemBegin && CurrIndex <= g_GlobalDataMgr->m_LinkedGlobalItemEnd))
			{
				std::wstring new_str = CurrText.c_str();
				auto findedstring = CurrText.find(g_GlobalDataMgr->m_CurrentLinkedItemName.c_str());
				if (findedstring != std::wstring::npos)
				{
					CurrText.erase(g_GlobalDataMgr->m_LinkedGlobalItemBegin, g_GlobalDataMgr->m_CurrentLinkedItemName.size());

					pCIFEdit->SetText(CurrText.c_str());
					pCIFEdit->SetCurrentIndex(CurrText.length());
					g_GlobalDataMgr->m_LinkedGlobalItemEnd = 0;
					g_GlobalDataMgr->m_LinkedGlobalItemBegin = 0;
					g_GlobalDataMgr->m_CurrentLinkedItemName = std::wstring();
					return;
				}
			}
		}

	}
}
const DWORD cdwOnIndexChanged = 0x0063A389;
const DWORD cdwOnIndexChangedJmpback = 0x0063A38F;

const DWORD cdwOnIndexHover = 0x0063A1A3;
const DWORD cdwOnIndexHoverJmpback = 0x0063A1A8;

const DWORD cdwOnChatTypeChanged = 0x007AA74D;
const DWORD cdwOnChatTypeChangedJmpback = cdwOnChatTypeChanged + 6;

__declspec (naked) void ASM_OnIndexChanged()
{
	__asm
	{
		PUSHAD;
		PUSHFD;
		PUSH EBX;
		CALL GlobalItemLinking::AppendTextToChatBox;
		POPFD;
		POPAD;
		TEST EBP, EBP;
		PUSH ESI;
		PUSH EDI;
		MOV ESI, ECX;
		JMP cdwOnIndexChangedJmpback;
	}
}


const DWORD call1_addr = 0x008B4750;

__declspec (naked) void ASM_OnIndexHover()
{
	__asm
	{
		PUSHAD;
		PUSHFD;
		PUSH EBP;
		PUSH EDX;
		CALL GlobalItemLinking::OnIndexHovered;
		POPFD;
		POPAD;
		CALL call1_addr;
		JMP cdwOnIndexHoverJmpback;
	}
}

__declspec (naked) void ASM_OnChatTypeChanged()
{
	__asm
	{
		MOV CGlobalDataManager::SelectedGameChatType, EBP;
		MOV DWORD PTR DS : [ESI + 0x420], EBP;
		jmp cdwOnChatTypeChangedJmpback;
	}
}
enum ChatType
{
	NormalChat = 16,
	PartyChat = 17,
	GuildChat = 18,
	UnionChat = 19,
	AcademyChat = 30
};
class CIFTextBox
{
public:
	char pad_0000[48]; //0x0000
	CIFChatViewer* pChatViewer; //0x0030
	DWORD m_ChatType; // 0x34
	char pad_0034[904]; //0x0038
	uint32_t LastIndex; //0x03C0
};
void GlobalItemLinking::AppendTextToChatBox(w_string_last* text)
{
	try
	{
		bool inserted_new = false;
		CIFTextBox* pCIFTextBox = 0;
		_asm {mov pCIFTextBox, ecx};
		
		if (text && pCIFTextBox && pCIFTextBox->pChatViewer && pCIFTextBox->pChatViewer->selfPtr == 0xDBBA44 && pCIFTextBox->m_ChatType == ChatType::NormalChat)
		{
			auto index = pCIFTextBox->LastIndex;
			//printf("appended new text index = %d - pointer = %02x and msg = %ls\n", index, pCIFTextBox, text->c_str());
			if (index == 100)
			{
				index = 99;
				for (auto &currentGlobalData : g_GlobalDataMgr->GlobalChatLog)
				{
					if (currentGlobalData.completed)
					{
						currentGlobalData.index -= 1; //99 =98
					}
				}
			}
			const wchar_t* g_LastChatMsg = text->c_str();
			//std::wcout << g_LastChatMsg << L" and index " << index << std::endl;
			if (g_LastChatMsg != NULL && g_LastChatMsg != 0 && *(DWORD*)g_LastChatMsg != 0x00200020)
			{
				std::wstring isGlobalCheck(g_LastChatMsg);
				if (!isGlobalCheck.empty() && isGlobalCheck.find(L"͟>") != std::wstring::npos)
				{
					std::wstring GlobalMsg(g_LastChatMsg);
					if (!GlobalMsg.empty() && GlobalMsg.find(L":") != std::wstring::npos)
					{
						GlobalChat chatp;
						for (auto& chat : g_GlobalDataMgr->GlobalChatLog)
						{
							auto MsgInList = std::wstring(chat.msg);
							if (GlobalMsg == MsgInList)
							{
								//wprintf(L"before->text = %s-%s, index = %d, completed = %d\n", MsgInList.c_str(), GlobalMsg.c_str(), chat.index, chat.completed);
								if (!chat.completed)
								{
									chat.completed = true;
									chat.index = index;
									//wprintf(L"after->text = %s-%s, index = %d, completed = %d\n", MsgInList.c_str(), GlobalMsg.c_str(), chat.index, chat.completed);
									break;
								}
								else if (chat.completed)
								{
									if(index != 0)
										chatp.index = index;
									chatp.msg = GlobalMsg;
									chatp.completed = true;
									chatp.buffer = chat.buffer;
									inserted_new = true;
								}
							}
						}
						if (inserted_new)
							g_GlobalDataMgr->GlobalChatLog.push_back(chatp);
						//wprintf(L"ChatIndex[%d]:%s\n", index, GlobalMsg.c_str());
					}
				}
			}

			std::remove_if(g_GlobalDataMgr->GlobalChatLog.begin(), g_GlobalDataMgr->GlobalChatLog.end(), [](GlobalChat lhs) {
					return lhs.index < 0;
				});
		}
	}
	catch (std::exception& ex)
	{
	}
	catch (...)
	{
	}
}
extern HWND g_orig_wndproc_hwnd;
CIFSlotWithHelp* lastFoundEmptySlot;
auto LastEmptySlot = -1;
void GlobalItemLinking::OnIndexHovered(DWORD EDX, DWORD EBP)
{
	try
	{
		CIFChatWndCtrl* checker = 0;
		_asm mov checker, ebx;
		if (checker && checker->Instance == 0xD9E37C)
		{
			if (g_GlobalDataMgr->SelectedGameChatType == 0 && checker->pCIFChatViewer->selfPtr == 0xDBBA44)
			{
				if (g_GlobalDataMgr->SelectedGameChatType == 0)
				{
					std::wstring test = L"none";
					auto index_stack = EDX;
				//	printf("index stack = %d\n", index_stack);
					for (auto iter : g_GlobalDataMgr->GlobalChatLog)
					{
						//wprintf(L"[%d]amk yha : %d\n", iter.index, index_stack);
						if (iter.index == index_stack && iter.completed)
						{
							test = iter.msg;
							if (EBP == 1)
							{

								CIFSlotWithHelp* slot = (CIFSlotWithHelp*)g_CGInterface->field_36C.GetGUIObjectByID(99, 0);

								if (slot->pCSOItem == nullptr || slot->pCSOItem == 0)
								{
								//	wprintf(L"pCSOItem \n");

									CIFInventory* pInventory = g_CGInterface->GetMainPopup()->GetInventory();
									CIFSlotWithHelp* pEmptySlot = nullptr;
									bool isFound = false;
									for (int i = 0; i < 96; i++)
									{
										CIFSlotWithHelp* pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
										if (pSlot->pCSOItem == nullptr || pSlot->pCSOItem == 0)
										{
											pEmptySlot = pSlot;
											isFound = true;
											break;
										}
									}
								//	printf("ptr of Inventory = %02x - found an empty slot  slot ptr = %02x\n", pInventory, pEmptySlot);
									if (isFound && pEmptySlot && pEmptySlot->pCSOItem == nullptr)
									{
										lastFoundEmptySlot = pEmptySlot;
										LastEmptySlot = pEmptySlot->dwSlotID - 87;
										if (pEmptySlot->pCSOItem == nullptr && pEmptySlot->pCSOItem == 0)
										{
											pEmptySlot->bisVisible = false;
											CMsgStreamBuffer* pBuffer = new CMsgStreamBuffer(0xB034);
											pBuffer->Write<uint8_t>(0x01);
											pBuffer->Write<uint8_t>(0x06);
											pBuffer->Write<uint8_t>(LastEmptySlot);
											for (size_t i = 0; i < iter.buffer->GetLength(); ++i)
											{
												pBuffer->Write<uint8_t>(iter.buffer->Read<uint8_t>());
											}
											iter.buffer->Seek(0);
											//firstly get rid of the annoying message (we should hide it xd)
											g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0087C1F0), 2);
											*(BYTE*)(0x0087C1F0) = 0xEB;
											*(BYTE*)(0x0087C1F0 + 1) = 0x37;
											g_MemoryHelper->ReProtect();
											g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0087C15B), 1);
											*(BYTE*)(0x0087C15B) = 0x75;
											g_MemoryHelper->ReProtect();
											//first of all make a copy of original item
											pBuffer->SendToClient();
											//after giving the item, rollback the item gained msg so player will keep seeing it
											g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0087C1F0), 2);
											*(BYTE*)(0x0087C1F0) = 0x72;
											*(BYTE*)(0x0087C1F0 + 1) = 0x05;
											g_MemoryHelper->ReProtect();
											g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0087C15B), 1);
											*(BYTE*)(0x0087C15B) = 0x74;
											g_MemoryHelper->ReProtect();
											slot->pCSOItem = pEmptySlot->pCSOItem;
											pEmptySlot->bIconVisible = false;
											if (slot->pCSOItem)
											{
												if (slot->dwSlotType == 0)
												{
													slot->dwSlotType = 70;
													//slot->dwWidth = 1;
													//slot->dwHeight = 1;
												}
												slot->pCSOItem->ActiveShit = true;
												slot->UpdateLocation(g_Controler->cursorPosX + 25, g_Controler->cursorPosY);
												slot->MakeBubble();
											}
										}

									}
									else
									{
										g_CGInterface->SendGuideMsg(L"You need an empty slot in your inventory in order to get global item linking system enabled.", 0xFFFFFFFF);
										if (lastFoundEmptySlot && !lastFoundEmptySlot->bisVisible)
											lastFoundEmptySlot->bisVisible = true;
									}
								}
							}
							if (EBP == 0)
							{
								if (lastFoundEmptySlot && lastFoundEmptySlot->pCSOItem)
								{
									if (LastEmptySlot > 0)
									{
										CMsgStreamBuffer* pBuffer = new CMsgStreamBuffer(0xB034);
										pBuffer->Write<uint8_t>(1);
										pBuffer->Write<uint8_t>(7);
										pBuffer->Write<uint8_t>(LastEmptySlot);
										pBuffer->SendToClient();
										LastEmptySlot = 0;
									}
								}
								if (lastFoundEmptySlot && !lastFoundEmptySlot->bisVisible)
									lastFoundEmptySlot->bisVisible = true;
								CIFSlotWithHelp* slot = (CIFSlotWithHelp*)g_CGInterface->field_36C.GetGUIObjectByID(99, 0);
								if (slot)
								{
									slot->UpdateLocation(9999, 0);
									slot->ShowGWnd(false);
									if (slot->pCSOItem)
									{
										slot->bisVisible = false;
										slot->pCSOItem = nullptr;
										lastFoundEmptySlot->MakeBubble();
										lastFoundEmptySlot = nullptr;
									}
								}
								//printf("%02x\n", *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots));
								//printf("reloaded icon new location %d - %d\n", slot->XPos, slot->YPos);
							}

							/*wprintf(L"index = %d - IsFocused = %d\n", index_stack, EBP);
							wprintf(L"___________________________________________________\n");*/
							break;
						}
					}
				}
			}
		}
	}
	catch (const std::exception& ex)
	{

	}
	catch (...)
	{

	}
}
void GlobalItemLinking::Initialize()
{
	g_MemoryHelper->SetNop(cdwOnIndexChanged, 6);
	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwOnIndexChanged), ASM_OnIndexChanged);

	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwOnIndexHover), ASM_OnIndexHover);


	g_MemoryHelper->SetNop(cdwOnChatTypeChanged, 6);
	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwOnChatTypeChanged), ASM_OnChatTypeChanged);
	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwOnCIFEditWndProcHandleAddr), ASM_OnCIFEditWndProcHandle);
}