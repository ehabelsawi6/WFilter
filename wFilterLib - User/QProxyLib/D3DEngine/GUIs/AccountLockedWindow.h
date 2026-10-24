#ifndef Q_LIBRARY_ACCOUNT_LOCKED_H
#define Q_LIBRARY_ACCOUNT_LOCKED_H
#include "../D3DEngine.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

class AccountLockedWindow :public Form
{
private:
	void InitializeComponent();
public:
	AccountLockedWindow() : Form()
	{
		InitializeComponent();
	}


	TextBox* tb_pinCode;
	TextBox* tb_pinCode2;
	CheckBox* rememberMe;
};

#endif