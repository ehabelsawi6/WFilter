#pragma once
#include "Helpers/CustomButton.h"
using namespace OSHGui;
using namespace OSHGui::Drawing;
class CustomTitleWindow : public Form
{
private:
	void InitializeComponent();
protected:
public:
	TextBox* tb_CustomTitle;
	Label* myCredits;
	CustomTitleWindow() : Form()
	{
		InitializeComponent();
	};
};