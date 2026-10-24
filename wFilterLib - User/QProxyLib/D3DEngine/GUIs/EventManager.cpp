#include "EventManager.h"
#include "Helpers/CustomButton.h"
#include "Helpers/CustomLabel.h"
#include "../../GameMain/GameMain.h"
//Event Manager
extern Misc::RawDataContainer bg_event_managerdata;

extern Misc::RawDataContainer btn_new_canceldata;
extern Misc::RawDataContainer btn_new_cancel_disableddata;
extern Misc::RawDataContainer btn_new_cancel_hoverdata;
extern Misc::RawDataContainer btn_new_cancel_pressdata;

extern Misc::RawDataContainer btn_new_registerdata;
extern Misc::RawDataContainer btn_new_register_disableddata;
extern Misc::RawDataContainer btn_new_register_hoverdata;
extern Misc::RawDataContainer btn_new_register_pressdata;

//Event Manager Buttons
extern Misc::RawDataContainer btn_lms_eventdata;
extern Misc::RawDataContainer btn_lms_event_hoverdata;
extern Misc::RawDataContainer btn_lms_event_pressdata;

extern Misc::RawDataContainer btn_crew_eventdata;
extern Misc::RawDataContainer btn_crew_event_hoverdata;
extern Misc::RawDataContainer btn_crew_event_pressdata;

extern Misc::RawDataContainer btn_survival_eventdata;
extern Misc::RawDataContainer btn_survival_event_hoverdata;
extern Misc::RawDataContainer btn_survival_event_pressdata;

extern Misc::RawDataContainer btn_perennial_eventdata;
extern Misc::RawDataContainer btn_perennial_event_hoverdata;
extern Misc::RawDataContainer btn_perennial_event_pressdata;

extern Misc::RawDataContainer btn_madness_eventdata;
extern Misc::RawDataContainer btn_madness_event_hoverdata;
extern Misc::RawDataContainer btn_madness_event_pressdata;

//Close Button
extern Misc::RawDataContainer main_menu_button_closedata;
extern Misc::RawDataContainer main_menu_button_close_hoverdata;
extern Misc::RawDataContainer main_menu_button_close_pressdata;

