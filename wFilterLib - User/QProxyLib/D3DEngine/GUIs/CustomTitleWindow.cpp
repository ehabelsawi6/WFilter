#include "CustomTitleWindow.h"
#include "../../GameMain/GameMain.h"
#include "../../GameStuff/CGInterface/CGInterface.h"

//extern OSHGui::Misc::RawDataContainer btn_custom_canceldata;
//extern OSHGui::Misc::RawDataContainer btn_custom_cancel_hoverdata;
//extern OSHGui::Misc::RawDataContainer btn_custom_cancel_pressdata;
//
//extern OSHGui::Misc::RawDataContainer btn_custom_changedata;
//extern OSHGui::Misc::RawDataContainer btn_custom_change_hoverdata;
//extern OSHGui::Misc::RawDataContainer btn_custom_change_pressdata;
// 

extern Misc::RawDataContainer com_button_disabled_data;
extern Misc::RawDataContainer com_button_data;
extern Misc::RawDataContainer com_button_hover_data;
extern Misc::RawDataContainer com_button_press_data;

//Title
extern OSHGui::Misc::RawDataContainer bg_custom_titledata;

extern OSHGui::Misc::RawDataContainer custom_textbox_data;

//Close Button
extern Misc::RawDataContainer main_menu_button_closedata;
extern Misc::RawDataContainer main_menu_button_close_hoverdata;
extern Misc::RawDataContainer main_menu_button_close_pressdata;

void CustomTitleWindow::InitializeComponent()
{
	this->SetCaptionBar(true);
	this->SetPanelEnabled(false);
	this->SetText("Custom Title");
	this->SetSize(298, 149);

	auto size = Application::Instance().GetRenderer().GetDisplaySize();
	this->SetLocation(((size.Width - this->GetSize().Width) / 2), ((size.Height - this->GetSize().Height)) / 2);

	/*SetCaptionBar(false);
	SetPanelEnabled(false);
	SetSize(0, 0);
	auto size = Application::Instance().GetRenderer().GetDisplaySize();
	this->SetLocation((size.Width / 2) - (298 / 2), (size.Height / 2) - (100));*/

	/*PictureBox* CustomTitleBG = new PictureBox();
	CustomTitleBG->SetImage(Drawing::Image::FromMemory(bg_custom_titledata));
	CustomTitleBG->SetSize(298, 149);
	CustomTitleBG->SetLocation(0,0);
	this->AddControl(CustomTitleBG);*/

	//CustomButton* btn_Close = new CustomButton(Drawing::Image::FromMemory(main_menu_button_closedata), Drawing::Image::FromMemory(main_menu_button_close_hoverdata), Drawing::Image::FromMemory(main_menu_button_close_pressdata));
	//btn_Close->SetLocation(263, 12);
	//btn_Close->GetClickEvent() += ClickEventHandler([this](Control* sender) {
	//		this->Close();
	//	});
	//this->AddControl(btn_Close);

	Label* myCreditsF = new Label();
	myCreditsF->SetText("Custom Title costs [ "+std::to_string(g_GlobalDataMgr->DShopCustomTitlePrice)+" ] DS-Points");
	myCreditsF->SetLocation((((this->GetSize().Width / 2) + 2) - (myCreditsF->GetSize().Width / 2)), 5);
	this->AddControl(myCreditsF);

	myCredits = new Label();
	myCredits->SetText(std::to_string(g_GlobalDataMgr->DShopCustomTitlePrice));
	myCredits->SetLocation(180, 5);
	myCredits->SetForeColor(Color::Yellow());
//	this->AddControl(myCredits);

	Label* test = new Label();
	test->SetText("Enter the new Title Name");
	test->SetLocation((((298 / 2) + 11) - (test->GetSize().Width / 2)) - CStringHelper::ws2s(g_CICPlayer->GetCharName()->c_str()).length(), 22);
	this->AddControl(test);


	PictureBox* CustomTitle_bg = new PictureBox();
	CustomTitle_bg->SetImage(Drawing::Image::FromMemory(custom_textbox_data));
	CustomTitle_bg->SetLocation(38, 44);
	CustomTitle_bg->SetSize(230, 30);
	CustomTitle_bg->SetStretch(true);
	this->AddControl(CustomTitle_bg);

	tb_CustomTitle = new TextBox();
	tb_CustomTitle->SetLocation(38, 44);
	tb_CustomTitle->SetSize(230, 30);
	tb_CustomTitle->SetMaxLength(50);
	this->AddControl(tb_CustomTitle);

	CustomButton* btn_Confirm;
	if (g_GlobalDataMgr->DSPoints >= g_GlobalDataMgr->DShopCustomTitlePrice)
		btn_Confirm = new CustomButton(Drawing::Image::FromMemory(com_button_data), Drawing::Image::FromMemory(com_button_hover_data), Drawing::Image::FromMemory(com_button_press_data));
	else
	{
		btn_Confirm = new CustomButton(Drawing::Image::FromMemory(com_button_disabled_data));
		btn_Confirm->SetEnabled(false);
	}

	btn_Confirm->SetSize(77, 28);
	btn_Confirm->SetLocation(62, 74);
	btn_Confirm->SetText("Change");
	btn_Confirm->GetClickEvent() += ClickEventHandler([this](Control* sender) {
		std::wstring str;
		auto titleName = this->tb_CustomTitle->GetText();
		if (titleName.length() <= 0 || titleName.empty())
		{
			str = L"The new Custom Title box can't be empty.";
			g_CGInterface->ShowMessage_PINK(str);
			return;
		}
		else if (titleName.length() > 50)
		{
			str = L"The new Custom Title cannot be longer than 50 characters.";
			g_CGInterface->ShowMessage_PINK(str);
			return;
		}
		else if (titleName.find("'") != std::string::npos || titleName.find("\\") != std::string::npos)
		{
			str = L"The new Custom Title cannot contain illegal characters.";
			g_CGInterface->ShowMessage_PINK(str);
			return;
		}

		if (str.length() <= 0)
		{ 
			CMsgStreamBuffer* packet = new CMsgStreamBuffer(0x1337);
			packet->Write<uint8_t>(0x81);
			packet->WriteStringA(titleName.c_str());
			packet->SendToServer();

			this->Close();
		}
		});
	this->AddControl(btn_Confirm);

	CustomButton* btn_Cancel = new CustomButton(Drawing::Image::FromMemory(com_button_data), Drawing::Image::FromMemory(com_button_hover_data), Drawing::Image::FromMemory(com_button_press_data));
	btn_Cancel->SetSize(80, 28);
	btn_Cancel->SetLocation(162, 74);
	btn_Cancel->SetText("Cancel");
	btn_Cancel->GetClickEvent() += ClickEventHandler([this](Control* sender) {
		this->Close();
		});
	this->AddControl(btn_Cancel);
}
