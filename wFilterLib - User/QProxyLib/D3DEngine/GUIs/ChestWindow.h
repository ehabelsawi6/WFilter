#ifndef Q_GUI_CHEST_WINDOW_H
#define Q_GUI_CHEST_WINDOW_H
#include "IconWindow.h"
#include "../../Network/MsgStreamBuffer.h"

class ChestWindow : public Form
{
	struct ItemData
	{
		uint32_t Index;
		uint32_t ItemID;
		std::string Name;
		uint16_t Quantity;
		std::string Date;
		std::string Type;
	};
private:
	void InitializeComponent();
	Label* content_remaining_inventory;
	
protected:
public:
	ChestWindow() : Form()
	{
		InitializeComponent();
	};
	std::list<ItemData> m_items;
	Label* paginator_text;
	int m_offset = 0;
	int m_selected_page = 1;
	void OnRecvData(CMsgStreamBuffer* packet);
	void OnTakeBtnClicked(uint32_t index);
	void OnRemoveData(uint32_t index);
	void RefreshItemsList(int begin_from = 0);
	void UpdateRemainingInventory();
	void UpdatePagination();
};
#endif