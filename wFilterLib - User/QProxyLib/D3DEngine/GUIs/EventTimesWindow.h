#ifndef Q_LIBRARY_TEST_WINDOW_H
#define Q_LIBRARY_TEST_WINDOW_H

#include "../D3DEngine.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

class EventTimesWindow :public Form
{
private:
	void InitializeComponent();
public:
	EventTimesWindow() : Form()
	{
		InitializeComponent();
	}
	void RefreshData(const int& page = 0);
	int8_t m_current_page = 1;
	Label* lbl_Pager;
};

#endif