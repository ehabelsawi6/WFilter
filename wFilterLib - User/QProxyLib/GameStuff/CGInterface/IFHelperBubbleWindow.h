#pragma once
#include "../../GameMain/GameMain.h"

class CIFHelperBubbleWindow
{
public:
	//void Write(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);

	void WriteLine(w_string_last& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);
};