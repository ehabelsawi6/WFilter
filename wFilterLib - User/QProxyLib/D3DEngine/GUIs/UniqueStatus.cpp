#include "UniqueStatus.h"
#include "Helpers/CustomButton.h"
#include "../../GameMain/GameMain.h"
#include <chrono>
#include <ctime>


extern OSHGui::Misc::RawDataContainer unique_status_head_data;
extern Misc::RawDataContainer com_button_data;
extern Misc::RawDataContainer com_button_hover_data;
extern Misc::RawDataContainer com_button_press_data;

//Unique Status
extern Misc::RawDataContainer btn_reloaddata;
extern Misc::RawDataContainer btn_reload_hoverdata;
extern Misc::RawDataContainer btn_reload_pressdata;
extern Misc::RawDataContainer unique_status_bg;
 //extern Misc::RawDataContainer unique_status_head_data;

//Close Button
extern Misc::RawDataContainer main_menu_button_closedata;
extern Misc::RawDataContainer main_menu_button_close_hoverdata;
extern Misc::RawDataContainer main_menu_button_close_pressdata;
//Paginator
//extern Misc::RawDataContainer btn_paginator_leftdata;
//extern Misc::RawDataContainer btn_paginator_rightdata;
//extern Misc::RawDataContainer btn_paginator_left_hoverdata;
//extern Misc::RawDataContainer btn_paginator_left_pressdata;
//extern Misc::RawDataContainer btn_paginator_right_hoverdata;
//extern Misc::RawDataContainer btn_paginator_right_pressdata;

extern Misc::RawDataContainer com_left_arrowdata;
extern Misc::RawDataContainer com_left_arrow_focusdata;
extern Misc::RawDataContainer com_left_arrow_pressdata;
extern Misc::RawDataContainer com_right_arrowdata;
extern Misc::RawDataContainer com_right_arrow_focusdata;
extern Misc::RawDataContainer com_right_arrow_pressdata;


int g_counter = 0;
void UniqueStatusWindow::InitializeComponent()
{
	g_counter = 0;

	CMsgStreamBuffer* uniqueStatusRequest = new CMsgStreamBuffer(MsgOpcodes::CLIENT_CUSTOM);
	uniqueStatusRequest->Write<uint8_t>(MsgOpcodeTypes::UniqueStatusRequest);
	uniqueStatusRequest->SendToServer();


	this->SetCaptionBar(true);
	this->SetPanelEnabled(false);
	this->SetText("Unique Status");
	this->SetSize(387, 415);

	auto size = Application::Instance().GetRenderer().GetDisplaySize();
	this->SetLocation(((size.Width - this->GetSize().Width) / 2), ((size.Height - this->GetSize().Height)) / 2);

	/*this->SetCaptionBar(false);
	this->SetSize(0, 0);
	this->SetPanelEnabled(false);
	auto default_location = Application::Instance().GetRenderer().GetDisplaySize();
	this->SetLocation((default_location.Width / 2) - (367/2), (default_location.Height / 2) - (419/2) - 50);*/

	PictureBox* background_image = new PictureBox();
	background_image->SetImage(Image::FromMemory(unique_status_bg));
	background_image->SetSize(376, 373);
	background_image->SetLocation(0, -7);
	background_image->SetEnabled(true);
	background_image->SetStretch(true);

	this->AddControl(background_image);

	//CustomButton* btn_Close = new CustomButton(Image::FromMemory(main_menu_button_closedata), Image::FromMemory(main_menu_button_close_hoverdata), Image::FromMemory(main_menu_button_close_pressdata));
	//btn_Close->SetLocation(335, 20);
	//btn_Close->GetClickEvent() += ClickEventHandler([&](Control* control) {
	//	this->Close();
	//	});
	//this->AddControl(btn_Close);

	lbl_Pager = new Label();
	lbl_Pager->SetLocation(185, 350);
	lbl_Pager->SetText(std::to_string(this->m_current_page));
	this->AddControl(lbl_Pager);

	/*CustomButton* btn_Refresh = new CustomButton(Image::FromMemory(btn_reloaddata), Image::FromMemory(btn_reload_hoverdata), Image::FromMemory(btn_reload_pressdata));
	btn_Refresh->SetLocation(320, 394);
	btn_Refresh->GetClickEvent() += ClickEventHandler([&](Control* sender)
		{
			CMsgStreamBuffer* uniqueStatusRequest = new CMsgStreamBuffer(MsgOpcodes::CLIENT_CUSTOM);
			uniqueStatusRequest->Write<uint8_t>(MsgOpcodeTypes::UniqueStatusRequest);
			uniqueStatusRequest->SendToServer();
			this->m_current_page = 1;
			this->lbl_Pager->SetText(std::to_string(1));
		});*/
	//this->AddControl(btn_Refresh);

	CustomButton* btn_Left = new CustomButton(Image::FromMemory(com_left_arrowdata), Image::FromMemory(com_left_arrow_focusdata), Image::FromMemory(com_left_arrow_pressdata));
	btn_Left->SetLocation(160, 350);
	btn_Left->GetClickEvent() += ClickEventHandler([this](Control* sender) {
			if (this->m_current_page > 1)
			{
				auto current_index = m_current_page * 18;
				auto limiter = current_index - 18;

				//printf("selected_page = %d - current_index = %d - limiter = %d\n", m_selected_page, current_index, limiter);
				if (limiter > 18)
				{
					RefreshData(limiter - 18);
				}
				else
				{
					RefreshData(0);
				}

				this->m_current_page--;
				this->lbl_Pager->SetText(std::to_string(m_current_page));
			}
		});
	this->AddControl(btn_Left);

	CustomButton* btn_Right = new CustomButton(Image::FromMemory(com_right_arrowdata), Image::FromMemory(com_right_arrow_focusdata), Image::FromMemory(com_right_arrow_pressdata));
	btn_Right->SetLocation(200, 350);
	btn_Right->GetClickEvent() += ClickEventHandler([&](Control* sender) {
			auto next_begin_index = m_current_page * 18;
			if (next_begin_index < g_GlobalDataMgr->m_UniqueData.size())
			{
				this->m_current_page++;
				this->lbl_Pager->SetText(std::to_string(m_current_page));
				if (m_current_page == 2)
					RefreshData(next_begin_index + 1);
				else if (m_current_page != 2)
					RefreshData(next_begin_index);
			}
		});
	this->AddControl(btn_Right);
}

