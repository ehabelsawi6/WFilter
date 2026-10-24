#ifndef Q_LIBRARY_EVENT_MANAGER_H
#define Q_LIBRARY_EVENT_MANAGER_H
#include "../D3DEngine.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

class EventManagerWindow : public Form
{
private:
	void InitializeComponent();

public:
	EventManagerWindow() : Form()
	{
		InitializeComponent();
	}
};
#endif