#include "SplashScreen.h"
#include "../Helpers/CustomButton.h"
#include "../../../GameMain/GameMain.h"

extern Misc::RawDataContainer menu_pandora_bg;

void SplashScreen::InitializeComponent()
{
	this->SetCaptionBar(false);
	this->SetPanelEnabled(false);
	auto Sz = Application::Instance().GetRenderer().GetDisplaySize();
	this->SetLocation(Sz.Width - 308, Sz.Height - 152);

	this->SetSize(0, 0);
	CustomButton* shit = new CustomButton(Image::FromMemory(menu_pandora_bg));
	shit->SetEnabled(false);
	shit->SetLocation(0, 0);
	this->AddControl(shit);
}