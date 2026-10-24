#ifndef Q_PANDORA_SPLASH_SCREEN_H
#define Q_PANDORA_SPLASH_SCREEN_H
#include "../../D3DEngine.h"
using namespace OSHGui;
using namespace OSHGui::Drawing;

class SplashScreen : public Form
{
private:
	void InitializeComponent();
protected:
	//virtual void PopulateGeometry() override;

public:
	SplashScreen() : Form()
	{
		InitializeComponent();
	}
};
#endif