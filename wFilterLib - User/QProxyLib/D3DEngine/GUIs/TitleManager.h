#ifndef Q_GUI_TITLE_MANAGER_H
#define Q_GUI_TITLE_MANAGER_H
#include "../D3DEngine.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

class TitleManagerWindow : public Form
{
private:
	void InitializeComponent();
	TitleListBox* lb_TitlesList;
	Label* lb_CurrentTitle;
	Label* lb_TitleName;
	void UpdateCurrentTitle();
public:
	TitleManagerWindow() : Form()
	{
		InitializeComponent();
	}
};
#endif