void UniqueStatusWindow::RefreshData(const int &page)
{
	for (auto& ctrl : this->GetControls())
	{
		if (g_StringHelper->contains(ctrl->GetName(), "unique"))
		{
			ctrl->SetName("");
			ctrl->SetEnabled(false);
			ctrl->SetVisible(false);
			this->RemoveControl(ctrl);
		}
	}

	auto Font = FontManager::LoadFont("Arial", 7.5f, false);

	int base_y = 17;
	int limit = 18;
	int m_start_point = page;
	if (m_start_point != 0)
	{
		int m_temp_counter = 0;
		int m_temp_limiter = 1;
		for (auto &data : g_GlobalDataMgr->m_UniqueData)
		{
			m_temp_counter++;
			if (m_temp_counter >= m_start_point && m_temp_limiter <= 18)
			{
				m_temp_limiter++;
				g_counter++;
				Label* lb_UniqueName = new Label();
				lb_UniqueName->SetText(g_StringHelper->ws2s(data.UniqueName) + data.szKillerName);
				lb_UniqueName->SetName("uniqueName" + std::to_string(g_counter));
				lb_UniqueName->SetLocation(1, base_y);
				if (data.bState)
					lb_UniqueName->SetForeColor(Color::FromARGB(255, 83, 255, 0));
				else
					lb_UniqueName->SetForeColor(Color::Gray());
				lb_UniqueName->SetFont(Font);
				this->AddControl(lb_UniqueName);

				Label* lb_State = new Label();
				lb_State->SetText(data.bState ? "Alive" : "Dead");
				lb_State->SetName("uniqueState" + std::to_string(g_counter));
				lb_State->SetLocation(224, base_y);
				if (data.bState)
					lb_State->SetForeColor(Color::FromARGB(255, 83, 255, 0));
				else
					lb_State->SetForeColor(Color::Gray());
				lb_State->SetFont(Font);
				this->AddControl(lb_State);


				Label* lb_Time = new Label();
				lb_Time->SetText(data.time);
				lb_Time->SetName("uniqueTime" + std::to_string(g_counter));
				lb_Time->SetLocation(270, base_y);
				if (data.bState)
					lb_Time->SetForeColor(Color::FromARGB(255, 83, 255, 0));
				else
					lb_Time->SetForeColor(Color::Gray());
				lb_Time->SetFont(Font);
				this->AddControl(lb_Time);


				base_y += 18;
			}
			
		}
	}
	else
	{
		int m_temp_limiter = 1;
		for (auto &data : g_GlobalDataMgr->m_UniqueData)
		{
			if (m_temp_limiter <= limit)
			{
				g_counter++;
				Label* lb_UniqueName = new Label();
				lb_UniqueName->SetText(g_StringHelper->ws2s(data.UniqueName) + data.szKillerName);
				lb_UniqueName->SetName("uniqueName" + std::to_string(g_counter));
				lb_UniqueName->SetLocation(1, base_y);
				if (data.bState)
					lb_UniqueName->SetForeColor(Color::FromARGB(255, 83, 255, 0));
				else
					lb_UniqueName->SetForeColor(Color::Gray());
				lb_UniqueName->SetFont(Font);
				this->AddControl(lb_UniqueName);

				Label* lb_State = new Label();
				lb_State->SetText(data.bState ? "Alive" : "Dead");
				lb_State->SetName("uniqueState" + std::to_string(g_counter));
				lb_State->SetLocation(224, base_y);
				if (data.bState)
					lb_State->SetForeColor(Color::FromARGB(255, 83, 255, 0));
				else
					lb_State->SetForeColor(Color::Gray());
				lb_State->SetFont(Font);
				this->AddControl(lb_State);


				Label* lb_Time = new Label();
				lb_Time->SetText(data.time);
				lb_Time->SetName("uniqueTime" + std::to_string(g_counter));
				lb_Time->SetLocation(270, base_y);
				if (data.bState)
					lb_Time->SetForeColor(Color::FromARGB(255, 83, 255, 0));
				else
					lb_Time->SetForeColor(Color::Gray());
				lb_Time->SetFont(Font);
				this->AddControl(lb_Time);


				base_y += 18;
			}
			m_temp_limiter++;
		}
	}
}
