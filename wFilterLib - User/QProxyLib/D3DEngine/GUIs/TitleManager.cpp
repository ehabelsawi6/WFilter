#include "TitleManager.h"
#include "../GUIs/Helpers/CustomButton.h"
#include "../../GameStuff/CICPlayer/CICPlayer.h"
#include "../../GameMain/GameMain.h"

//Title Manager main stuff (designs)
extern Misc::RawDataContainer gui_title_manager_bgdata;
extern Misc::RawDataContainer com_button_use_title;
extern Misc::RawDataContainer com_button_use_title_hover;
extern Misc::RawDataContainer com_button_use_title_press;
//Remove button
extern Misc::RawDataContainer com_button_disabled_data;
extern Misc::RawDataContainer com_button_data;
extern Misc::RawDataContainer com_button_hover_data;
extern Misc::RawDataContainer com_button_press_data;

void TitleManagerWindow::UpdateCurrentTitle()
{
	Graphics g(*geometry_);
	auto cTitle_loc = g.MeasureString(lb_CurrentTitle->GetText(), lb_CurrentTitle->GetFont());
	lb_CurrentTitle->SetLocation(231 - (cTitle_loc.Width / 2), 35);
	if (lb_CurrentTitle->GetText() != "<No Title>")
	{
		//Color
		uint32_t DefaultHwanColor = 0xFFFFE65B;
		uint8_t red = (DefaultHwanColor & 0x00FF0000) >> 16;
		uint8_t green = (DefaultHwanColor & 0x0000FF00) >> 8;
		uint8_t blue = (DefaultHwanColor & 0x000000FF);
		lb_CurrentTitle->SetForeColor(Color::FromARGB(255, red, green, blue));
	}
}
void TitleManagerWindow::InitializeComponent()
{
	Graphics g(*geometry_);

	this->SetCaptionBar(true);
	this->SetPanelEnabled(false);
	this->SetText("Title Manager");
	this->SetSize(480, 374);

	CustomButton* titlemanager_bg = new CustomButton(Image::FromMemory(gui_title_manager_bgdata));
	titlemanager_bg->SetLocation(10, 2);
	titlemanager_bg->SetSize(446, 312);
	titlemanager_bg->SetEnabled(false);
	this->AddControl(titlemanager_bg);


	ScrollBar* useless_scroll_bar = new ScrollBar();
	useless_scroll_bar->SetSize(16, 200);
	useless_scroll_bar->SetLocation(435, 79);
	AddControl(useless_scroll_bar);

	CustomButton* button_remove_title = new CustomButton(Drawing::Image::FromMemory(com_button_data), Drawing::Image::FromMemory(com_button_hover_data), Drawing::Image::FromMemory(com_button_press_data));
	button_remove_title->SetLocation(374, 30);
	button_remove_title->SetSize(76, 24);
	button_remove_title->SetText("Remove");
	button_remove_title->GetClickEvent() += ClickEventHandler([&](Control* sender)
		{
			if (lb_CurrentTitle->GetText() != "<No Title>")
			{
				CMsgStreamBuffer* pBuffer = new CMsgStreamBuffer(MsgOpcodes::CLIENT_CUSTOM);
				pBuffer->Write<uint8_t>(MsgOpcodeTypes::TitlesListRemoveRequest);
				pBuffer->SendToServer();
				this->lb_CurrentTitle->SetText("<No Title>");
				UpdateCurrentTitle();
			}
		});
	this->AddControl(button_remove_title);

	CustomButton* button_use_title = new CustomButton(Image::FromMemory(com_button_use_title), Image::FromMemory(com_button_use_title_hover), Image::FromMemory(com_button_use_title_press));
	button_use_title->SetLocation(255, 279);
	button_use_title->SetSize(182, 24);
	button_use_title->GetClickEvent() += ClickEventHandler([&](Control* sender)
		{
			auto ItemText = lb_TitlesList->GetSelectedItem()->GetItemText();
			if (!ItemText.empty() && ItemText != "<No Title>")
			{
				const auto hwanLevel = g_GlobalDataMgr->GetHwanLevelByString(ItemText);
				CMsgStreamBuffer* pBuffer = new CMsgStreamBuffer(MsgOpcodes::CLIENT_CUSTOM);
				pBuffer->Write<uint8_t>(MsgOpcodeTypes::TitlesListChangeRequest);
				pBuffer->Write<uint8_t>(hwanLevel);
				pBuffer->SendToServer();

				auto selectedTitleText = g_GlobalDataMgr->GetHwanStringByLevel(hwanLevel);
				lb_CurrentTitle->SetText("<" + selectedTitleText + ">");
				UpdateCurrentTitle();
			}
		});
	button_use_title->SetText("Use Title");
	this->AddControl(button_use_title);

	lb_CurrentTitle = new Label();
	lb_CurrentTitle->SetLocation(231, 35);
	lb_CurrentTitle->SetText("<No Title>");
	std::string current_title;
	if (g_CICPlayer)
	{
		current_title = g_CGlobalDataManager->GetHwanStringByLevel(g_CICPlayer->GetHwanLevel());
	}
	if (!current_title.empty())
	{
		lb_CurrentTitle->SetText("<" + current_title + ">");
	}
	UpdateCurrentTitle();

	this->AddControl(lb_CurrentTitle);

	lb_TitlesList = new TitleListBox();
	lb_TitlesList->SetLocation(13, 79);
	lb_TitlesList->SetSize(235, 232);
	lb_TitlesList->SetAutoScrollEnabled(true);
	lb_TitlesList->GetMouseUpEvent() += MouseUpEventHandler([&](Control* sender, OSHGui::MouseEventArgs args){
		auto ItemText = lb_TitlesList->GetSelectedItem()->GetItemText();
		if (!ItemText.empty() && ItemText != "<No Title>")
		{
			lb_TitleName->SetText("<"+ItemText+">");
		}
	});
	this->AddControl(lb_TitlesList);
	auto titlesListSize = g_GlobalDataMgr->m_CurrentTitlesList.size();
	if (titlesListSize != 0)
	{
		for (const auto hwanLevel : g_GlobalDataMgr->m_CurrentTitlesList)
		{
			if (!hwanLevel.second.empty())
				this->lb_TitlesList->AddItem(hwanLevel.second);
		}
	}
	if(titlesListSize < 7)
	{
		for (size_t i = 0; i <= (7-titlesListSize); i++)
		{
			lb_TitlesList->AddItem("<No Title>");
		}
	}
	lb_TitlesList->SetSelectedIndex(0);


	Label* lb_Description = new Label();
	lb_Description->SetText("When <Use Title> button is-");
	lb_Description->SetLocation(263, 85);

	AddControl(lb_Description);

	Label* lb_Description1 = new Label();
	lb_Description1->SetText("clicked, Your title will be-");
	lb_Description1->SetLocation(263, 106);

	AddControl(lb_Description1);

	lb_TitleName = new Label();
	lb_TitleName->SetText("<Not Selected>");
	lb_TitleName->SetLocation(263, 127);

	AddControl(lb_TitleName);
}