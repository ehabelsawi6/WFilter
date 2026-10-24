#include "ChestWindow.h"
#include "Helpers/CustomButton.h"
#include "../../GameMain/GameMain.h"
#include "../../GameStuff/CGInterface/CGInterface.h"

extern Misc::RawDataContainer menu_chest_button_take_hover;
extern Misc::RawDataContainer menu_chest_button_take_normal;
extern Misc::RawDataContainer menu_chest_button_take_press;
extern Misc::RawDataContainer menu_chest_content;
extern Misc::RawDataContainer menu_chest_items_tab;
extern Misc::RawDataContainer menu_chest_item_take;
extern Misc::RawDataContainer menu_chest_item_take_hover;
extern Misc::RawDataContainer menu_chest_item_take_press;


//
extern Misc::RawDataContainer com_left_arrowdata;
extern Misc::RawDataContainer com_left_arrow_disabledata;
extern Misc::RawDataContainer com_left_arrow_focusdata;
extern Misc::RawDataContainer com_left_arrow_pressdata;
extern Misc::RawDataContainer com_right_arrowdata;
extern Misc::RawDataContainer com_right_arrow_disabledata;
extern Misc::RawDataContainer com_right_arrow_focusdata;
extern Misc::RawDataContainer com_right_arrow_pressdata;
extern Misc::RawDataContainer paginator_bgdata;
void ChestWindow::UpdatePagination()
{
	Graphics g(*geometry_);
	auto r_loc = g.MeasureString(paginator_text->GetText(), paginator_text->GetFont());
	paginator_text->SetLocation(329 - (r_loc.Width / 2), 337);
}
void ChestWindow::UpdateRemainingInventory()
{
	Graphics g(*geometry_);
	content_remaining_inventory->SetText(std::to_string(g_CGlobalDataManager->GetEmptyInventorySlots()));
	auto r_loc = g.MeasureString(content_remaining_inventory->GetText(), content_remaining_inventory->GetFont());
	content_remaining_inventory->SetLocation(217 - (r_loc.Width / 2), 340);
}
void ChestWindow::OnRecvData(CMsgStreamBuffer* packet)
{
	uint16_t ItemCount = packet->Read<uint16_t>();
	for (uint16_t i = 0; i < ItemCount; i++)
	{
		ItemData item;
		item.Index = packet->Read<uint32_t>();
		item.ItemID = packet->Read<uint32_t>();
		auto itmData = g_CGlobalDataManager->GetGenericObjectDataByID(item.ItemID);
		item.Name = g_StringHelper->ws2s(g_CGlobalDataManager->GetObjectName(itmData));
		item.Quantity = packet->Read<uint16_t>();
		item.Date = packet->ReadStringA();
		item.Type = packet->ReadStringA();
		this->m_items.push_back(item);
	}
	this->RefreshItemsList();
}

void ChestWindow::OnRemoveData(uint32_t index)
{
	for (auto it = this->m_items.begin(); it != this->m_items.end();)
	{
		if (it->Index == index)
		{
			it = this->m_items.erase(it);
			break;
		}
		else it++;
	}

	for each (auto ctrl in this->GetControls())
	{
		if (g_StringHelper->contains(ctrl->GetName(), "chest_temporary"))
		{
			//printf("found %s\n", ctrl->GetName().c_str());
			ctrl->SetName("");
			ctrl->SetEnabled(false);
			ctrl->SetVisible(false);
			this->RemoveControl(ctrl);
		}
	}
	if (m_selected_page > 1)
	{
		auto current_index = m_selected_page * 12;
		if (current_index >= m_items.size())
		{
			current_index -= 12;
			RefreshItemsList(current_index);
		}
		else
			RefreshItemsList(current_index);
	}
	else
		RefreshItemsList();
	UpdateRemainingInventory();
}

