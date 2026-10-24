#ifndef Q_GUI_KILL_COUNTER_MANAGER_H
#define Q_GUI_KILL_COUNTER_MANAGER_H
#include "../D3DEngine.h"
#include "../../Network/MsgStreamBuffer.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

class Top5KillCounterWindow : public Form
{
private:
	void InitializeComponent();
	PictureBox* dpsMeter_bg;
public:
	Top5KillCounterWindow() : Form()
	{
		InitializeComponent();
	}
	void Start(CMsgStreamBuffer* &packet);
};
#endif