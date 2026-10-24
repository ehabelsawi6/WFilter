#ifndef Q_GUI_DPS_METER_MANAGER_H
#define Q_GUI_DPS_METER_MANAGER_H
#include "../D3DEngine.h"
#include "../../Network/MsgStreamBuffer.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

class DPSMeterWindow : public Form
{
private:
	void InitializeComponent();
	PictureBox* dpsMeter_bg;
public:
	DPSMeterWindow() : Form()
	{
		InitializeComponent();
	}
	void Start(CMsgStreamBuffer* &packet);
};
#endif