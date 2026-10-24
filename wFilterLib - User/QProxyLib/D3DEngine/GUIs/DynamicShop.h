#ifndef Q_LIBRARY_DYNAMIC_SHOP_H
#define Q_LIBRARY_DYNAMIC_SHOP_H
#include "../D3DEngine.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

class DynamicShopWindow : public Form
{
private:
	void InitializeComponent();

	TabControl* tabPage3;
	TabPage* TitlesPage;
	TabPage* IconsPage;
	TabPage* ColorsPage;
	ListBox1* listBox1;
	PictureBox* titleBarPic;

	//Color Tab

    OSHGui::Button* buttonTitle;
    OSHGui::CheckBox* checkName;
    OSHGui::CheckBox* checkTitle;
    OSHGui::Label* colorNameLabel;
    OSHGui::ColorPicker* colorPickerName;
    OSHGui::ColorPicker* colorPickerTitle;
    OSHGui::Label* colorTitleLabel;
    OSHGui::GroupBox* groupBox4;
    OSHGui::Label* label5;
    OSHGui::Label* label6;
    OSHGui::Label* priceTitle;
    OSHGui::Label* label8;
    OSHGui::Label* label9;
    OSHGui::Button* buttonName;
    OSHGui::ColorPicker* namePicker;
    OSHGui::Label* priceName;
    OSHGui::Panel* panel1;
    OSHGui::Panel* panel2;
    OSHGui::CheckBox* previewNameBtn;
    OSHGui::CheckBox* previewTitleBtn;
    OSHGui::Button* titleColorBuyBtn;
    OSHGui::ColorPicker* titlePicker;
    OSHGui::Label* titlePriceTxt;
    Timer* timer;

public:
	DynamicShopWindow() : Form()
	{
		InitializeComponent();
	}
	
	 unsigned int createRGBA(int r, int g, int b, int a)
	{
		return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8);

	}

};
#endif