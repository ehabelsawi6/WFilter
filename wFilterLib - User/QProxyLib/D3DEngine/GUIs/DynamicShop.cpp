#include "DynamicShop.h"
#include "../ResourceManager.h"
#include "../../GameMain/GameMain.h"
#include "Helpers/CustomButton.h"
#include "../../GameStuff/CGInterface/CGInterface.h"


extern Misc::RawDataContainer title_bardata;

extern Misc::RawDataContainer com_button_disabled_data;
extern Misc::RawDataContainer com_button_data;
extern Misc::RawDataContainer com_button_hover_data;
extern Misc::RawDataContainer com_button_press_data;

int c_interval = 0;

void DynamicShopWindow::InitializeComponent()
{
    SetCaptionBar(true);
    SetPanelEnabled(false);

    SetName("DynamicShopWindow");
    SetSize(Size(500, 350));
    SetText("Dynamic Shop");

    auto size = Application::Instance().GetRenderer().GetDisplaySize();
    SetLocation(((size.Width - this->GetSize().Width) / 2), ((size.Height - this->GetSize().Height)) / 2);




    tabPage3 = new TabControl();
    tabPage3->SetName("tabPage3");
    tabPage3->SetLocation(Point(3, -5));
    tabPage3->SetSize(Size(480, 300));

    TitlesPage = new TabPage();
    TitlesPage->SetName("TitlesPage");
    TitlesPage->SetText("Titles");

    titleBarPic = new PictureBox();
    titleBarPic->SetImage(Image::FromMemory(title_bardata));
    titleBarPic->SetSize(Size(468, 17));
    titleBarPic->SetLocation(Point(5, 5));
    titleBarPic->SetStretch(true);
    TitlesPage->AddControl(titleBarPic);


    listBox1 = new ListBox1();
    listBox1->SetTStyle(8);
    listBox1->SetName("listBox1");
    listBox1->SetLocation(Point(3, 20));
    listBox1->SetSize(Size(465, 218));
    listBox1->SetAutoScrollEnabled(true);
    //listBox1->AddItem("1,H,1,5");

    auto titlesListSize = g_GlobalDataMgr->m_DSTitles.size();
    if (titlesListSize != 0)
    {
        int count = 0;
        for (const auto hwanLevel : g_GlobalDataMgr->m_DSTitles)
        {
            count++;
            listBox1->AddItem(std::to_string(hwanLevel.TitleId) +","+ g_GlobalDataMgr->GetHwanString(hwanLevel.TitleId) + ",1," + std::to_string(hwanLevel.Price));
        }
    }
    listBox1->SetSelectedIndex(0);
    TitlesPage->AddControl(listBox1);


    CustomButton* btn_Buy = new CustomButton(Image::FromMemory(com_button_data), Image::FromMemory(com_button_hover_data), Image::FromMemory(com_button_press_data));
    btn_Buy->SetLocation(385, 245);
    btn_Buy->SetText("Buy");
    btn_Buy->GetClickEvent() += ClickEventHandler([&](Control* control) {
        auto ItemText = listBox1->GetSelectedItem()->GetItemText().c_str();
       // g_CGInterface->ShowMessage_PINK(CStringHelper::wsplit(CStringHelper::s2ws(ItemText),',')[0]);

        CMsgStreamBuffer* packet = new CMsgStreamBuffer(0x1337);
        packet->Write<uint8_t>(0x30);
        packet->Write<uint32_t>(g_CICPlayer->GetUniqueID());
        packet->Write<uint8_t>(0x1);
        packet->Write<uint8_t>(std::stoi(CStringHelper::split(ItemText, ',')[0]));
        packet->SendToServer();

        this->Close();
	});
    TitlesPage->AddControl(btn_Buy);

    tabPage3->AddTabPage(TitlesPage);

    IconsPage = new TabPage();
    IconsPage->SetName("IconsPage");
    IconsPage->SetText("Icons");

    PictureBox* titleBarPic2 = new PictureBox();
    titleBarPic2->SetImage(Image::FromMemory(title_bardata));
    titleBarPic2->SetSize(Size(468, 17));
    titleBarPic2->SetLocation(Point(5, 5));
    titleBarPic2->SetStretch(true);
   // IconsPage->AddControl(titleBarPic2);

   // tabPage3->AddTabPage(IconsPage);

#pragma region Colors Page
    ColorsPage = new TabPage();
    ColorsPage->SetName("ColorsPage");
    ColorsPage->SetText("Colros");
    tabPage3->AddTabPage(ColorsPage);


    panel1 = new Panel();
    panel1->SetName("panel1");
    panel1->SetLocation(Point(24, 26));
    panel1->SetSize(Size(166, 178));

    buttonName = new Button();
    buttonName->SetName("buttonName");
    buttonName->SetLocation(Point(102, 145));
    buttonName->SetSize(Size(50, 24));
    buttonName->SetText("Buy");
    panel1->AddControl(buttonName);

    priceName = new Label();
    priceName->SetName("priceName");
    priceName->SetLocation(Point(22, 145));
    priceName->SetSize(Size(46, 14));
    priceName->SetText("Price : " + std::to_string(g_GlobalDataMgr->DShopNameColorPrice));
    panel1->AddControl(priceName);

    colorPickerName = new ColorPicker();
    colorPickerName->SetName("colorPickerName");
    colorPickerName->SetLocation(Point(8, 40));
    colorPickerName->SetSize(Size(151, 92));
    panel1->AddControl(colorPickerName);

    label6 = new Label();
    label6->SetName("label6");
    label6->SetLocation(Point(14, 18));
    label6->SetSize(Size(47, 14));
    label6->SetText("Preview");
    panel1->AddControl(label6);

    checkName = new CheckBox();
    checkName->SetName("checkName");
    checkName->SetLocation(Point(71, 16));
    checkName->SetSize(Size(87, 17));
    checkName->SetText(" Live Preview");
    panel1->AddControl(checkName);

    ColorsPage->AddControl(panel1);

    label5 = new Label();
    label5->SetName("label5");
    label5->SetLocation(Point(65, 9));
    label5->SetSize(Size(85, 14));
    label5->SetText("CharName Color");
    ColorsPage->AddControl(label5);

    panel2 = new Panel();
    panel2->SetName("panel2");
    panel2->SetLocation(Point(263, 26));
    panel2->SetSize(Size(166, 178));

    buttonTitle = new Button();
    buttonTitle->SetName("buttonTitle");
    buttonTitle->SetLocation(Point(102, 145));
    buttonTitle->SetSize(Size(50, 24));
    buttonTitle->SetText("Buy");
    panel2->AddControl(buttonTitle);

    priceTitle = new Label();
    priceTitle->SetName("priceTitle");
    priceTitle->SetLocation(Point(22, 145));
    priceTitle->SetSize(Size(46, 14));
    priceTitle->SetText("Price : " + std::to_string(g_GlobalDataMgr->DShopTitleColorPrice));
    panel2->AddControl(priceTitle);

    colorPickerTitle = new ColorPicker();
    colorPickerTitle->SetName("colorPickerTitle");
    colorPickerTitle->SetLocation(Point(8, 40));
    colorPickerTitle->SetSize(Size(151, 93));
    panel2->AddControl(colorPickerTitle);

    label8 = new Label();
    label8->SetName("label8");
    label8->SetLocation(Point(14, 18));
    label8->SetSize(Size(47, 14));
    label8->SetText("Preview");
    panel2->AddControl(label8);

    checkTitle = new CheckBox();
    checkTitle->SetName("checkTitle");
    checkTitle->SetLocation(Point(71, 16));
    checkTitle->SetSize(Size(87, 17));
    checkTitle->SetText(" Live Preview");
    panel2->AddControl(checkTitle);

    ColorsPage->AddControl(panel2);

    label9 = new Label();
    label9->SetName("label9");
    label9->SetLocation(Point(301, 9));
    label9->SetSize(Size(81, 14));
    label9->SetText("TitleName Color");
    ColorsPage->AddControl(label9);;


    colorPickerName->GetColorChangedEvent() += ColorChangedEventHandler([&](Control* control, Color color) {
        label6->SetForeColor(color);
        if (checkName->GetChecked())
            reinterpret_cast<void(__thiscall*)(CICPlayer*, uint32_t)>(0x009C1920)(g_CICPlayer, color.GetARGB());
        });


    timer = new Timer();
    timer->SetInterval(5000);
    timer->GetTickEvent() += TickEventHandler([this](Control* sender) {

        auto hasTitleColor = g_GlobalDataMgr->m_TitleColors.find(g_CICPlayer->GetCharName()->c_str());
        if (hasTitleColor != g_GlobalDataMgr->m_TitleColors.end())
            g_CICPlayer->GetTitleFontTexture()->SetColor(hasTitleColor->second);

        if (c_interval == 10)
        {
            c_interval = 0;
            sender->SetEnabled(false);
        }
        c_interval++;
        });
    this->AddControl(timer);


    colorPickerTitle->GetColorChangedEvent() += ColorChangedEventHandler([&](Control* control, Color color) {
        label8->SetForeColor(color);
        if (checkTitle->GetChecked()) {

            g_CICPlayer->GetTitleFontTexture()->SetColor(color.GetARGB());

            if (!timer->GetEnabled())
                timer->Start();

        }
        });



    buttonName->GetClickEvent() += ClickEventHandler([&](Control* control) {

        CMsgStreamBuffer* packet = new CMsgStreamBuffer(0x1337);
        packet->Write<uint8_t>(0x30);
        packet->Write<uint32_t>(g_CICPlayer->GetUniqueID());
        packet->Write<uint8_t>(0x2);
        packet->Write<uint32_t>(label6->GetForeColor().GetARGB());
        packet->SendToServer();

        this->Close();
        });

    buttonTitle->GetClickEvent() += ClickEventHandler([&](Control* control) {

        CMsgStreamBuffer* packet = new CMsgStreamBuffer(0x1337);
        packet->Write<uint8_t>(0x30);
        packet->Write<uint32_t>(g_CICPlayer->GetUniqueID());
        packet->Write<uint8_t>(0x3);
        packet->Write<uint32_t>(label8->GetForeColor().GetARGB());
        packet->SendToServer();

        this->Close();
        });

    //ColorPicker* nameColor3 = new ColorPicker();
    //nameColor3->GetColorChangedEvent() += ColorChangedEventHandler([&](Control* control,Color color) {
    //    g_CGInterface->ShowMessage_PINK(std::to_wstring(color.GetARGB()));
    //    reinterpret_cast<void(__thiscall*)(CICPlayer*, uint32_t)>(0x009C1920)(g_CICPlayer, color.GetARGB());

    //  //  g_CICPlayer->UpdateNameColor(color.GetARGB());
    //    });
    //ColorsPage->AddControl(nameColor3);

    AddControl(tabPage3);

#pragma endregion

    

    Label* points = new Label();
    points->SetLocation(15, 270);
    points->SetText("Current DS-Points: " + std::to_string(g_GlobalDataMgr->DSPoints));
    points->SetForeColor(Color::Yellow());
    this->AddControl(points);

}

