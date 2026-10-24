#include "AccountLockWindow.h"
#include "Helpers/CustomButton.h"
#include "../../GameStuff/CGInterface/CGInterface.h"

extern Misc::RawDataContainer com_button_data;
extern Misc::RawDataContainer com_button_hover_data;
extern Misc::RawDataContainer com_button_press_data;

extern Misc::RawDataContainer AccountLocked_bg;
extern Misc::RawDataContainer AccountLock;

void AccountLockWindow::InitializeComponent()
{
	this->SetCaptionBar(true);
	this->SetPanelEnabled(false);
	this->SetSize(320, 200);
	this->SetText("Character Lock");
	auto size = Application::Instance().GetRenderer().GetDisplaySize();
	this->SetLocation(((size.Width - this->GetSize().Width) / 2), ((size.Height - this->GetSize().Height)) / 2);


	PictureBox* bg_image = new PictureBox();
	bg_image->SetImage(Image::FromMemory(AccountLock));
	bg_image->SetSize(300, 145);
	bg_image->SetLocation(3, 1);
	this->AddControl(bg_image);

	tb_pinCode = new TextBox();
	tb_pinCode->SetLocation(98, 40);
	tb_pinCode->SetSize(100, 30);
	tb_pinCode->SetMaxLength(4);
	tb_pinCode->NumbersOnly();
	tb_pinCode->SetPasswordChar('*');
	this->AddControl(tb_pinCode);

	tb_pinCode2 = new TextBox();
	tb_pinCode2->SetLocation(98, 70);
	tb_pinCode2->SetSize(100, 30);
	tb_pinCode2->SetMaxLength(4);
	tb_pinCode2->NumbersOnly();
	tb_pinCode2->SetPasswordChar('*');
	this->AddControl(tb_pinCode2);

	/*rememberMe = new CheckBox();
	rememberMe->SetLocation(192, 111);
	rememberMe->SetSize(10, 10);
	rememberMe->SetText(" Remember Me");
	this->AddControl(rememberMe);*/

	CustomButton* btn_unlock = new CustomButton(Image::FromMemory(com_button_data), Image::FromMemory(com_button_hover_data), Image::FromMemory(com_button_press_data));
	btn_unlock->SetText("Lock");
	btn_unlock->SetLocation(110, 106);
	btn_unlock->GetClickEvent() += ClickEventHandler([&](Control* sender) {

		std::wstring str;
		auto pinCode = tb_pinCode->GetText();
		auto pinCode2 = tb_pinCode2->GetText();

		if (pinCode.length() <= 0 || pinCode.empty() || pinCode2.length() <= 0 || pinCode2.empty())
		{
			str = L"The PIN Code can't be empty.";
			g_CGInterface->ShowMessage_PINK(str);
			return;
		}
		else if (pinCode.length() > 4 || pinCode.length() < 4 || pinCode2.length() > 4 || pinCode2.length() < 4)
		{
			str = L"The PIN Code cannot be longer or shorter than 4 numbers.";
			g_CGInterface->ShowMessage_PINK(str);
			return;
		}
		else if (pinCode != pinCode2) {
			str = L"The PIN Code isn't matching the confirm PIN Code.";
			g_CGInterface->ShowMessage_PINK(str);
			return;
		}

		CMsgStreamBuffer* packet = new CMsgStreamBuffer(0x1337);
		packet->Write<uint8_t>(0x64);
		packet->WriteStringA(pinCode.c_str());
		packet->SendToServer();
		this->Close();

		});
	this->AddControl(btn_unlock);

}
