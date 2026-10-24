#pragma once
#ifndef Q_UI_ICNWINDOW_H
#define Q_UI_ICNWINDOW_H
#include "../../stdafx.h"
#include "../D3DEngine.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

class IconWindow : public Form
{
private:
	void InitializeComponent();
protected:
	//virtual void PopulateGeometry() override;

public:
	IconWindow() : Form()
	{
		InitializeComponent();
	}
};
#endif // !Q_UI_ICNWINDOW_H