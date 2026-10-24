#include "GrantNameWindow.h"
#include "Helpers/CustomButton.h"
#include "../../GameStuff/CICPlayer/CICPlayer.h"
#include "../../GameStuff/CGInterface/CGInterface.h"
#include "../../GameStuff/CharacterDependentData/CharacterDependentData.h"

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
extern OSHGui::Misc::RawDataContainer custom_textbox_data;

// 
//Grant
extern OSHGui::Misc::RawDataContainer bg_custom_grantdata;
//Close Button
extern Misc::RawDataContainer main_menu_button_closedata;
extern Misc::RawDataContainer main_menu_button_close_hoverdata;
extern Misc::RawDataContainer main_menu_button_close_pressdata;

void GrantNameWindow::InitializeComponent()
{
	this->SetCaptionBar(true);
	this->SetPanelEnabled(false);
	this->SetText("Grant Name");
	this->SetSize(298, 149);

	auto size = Application::Instance().GetRenderer().GetDisplaySize();
	this->SetLocation(((size.Width - this->GetSize().Width) / 2), ((size.Height - this->GetSize().Height)) / 2);

	//SetCaptionBar(false);
	//SetSize(0, 0);
	//auto size = Application::Instance().GetRenderer().GetDisplaySize();
	//this->SetLocation((size.Width / 2) - (298 / 2), (size.Height / 2) - (115));

	/*PictureBox* CustomTitleBG = new PictureBox();
	CustomTitleBG->SetImage(Drawing::Image::FromMemory(bg_custom_grantdata));
	CustomTitleBG->SetSize(298, 149);
	CustomTitleBG->SetLocation(0, 0);
	this->AddControl(CustomTitleBG);*/

	//CustomButton* btn_Close = new CustomButton(Drawing::Image::FromMemory(main_menu_button_closedata), Drawing::Image::FromMemory(main_menu_button_close_hoverdata), Drawing::Image::FromMemory(main_menu_button_close_pressdata));
	//btn_Close->SetLocation(263, 12);
	//btn_Close->GetClickEvent() += ClickEventHandler([this](Control* sender) {
	//	this->Close();
	//	});
	//this->AddControl(btn_Close);

	Label* test = new Label();
	test->SetText("Enter the new Grant Name");
	test->SetLocation((((298 / 2) + 11) - (test->GetSize().Width / 2)) - CStringHelper::ws2s(g_CICPlayer->GetCharName()->c_str()).length(), 5);
	this->AddControl(test);

	PictureBox* GrantName_bg = new PictureBox();
	GrantName_bg->SetImage(Drawing::Image::FromMemory(custom_textbox_data));
	GrantName_bg->SetLocation(38, 34);
	GrantName_bg->SetSize(230, 30);
	GrantName_bg->SetStretch(true);
	this->AddControl(GrantName_bg);


	tb_GrantName = new TextBox();
	tb_GrantName->SetLocation(38, 34);
	tb_GrantName->SetSize(230, 30);
	tb_GrantName->SetMaxLength(20);
	this->AddControl(tb_GrantName);

	CustomButton* btn_Confirm = new CustomButton(Drawing::Image::FromMemory(com_button_data), Drawing::Image::FromMemory(com_button_hover_data), Drawing::Image::FromMemory(com_button_press_data));
	btn_Confirm->SetSize(77, 28);
	btn_Confirm->SetLocation(62, 74);
	btn_Confirm->SetText("Change");

	btn_Confirm->GetClickEvent() += ClickEventHandler([this](Control* sender) {
		if (!g_CCharacterDependentData.IsInGuild())
		{
			g_CGInterface->ShowMessage_PINK(L"Cannot proceed, because you don't have any guild.");
			return;
		}
		std::wstring str;
		auto grantName = tb_GrantName->GetText();
		if (grantName.length() <= 0 || grantName.empty())
		{
			str = L"The new grant name box can't be empty.";
			g_CGInterface->ShowMessage_PINK(str);
			return;
		}
		else if (grantName.length() > 12)
		{
			str = L"The new grant name cannot be longer than 12 characters.";
			g_CGInterface->ShowMessage_PINK(str);
			return;
		}
		else if (grantName.find("'") != std::string::npos || grantName.find("\\") != std::string::npos)
		{
			str = L"The new grant name cannot contains illegal characters. You only allowed to use A-Z ~ 0-9 Letters.";
			g_CGInterface->ShowMessage_PINK(str);
			return;
		}

		if (str.length() <= 0)
		{
			CMsgStreamBuffer* packet = new CMsgStreamBuffer(0x1337);
			packet->Write<uint8_t>(0x80);
			packet->WriteStringA(grantName.c_str());
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
