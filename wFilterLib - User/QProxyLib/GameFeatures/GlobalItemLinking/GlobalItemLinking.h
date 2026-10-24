#ifndef Q_LIBRARY_GLOBAL_ITEM_LINKING_H
#define Q_LIBRARY_GLOBAL_ITEM_LINKING_H
#include "../../stdafx.h"
#include "../../Helpers/CStringHelper.h"
class CInstanceEdit
{
private:
	DWORD SelfPtr;
public:
	DWORD GetPtr()
	{
		return this->SelfPtr;
	}
};
class CIFEdit
{
private:
	char pad_0000[48]; //0x0000
	CInstanceEdit* pInstanceEdit; //0x0030
	char pad_0034[356]; //0x0034
	w_string_last m_innerText; //0x01AC
	char pad_01B0[584]; //0x01B0
	uint32_t m_TextAreaSize; //0x03FC
	char pad_0400[68]; //0x0400
	uint32_t m_CurrentIndex; //0x0448
	char pad_044C[996]; //0x044C

public:
	bool SetText(const wchar_t* src);
	const wchar_t* GetText();
	CInstanceEdit* GetInstance()
	{
		return this->pInstanceEdit;
	}
	uint32_t GetAreaSize()
	{
		return this->m_TextAreaSize;
	}
	uint32_t GetCurrentIndex()
	{
		return this->m_CurrentIndex;
	}
	void SetCurrentIndex(uint32_t Index)
	{
		this->m_CurrentIndex = Index;
	}
	void SetTextAreaSize(uint32_t Size)
	{
		this->m_TextAreaSize = Size;
	}
};
class CIFWholeChat
{
public:
	char _pad_to_CIFEdit[0x7B8];
	CIFEdit* pCIFEdit;
};

class CIFChatViewer
{
public:
	DWORD selfPtr;
};
class CIFChatWndCtrl
{
public:
	char pad_0000[56]; //0x0000
	uint32_t Instance; //0x0038
	char pad_003C[44]; //0x003C
	CIFChatViewer* pCIFChatViewer; //0x0068
	char pad_006C[980]; //0x006C
}; //Size: 0x0440

class GlobalItemLinking
{
public:
	void Initialize();
	void FUN_00636cd0(CIFEdit* pCIFEdit);
	void AppendTextToChatBox(w_string_last* text);
	void OnIndexHovered(const DWORD EDX, const DWORD EBP);

private:

};
#endif