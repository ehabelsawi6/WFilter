#ifndef Q_LIBRARY_ACCOUNT_LOCK_H
#define Q_LIBRARY_ACCOUNT_LOCK_H
#include "../D3DEngine.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

class AccountLockWindow :public Form
{
private:
	void InitializeComponent();
public:
	AccountLockWindow() : Form()
	{
		InitializeComponent();
	}

	TextBox* tb_pinCode;
	TextBox* tb_pinCode2;
};

#endif