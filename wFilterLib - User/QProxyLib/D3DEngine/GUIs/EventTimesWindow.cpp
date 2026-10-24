#include "EventTimesWindow.h"
#include "Helpers/CustomLabel.h"
#include "../../GameMain/GameMain.h"
#include "Helpers/CustomButton.h"

extern Misc::RawDataContainer event_times_bg;

extern Misc::RawDataContainer com_left_arrowdata;
extern Misc::RawDataContainer com_left_arrow_focusdata;
extern Misc::RawDataContainer com_left_arrow_pressdata;
extern Misc::RawDataContainer com_right_arrowdata;
extern Misc::RawDataContainer com_right_arrow_focusdata;
extern Misc::RawDataContainer com_right_arrow_pressdata;

int e_counter = 0;

void EventTimesWindow::InitializeComponent()
{
	e_counter = 0;

	CMsgStreamBuffer* eventTimesRequest = new CMsgStreamBuffer(MsgOpcodes::CLIENT_CUSTOM);
	eventTimesRequest->Write<uint8_t>(MsgOpcodeTypes::OnEventTimesRequest);
	eventTimesRequest->SendToServer();

	this->SetCaptionBar(true);
	this->SetPanelEnabled(false);
	this->SetSize(370, 410);
	this->SetText("Event Times");
	auto size = Application::Instance().GetRenderer().GetDisplaySize();
	this->SetLocation(((size.Width - this->GetSize().Width) / 2), ((size.Height - this->GetSize().Height)) / 2);

	

	PictureBox* bg_image = new PictureBox();
	bg_image->SetImage(Image::FromMemory(event_times_bg));
	bg_image->SetSize(350, 330);
	bg_image->SetLocation(3, 1);
	this->AddControl(bg_image);


	lbl_Pager = new Label();
	lbl_Pager->SetLocation(180, 340);
	lbl_Pager->SetText(std::to_string(this->m_current_page));
	this->AddControl(lbl_Pager);



	


	CustomButton* btn_Left = new CustomButton(Image::FromMemory(com_left_arrowdata), Image::FromMemory(com_left_arrow_focusdata), Image::FromMemory(com_left_arrow_pressdata));
	btn_Left->SetLocation(155, 340);
	btn_Left->GetClickEvent() += ClickEventHandler([this](Control* sender) {
		if (this->m_current_page > 1)
		{
			auto current_index = m_current_page * 9;
			auto limiter = current_index - 9;

			//printf("selected_page = %d - current_index = %d - limiter = %d\n", m_selected_page, current_index, limiter);
			if (limiter > 9)
			{
				RefreshData(limiter - 9);
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
	btn_Right->SetLocation(195, 340);
	btn_Right->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		auto next_begin_index = m_current_page * 9;
		if (next_begin_index < g_GlobalDataMgr->m_EventTimes.size())
		{
			this->m_current_page++;
			this->lbl_Pager->SetText(std::to_string(m_current_page));
		
			
			 if (m_current_page == 1)
				RefreshData(0);
			 else
				 RefreshData(next_begin_index + m_current_page -1 );

		}
		});
	this->AddControl(btn_Right);
}

void EventTimesWindow::RefreshData(const int& page)
{
	
	for (auto& ctrl : this->GetControls())
	{
		if (g_StringHelper->contains(ctrl->GetName(), "event"))
		{
			ctrl->SetName("");
			ctrl->SetEnabled(false);
			ctrl->SetVisible(false);
			this->RemoveControl(ctrl);
		}
	}

	auto eventName_font = FontManager::LoadFont("Tahoma", 7, false);
	auto eventTime_font = FontManager::LoadFont("Tahoma", 7, false);

	int limit = 9;
	int m_start_point = page;
	int base_y = 41;
//	int num = 0;

	if (m_start_point != 0)
	{
		int m_temp_counter = 0;
		int m_temp_limiter = 1;
		for (auto& data : g_GlobalDataMgr->m_EventTimes)
		{
			m_temp_counter++;
			if (m_temp_counter >= m_start_point && m_temp_limiter <= limit)
			{
				m_temp_limiter++;
				e_counter++;
				
				//event names
				Label* event_1 = new Label();
				event_1->SetText(data.second.Name);
				event_1->SetName("eventName" + std::to_string(e_counter));
				event_1->SetLocation(10, base_y);
				event_1->SetFont(eventName_font);

				this->AddControl(event_1);

				//event times
				Label* time_1 = new Label();
				time_1->SetText(data.second.Time);
				time_1->SetName("eventTime" + std::to_string(e_counter));
				time_1->SetLocation(147, event_1->GetLocation().Y);
				time_1->SetFont(eventTime_font);
				this->AddControl(time_1);

				base_y += 34;
			//	num++;
			}
			
		}
	}
	else
	{
		int m_temp_limiter = 1;
		for (auto& data : g_GlobalDataMgr->m_EventTimes)
		{
			if (m_temp_limiter <= limit)
			{
				e_counter++;
				
				//event names
				Label* event_1 = new Label();
				event_1->SetText(data.second.Name);
				event_1->SetName("eventName" + std::to_string(e_counter));
				event_1->SetLocation(10, base_y);
				event_1->SetFont(eventName_font);

				this->AddControl(event_1);

				//event times
				Label* time_1 = new Label();
				time_1->SetText(data.second.Time);
				time_1->SetName("eventTime" + std::to_string(e_counter));
				time_1->SetLocation(147, event_1->GetLocation().Y);
				time_1->SetFont(eventTime_font);
				this->AddControl(time_1);

				base_y += 34;
				//num++;

			}
			m_temp_limiter++;
		}
	}
}