void ChestWindow::OnTakeBtnClicked(uint32_t index)
{
	auto remainingSlots = g_CGlobalDataManager->GetEmptyInventorySlots();
	if (remainingSlots != 0)
	{
		//printf("trying to take number %d\n", index);
		CMsgStreamBuffer* request_packet = new CMsgStreamBuffer(MsgOpcodes::CLIENT_CUSTOM);
		request_packet->Write<uint8_t>(MsgOpcodeTypes::Chest_RequestItem);
		request_packet->Write<uint32_t>(index);
		request_packet->SendToServer();
	}
	else
		g_CGInterface->ShowMessage_BLUE(L"Cannot proceed because your Inventory is full.");
	//OnRemoveData(index);
}
void ChestWindow::RefreshItemsList(int begin_from)
{
	int base_y = 48;
	for each (auto ctrl in this->GetControls())
	{
		if (g_StringHelper->contains(ctrl->GetName(), "chest_temporary"))
		{
			//printf("found %s\n", ctrl->GetName().c_str());
			ctrl->SetName("");
			ctrl->SetEnabled(false);
			ctrl->SetVisible(false);
			this->RemoveControl(ctrl);
		}
	}
	auto base_font = FontManager::LoadFont("Tahoma", 9, false);
	Graphics g(*geometry_);
	if (begin_from != 0)
	{
		int m_temp_counter = 0;
		int m_temp_limiter = 1;
		for (auto Item = this->m_items.begin(); Item != this->m_items.end(); Item++)
		{
			m_temp_counter++;
			if (m_temp_counter >= begin_from && m_temp_limiter <= 12)
			{
				m_temp_limiter++;
				Label* lb_No = new Label();
				lb_No->SetText(std::to_string(Item->Index));
				lb_No->SetName("chest_temporary_no" + std::to_string(Item->Index));
				lb_No->SetFont(base_font);
				auto lb_loc = g.MeasureString(lb_No->GetText(), lb_No->GetFont());
				lb_No->SetLocation(25 - (lb_loc.Width / 2), base_y);
				this->AddControl(lb_No);

				Label* lb_Name = new Label();
				lb_Name->SetText(Item->Name);
				lb_Name->SetName("chest_temporary_name" + std::to_string(Item->Index));
				lb_Name->SetFont(base_font);
				auto lb_Nameloc = g.MeasureString(lb_Name->GetText(), lb_Name->GetFont());
				lb_Name->SetLocation(120 - (lb_Nameloc.Width / 2), base_y);
				this->AddControl(lb_Name);

				Label* lb_Qty = new Label();
				lb_Qty->SetText(std::to_string(Item->Quantity));
				lb_Qty->SetName("chest_temporary_qty" + std::to_string(Item->Index));
				lb_Qty->SetFont(base_font);
				auto lb_Qtyloc = g.MeasureString(lb_Qty->GetText(), lb_Qty->GetFont());
				lb_Qty->SetLocation(243 - (lb_Qtyloc.Width / 2), base_y);
				this->AddControl(lb_Qty);

				Label* lb_Date = new Label();
				lb_Date->SetText(Item->Date);
				lb_Date->SetName("chest_temporary_date" + std::to_string(Item->Index));
				lb_Date->SetFont(base_font);
				auto lb_Dateloc = g.MeasureString(lb_Date->GetText(), lb_Date->GetFont());
				lb_Date->SetLocation(326 - (lb_Dateloc.Width / 2), base_y);
				this->AddControl(lb_Date);

				Label* lb_Type = new Label();
				lb_Type->SetText(Item->Type);
				lb_Type->SetName("chest_temporary_type" + std::to_string(Item->Index));
				lb_Type->SetFont(base_font);
				auto lb_Typeloc = g.MeasureString(lb_Type->GetText(), lb_Type->GetFont());
				lb_Type->SetLocation(427 - (lb_Typeloc.Width / 2), base_y);
				this->AddControl(lb_Type);

				CustomButton* btn_Take = new CustomButton(Image::FromMemory(menu_chest_item_take), Image::FromMemory(menu_chest_item_take_hover), Image::FromMemory(menu_chest_item_take_press));
				btn_Take->SetLocation(510, base_y);
				btn_Take->SetName("chest_temporary_take" + std::to_string(Item->Index));
				btn_Take->GetClickEvent() += ClickEventHandler([&, Item, this](Control* sender) {
					this->OnTakeBtnClicked(Item->Index);
					});
				this->AddControl(btn_Take);

				base_y += 21;
			}
		}

	}
	else
	{
		int m_temp_limiter = 1;
		for (const auto Item : this->m_items)
		{
			if (m_temp_limiter <= 12)
			{
				m_temp_limiter++;
				Label* lb_No = new Label();
				lb_No->SetText(std::to_string(Item.Index));
				lb_No->SetName("chest_temporary_no" + std::to_string(Item.Index));
				lb_No->SetFont(base_font);
				auto lb_loc = g.MeasureString(lb_No->GetText(), lb_No->GetFont());
				lb_No->SetLocation(25 - (lb_loc.Width / 2), base_y);
				this->AddControl(lb_No);

				Label* lb_Name = new Label();
				lb_Name->SetText(Item.Name);
				lb_Name->SetName("chest_temporary_name" + std::to_string(Item.Index));
				lb_Name->SetFont(base_font);
				auto lb_Nameloc = g.MeasureString(lb_Name->GetText(), lb_Name->GetFont());
				lb_Name->SetLocation(120 - (lb_Nameloc.Width / 2), base_y);
				this->AddControl(lb_Name);

				Label* lb_Qty = new Label();
				lb_Qty->SetText(std::to_string(Item.Quantity));
				lb_Qty->SetName("chest_temporary_qty" + std::to_string(Item.Index));
				lb_Qty->SetFont(base_font);
				auto lb_Qtyloc = g.MeasureString(lb_Qty->GetText(), lb_Qty->GetFont());
				lb_Qty->SetLocation(243 - (lb_Qtyloc.Width / 2), base_y);
				this->AddControl(lb_Qty);

				Label* lb_Date = new Label();
				lb_Date->SetText(Item.Date);
				lb_Date->SetName("chest_temporary_date" + std::to_string(Item.Index));
				lb_Date->SetFont(base_font);
				auto lb_Dateloc = g.MeasureString(lb_Date->GetText(), lb_Date->GetFont());
				lb_Date->SetLocation(326 - (lb_Dateloc.Width / 2), base_y);
				this->AddControl(lb_Date);

				Label* lb_Type = new Label();
				lb_Type->SetText(Item.Type);
				lb_Type->SetName("chest_temporary_type" + std::to_string(Item.Index));
				lb_Type->SetFont(base_font);
				auto lb_Typeloc = g.MeasureString(lb_Type->GetText(), lb_Type->GetFont());
				lb_Type->SetLocation(427 - (lb_Typeloc.Width / 2), base_y);
				this->AddControl(lb_Type);

				CustomButton* btn_Take = new CustomButton(Image::FromMemory(menu_chest_item_take), Image::FromMemory(menu_chest_item_take_hover), Image::FromMemory(menu_chest_item_take_press));
				btn_Take->SetLocation(510, base_y);
				btn_Take->SetName("chest_temporary_take" + std::to_string(Item.Index));
				btn_Take->GetClickEvent() += ClickEventHandler([&, Item, this](Control* sender) {
					this->OnTakeBtnClicked(Item.Index);
					});
				this->AddControl(btn_Take);

				base_y += 21;
			}
		}
	}
}
void ChestWindow::InitializeComponent()
{
	this->SetCaptionBar(true);
	this->SetPanelEnabled(false);
	this->SetSize(626, 417);
	this->SetText("Item Storage Box");

	auto size = Application::Instance().GetRenderer().GetDisplaySize();
	this->m_offset = 0;
	this->SetLocation(((size.Width - this->GetSize().Width) / 2), ((size.Height - this->GetSize().Height)) / 2);
	Graphics g(*geometry_);
	CustomButton* items_tab_btn = new CustomButton(Image::FromMemory(menu_chest_items_tab));
	items_tab_btn->SetLocation(14, -7);
	items_tab_btn->SetEnabled(false);
	this->AddControl(items_tab_btn);

	CustomButton* items_content_bg = new CustomButton(Image::FromMemory(menu_chest_content));
	items_content_bg->SetLocation(1, 15);
	items_content_bg->SetEnabled(false);
	this->AddControl(items_content_bg);

	content_remaining_inventory = new Label();
	content_remaining_inventory->SetText("0");
	auto r_loc = g.MeasureString(content_remaining_inventory->GetText(), content_remaining_inventory->GetFont());
	content_remaining_inventory->SetLocation(217 - (r_loc.Width / 2), 340);
	content_remaining_inventory->SetEnabled(false);
	content_remaining_inventory->SetFont(FontManager::LoadFont("Arial", 9, false));
	this->AddControl(content_remaining_inventory);

	CustomButton* take_all_btn = new CustomButton(Image::FromMemory(menu_chest_button_take_normal),
		Image::FromMemory(menu_chest_button_take_hover), Image::FromMemory(menu_chest_button_take_press));
	take_all_btn->SetLocation(495, 322);
	take_all_btn->GetClickEvent() += ClickEventHandler([this](Control* sender) {
		auto remainingSlots = g_CGlobalDataManager->GetEmptyInventorySlots();
		if (m_items.size() <= remainingSlots) // if items lower than current slots
		{
			auto pBuffer = new CMsgStreamBuffer(MsgOpcodes::CLIENT_CUSTOM);
			pBuffer->Write<uint8_t>(MsgOpcodeTypes::Chest_RequestAllList);
			pBuffer->SendToServer();
		}
		else
			g_CGInterface->ShowMessage_BLUE(L"Cannot proceed because you don't have enough slots in your inventory.");
		});
	this->AddControl(take_all_btn);

	ScrollBar* main_scroll_bar = new ScrollBar();
	main_scroll_bar->SetSize(16, 254);
	main_scroll_bar->SetLocation(588, 46);
	this->AddControl(main_scroll_bar);

	content_remaining_inventory->SetText(std::to_string(g_CGlobalDataManager->GetEmptyInventorySlots()));
	r_loc = g.MeasureString(content_remaining_inventory->GetText(), content_remaining_inventory->GetFont());
	content_remaining_inventory->SetLocation(217 - (r_loc.Width / 2), 340);

	CustomButton* paginator_bg = new CustomButton(Image::FromMemory(paginator_bgdata));
	paginator_bg->SetEnabled(false);
	paginator_bg->SetLocation(291, 336);
	this->AddControl(paginator_bg);

	CustomButton* left_arrow = new CustomButton(Image::FromMemory(com_left_arrowdata), Image::FromMemory(com_left_arrow_focusdata), Image::FromMemory(com_left_arrow_pressdata));
	left_arrow->SetLocation(304, 336);
	left_arrow->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		if (m_selected_page > 1)
		{
			auto current_index = m_selected_page * 12;
			auto limiter = current_index - 12;

			//printf("selected_page = %d - current_index = %d - limiter = %d\n", m_selected_page, current_index, limiter);
			if (limiter > 12)
			{
				RefreshItemsList(limiter - 12);
			}
			else
			{
				RefreshItemsList(0);
			}
			this->m_selected_page--;
			this->paginator_text->SetText(std::to_string(m_selected_page));
			this->UpdatePagination();
		}
		});
	this->AddControl(left_arrow);

	CustomButton* right_arrow = new CustomButton(Image::FromMemory(com_right_arrowdata), Image::FromMemory(com_right_arrow_focusdata), Image::FromMemory(com_right_arrow_pressdata));
	right_arrow->SetLocation(342, 336);
	right_arrow->GetClickEvent() += ClickEventHandler([&](Control* sender) {

			auto next_begin_index = m_selected_page * 12;
			if (next_begin_index < m_items.size())
			{
				this->m_selected_page++;
				this->paginator_text->SetText(std::to_string(m_selected_page));
				this->UpdatePagination();
				if(m_selected_page == 2)
					RefreshItemsList(next_begin_index+1);
				else if(m_selected_page != 2)
					RefreshItemsList(next_begin_index);
			}

		});
	this->AddControl(right_arrow);

	paginator_text = new Label();
	paginator_text->SetLocation(327, 337);
	paginator_text->SetText(std::to_string(this->m_selected_page));
	this->AddControl(paginator_text);

	CMsgStreamBuffer* request_packet = new CMsgStreamBuffer(MsgOpcodes::CLIENT_CUSTOM);
	request_packet->Write<uint8_t>(MsgOpcodeTypes::Chest_RequestList);
	request_packet->SendToServer();
}