int g_selectedevent = 1;
void EventManagerWindow::InitializeComponent()
{
	g_selectedevent = 1;

	this->SetCaptionBar(false);
	this->SetPanelEnabled(false);
	this->SetSize(0, 0);
	auto default_location = Application::Instance().GetRenderer().GetDisplaySize();
	this->SetLocation((default_location.Width / 2) - (452/2), (default_location.Height / 2) - (244/2) - 100);

	PictureBox* bg_image = new PictureBox();
	bg_image->SetImage(Image::FromMemory(bg_event_managerdata));
	bg_image->SetSize(452, 244);
	this->AddControl(bg_image);

	CustomButton* btn_Close = new CustomButton(Image::FromMemory(main_menu_button_closedata), Image::FromMemory(main_menu_button_close_hoverdata), Image::FromMemory(main_menu_button_close_pressdata));
	btn_Close->SetLocation(420, 18);
	btn_Close->GetClickEvent() += ClickEventHandler([this](Control* sender) {
			this->Close();
		});
	this->AddControl(btn_Close);



	CustomLabel* lb_EventName = new CustomLabel();
	lb_EventName->SetLocation(110, 43);
	lb_EventName->SetText("Name:");
	lb_EventName->SetForeColor(Color::Yellow());
	this->AddControl(lb_EventName);

	CustomLabel* lb_EventArena = new CustomLabel();
	lb_EventArena->SetLocation(170, 43);
	lb_EventArena->SetText("Arena:");
	lb_EventArena->SetForeColor(Color::Yellow());
	this->AddControl(lb_EventArena);

	CustomLabel* lb_EventDesc = new CustomLabel();
	lb_EventDesc->SetText("Desc");
	lb_EventDesc->SetForeColor(Color::Gray());
	lb_EventDesc->SetLocation(90, 50);
	this->AddControl(lb_EventDesc);

	Label* lb_Reward = new Label();
	lb_Reward->SetText("0 Silks");
	lb_Reward->SetLocation(296, 230);
	this->AddControl(lb_Reward);

	int ctr = 0;
	for (auto& data : g_GlobalDataMgr->m_EventsData)
	{
		ctr++;
		if (ctr == 1)
		{
			g_selectedevent = data.ID;
			lb_EventName->SetText("Name:" + data.Name);
			lb_EventArena->SetText("Arena:" + data.AreaName);
			lb_EventDesc->SetText(data.Description);
			lb_Reward->SetText(std::to_string(data.Rewards) + " Silks");
			break;
		}
	}

	CustomButton* btn_Event1 = new CustomButton(Image::FromMemory(btn_lms_eventdata), Image::FromMemory(btn_lms_event_hoverdata), Image::FromMemory(btn_lms_event_pressdata));
	btn_Event1->SetLocation(11, 89);
	btn_Event1->GetClickEvent() += ClickEventHandler([lb_EventName, lb_EventArena, lb_EventDesc, lb_Reward](Control* sender) {
			int ctr = 0;
			for (auto& data : g_GlobalDataMgr->m_EventsData)
			{
				ctr++;
				if (ctr == 1)
				{
					g_selectedevent = data.ID;
					lb_EventName->SetText("Name:" + data.Name);
					lb_EventArena->SetText("Arena:" + data.AreaName);
					lb_EventDesc->SetText(data.Description);
					lb_Reward->SetText(std::to_string(data.Rewards) + " Silks");
					break;
				}
			}
		});
	this->AddControl(btn_Event1);

	CustomButton* btn_Event2 = new CustomButton(Image::FromMemory(btn_crew_eventdata), Image::FromMemory(btn_crew_event_hoverdata), Image::FromMemory(btn_crew_event_pressdata));
	btn_Event2->SetLocation(11, 118);
	btn_Event2->GetClickEvent() += ClickEventHandler([lb_EventName, lb_EventArena, lb_EventDesc, lb_Reward](Control* sender) {
		int ctr = 0;
		for (auto& data : g_GlobalDataMgr->m_EventsData)
		{
			ctr++;
			if (ctr == 2)
			{
				g_selectedevent = data.ID;
				lb_EventName->SetText("Name:" + data.Name);
				lb_EventArena->SetText("Arena:" + data.AreaName);
				lb_EventDesc->SetText(data.Description);
				lb_Reward->SetText(std::to_string(data.Rewards) + " Silks");
				break;
			}
		}
		});
	this->AddControl(btn_Event2);

	CustomButton* btn_Event3 = new CustomButton(Image::FromMemory(btn_survival_eventdata), Image::FromMemory(btn_survival_event_hoverdata), Image::FromMemory(btn_survival_event_pressdata));
	btn_Event3->SetLocation(11, 147);
	btn_Event3->GetClickEvent() += ClickEventHandler([lb_EventName, lb_EventArena, lb_EventDesc, lb_Reward](Control* sender) {
		int ctr = 0;
		for (auto& data : g_GlobalDataMgr->m_EventsData)
		{
			ctr++;
			if (ctr == 3)
			{
				g_selectedevent = data.ID;
				lb_EventName->SetText("Name:" + data.Name);
				lb_EventArena->SetText("Arena:" + data.AreaName);
				lb_EventDesc->SetText(data.Description);
				lb_Reward->SetText(std::to_string(data.Rewards) + " Silks");
				break;
			}
		}
		});
	this->AddControl(btn_Event3);

	CustomButton* btn_Event4 = new CustomButton(Image::FromMemory(btn_perennial_eventdata), Image::FromMemory(btn_perennial_event_hoverdata), Image::FromMemory(btn_perennial_event_pressdata));
	btn_Event4->SetLocation(11, 176);
	btn_Event4->GetClickEvent() += ClickEventHandler([lb_EventName, lb_EventArena, lb_EventDesc, lb_Reward](Control* sender) {
		int ctr = 0;
		for (auto& data : g_GlobalDataMgr->m_EventsData)
		{
			ctr++;
			if (ctr == 4)
			{
				g_selectedevent = data.ID;
				lb_EventName->SetText("Name:" + data.Name);
				lb_EventArena->SetText("Arena:" + data.AreaName);
				lb_EventDesc->SetText(data.Description);
				lb_Reward->SetText(std::to_string(data.Rewards) + " Silks");
				break;
			}
		}
		});
	this->AddControl(btn_Event4);

	CustomButton* btn_Event5 = new CustomButton(Image::FromMemory(btn_madness_eventdata), Image::FromMemory(btn_madness_event_hoverdata), Image::FromMemory(btn_madness_event_pressdata));
	btn_Event5->SetLocation(11, 205);
	btn_Event5->GetClickEvent() += ClickEventHandler([lb_EventName, lb_EventArena, lb_EventDesc, lb_Reward](Control* sender) {
		int ctr = 0;
		for (auto& data : g_GlobalDataMgr->m_EventsData)
		{
			ctr++;
			if (ctr == 5)
			{
				g_selectedevent = data.ID;
				lb_EventName->SetText("Name:" + data.Name);
				lb_EventArena->SetText("Arena:" + data.AreaName);
				lb_EventDesc->SetText(data.Description);
				lb_Reward->SetText(std::to_string(data.Rewards) + " Silks");
				break;
			}
		}
		});
	this->AddControl(btn_Event5); 

	CustomButton* btn_Register = new CustomButton(Image::FromMemory(btn_new_registerdata), Image::FromMemory(btn_new_register_hoverdata), Image::FromMemory(btn_new_register_pressdata));
	btn_Register->SetLocation(227.5f, 190);	
	btn_Register->GetClickEvent() += ClickEventHandler([&](Control* sender) {
			CMsgStreamBuffer* pBuffer = new CMsgStreamBuffer(0x1337);
			pBuffer->Write<int8_t>(0x87);
			pBuffer->Write<int>(g_selectedevent);
			pBuffer->SendToServer();
		});
	this->AddControl(btn_Register); 

	CustomButton* btn_Cancel = new CustomButton(Image::FromMemory(btn_new_canceldata), Image::FromMemory(btn_new_cancel_hoverdata), Image::FromMemory(btn_new_cancel_pressdata));
	btn_Cancel->SetLocation(327.5f, 190);
	btn_Cancel->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		CMsgStreamBuffer* pBuffer = new CMsgStreamBuffer(0x1337);
		pBuffer->Write<int8_t>(0x88);
		pBuffer->Write<int>(g_selectedevent);
		pBuffer->SendToServer();
		});
	this->AddControl(btn_Cancel);
}