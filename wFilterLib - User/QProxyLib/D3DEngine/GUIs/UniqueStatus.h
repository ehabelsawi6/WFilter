#ifndef Q_LIBRARY_UNIQUE_STATUS_H
#define Q_LIBRARY_UNIQUE_STATUS_H
#include "../D3DEngine.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

class UniqueStatusWindow : public Form
{
private:
	void InitializeComponent();
public:
	UniqueStatusWindow() : Form()
	{
		InitializeComponent();
	}
	void RefreshData(const int &page = 0);
	int8_t m_current_page = 1;
	Label* lbl_Pager;
};
#endif