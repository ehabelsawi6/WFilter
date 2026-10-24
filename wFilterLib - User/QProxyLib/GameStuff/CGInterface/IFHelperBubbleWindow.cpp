#include "IFHelperBubbleWindow.h"
#include "../../GameMain/GameMain.h"


//void CIFHelperBubbleWindow::Write(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex)
//{
//    // Redirection to original client code
//    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, ForegroundColor, a4, FontIndex);
//}

void CIFHelperBubbleWindow::WriteLine(w_string_last& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex)
{
	reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, w_string_last*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, ForegroundColor, a4, FontIndex);
}