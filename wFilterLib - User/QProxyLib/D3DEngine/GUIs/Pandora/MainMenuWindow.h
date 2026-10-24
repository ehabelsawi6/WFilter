#ifndef Q_LIBRARY_MAIN_MENU_H
#define Q_LIBRARY_MAIN_MENU_H
#include "../../D3DEngine.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

class MainMenuWindow : public Form
{
private:
	void InitializeComponent();
public:
	MainMenuWindow() : Form()
	{
		InitializeComponent();
	}
};
#endif