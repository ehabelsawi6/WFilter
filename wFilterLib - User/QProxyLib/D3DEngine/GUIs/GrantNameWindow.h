#pragma once
#include "../../stdafx.h"
#include "../D3DEngine.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

class GrantNameWindow : public Form
{
private:
	void InitializeComponent();
public:
	GrantNameWindow() : Form()
	{
		InitializeComponent();
	}
	TextBox* tb_GrantName;

};