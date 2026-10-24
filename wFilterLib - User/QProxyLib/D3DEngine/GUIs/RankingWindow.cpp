#include "RankingWindow.h"
#include "Helpers/CustomButton.h"
#include "../../GameMain/GameMain.h"
#include "../../GameStuff/CICPlayer/CICPlayer.h"
#include <chrono>
#include <ctime>
//Custom Frame
extern Misc::RawDataContainer bg_top_image_bgdata;
extern Misc::RawDataContainer top_image_close_button;
extern Misc::RawDataContainer top_image_close_button_hover;
extern Misc::RawDataContainer top_image_close_button_press;

void RankingWindow::InitializeComponent()
{
	this->SetPanelEnabled(false);
	this->SetCaptionBar(false);
	this->SetSize(0, 0);
	auto loc = Application::Instance().GetRenderer().GetDisplaySize();
	int X = (loc.Width / 2) - (800 / 2);
	int Y = (loc.Height / 2) - (570 / 2);
	this->SetLocation((X + 800) - 263, Y - 73);
	PictureBox* top_bg_image = new PictureBox();
	top_bg_image->SetImage(Image::FromMemory(bg_top_image_bgdata));
	top_bg_image->SetSize(256, 32);
	top_bg_image->SetLocation(0,0);
	this->AddControl(top_bg_image);
	CustomButton* btn_Close = new CustomButton(Image::FromMemory(top_image_close_button), Image::FromMemory(top_image_close_button_hover), Image::FromMemory(top_image_close_button_press));
	btn_Close->SetSize(28, 32);
	btn_Close->SetLocation(219, 2);
	btn_Close->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		this->Close();
		});
	this->AddControl(btn_Close);
	m_Web = new SilkroadWeb();
	m_Web->Start(X, Y, 800, 570, VMProtectDecryptStringA("https://mars.playxeon.com/ranking/top-player.html"));
}