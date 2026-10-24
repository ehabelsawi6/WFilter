#include "Top5FTWKillCounter.h"
#include "../../GameMain/GameMain.h"

extern Misc::RawDataContainer top_5_ftw_kill_counter_bg;
extern Misc::RawDataContainer btn_ftw_guild_data;
extern Misc::RawDataContainer btn_ftw_guild_focusdata;
extern Misc::RawDataContainer btn_ftw_guild_pressdata;
extern Misc::RawDataContainer btn_ftw_player_data;
extern Misc::RawDataContainer btn_ftw_player_focusdata;
extern Misc::RawDataContainer btn_ftw_player_pressdata;

void Top5FTWKillCounterWindow::InitializeComponent()
{
	SetCaptionBar(false);
	SetSize(0, 0);
	SetBackColor(Color::Empty());
	auto font = FontManager::LoadFont("Tahoma", 8, false);

	KillCounter_bg = new PictureBox();
	KillCounter_bg->SetEnabled(false);
	KillCounter_bg->SetName("ggwp");
	KillCounter_bg->SetImage(Image::FromMemory(top_5_ftw_kill_counter_bg));
	KillCounter_bg->SetSize(213, 121);
	auto size = Application::Instance().GetRenderer().GetDisplaySize();
	this->SetLocation(size.Width - 360, 20);
	this->AddControl(KillCounter_bg);


	m_player1 = new Label();
	m_player1->SetLocation(45, 35);
	m_player1->SetText("No Name");
	this->AddControl(m_player1);

	m_player2 = new Label();
	m_player2->SetLocation(45, 55);
	m_player2->SetText("No Name");
	this->AddControl(m_player2);

	m_player3 = new Label();
	m_player3->SetLocation(45, 72);
	m_player3->SetText("No Name");
	this->AddControl(m_player3);

	m_player4 = new Label();
	m_player4->SetLocation(45, 90);
	m_player4->SetText("No Name");
	this->AddControl(m_player4);

	m_player5 = new Label();
	m_player5->SetLocation(45, 108);
	m_player5->SetText("No Name");
	this->AddControl(m_player5);

	m_pkillcount1 = new Label();
	m_pkillcount1->SetLocation(191, 35);
	m_pkillcount1->SetText("0");
	this->AddControl(m_pkillcount1);

	m_pkillcount2 = new Label();
	m_pkillcount2->SetLocation(191, 55);
	m_pkillcount2->SetText("0");
	this->AddControl(m_pkillcount2);

	m_pkillcount3 = new Label();
	m_pkillcount3->SetLocation(191, 72);
	m_pkillcount3->SetText("0");
	this->AddControl(m_pkillcount3);

	m_pkillcount4 = new Label();
	m_pkillcount4->SetLocation(191, 90);
	m_pkillcount4->SetText("0");
	this->AddControl(m_pkillcount4);

	m_pkillcount5 = new Label();
	m_pkillcount5->SetLocation(191, 108);
	m_pkillcount5->SetText("0");
	this->AddControl(m_pkillcount5);


	m_guild1 = new Label();
	m_guild1->SetLocation(45, 35);
	m_guild1->SetText("No Name");
	m_guild1->SetVisible(false);
	this->AddControl(m_guild1);

	m_guild2 = new Label();
	m_guild2->SetLocation(45, 55);
	m_guild2->SetText("No Name");
	m_guild2->SetVisible(false);
	this->AddControl(m_guild2);

	m_guild3 = new Label();
	m_guild3->SetLocation(45, 72);
	m_guild3->SetText("No Name");
	m_guild3->SetVisible(false);
	this->AddControl(m_guild3);

	m_guild4 = new Label();
	m_guild4->SetLocation(45, 90);
	m_guild4->SetText("No Name");
	m_guild4->SetVisible(false);
	this->AddControl(m_guild4);

	m_guild5 = new Label();
	m_guild5->SetLocation(45, 108);
	m_guild5->SetText("No Name");
	m_guild5->SetVisible(false);
	this->AddControl(m_guild5);

	m_gkillcount1 = new Label();
	m_gkillcount1->SetLocation(191, 35);
	m_gkillcount1->SetText("0");
	m_gkillcount1->SetVisible(false);
	this->AddControl(m_gkillcount1);

	m_gkillcount2 = new Label();
	m_gkillcount2->SetLocation(191, 55);
	m_gkillcount2->SetText("0");
	m_gkillcount2->SetVisible(false);
	this->AddControl(m_gkillcount2);

	m_gkillcount3 = new Label();
	m_gkillcount3->SetLocation(191, 72);
	m_gkillcount3->SetText("0");
	m_gkillcount3->SetVisible(false);
	this->AddControl(m_gkillcount3);

	m_gkillcount4 = new Label();
	m_gkillcount4->SetLocation(191, 90);
	m_gkillcount4->SetText("0");
	m_gkillcount4->SetVisible(false);
	this->AddControl(m_gkillcount4);

	m_gkillcount5 = new Label();
	m_gkillcount5->SetLocation(191, 108);
	m_gkillcount5->SetText("0");
	m_gkillcount5->SetVisible(false);
	this->AddControl(m_gkillcount5);


	players_btn = new CustomButton(Image::FromMemory(btn_ftw_player_data), Image::FromMemory(btn_ftw_player_focusdata), Image::FromMemory(btn_ftw_player_pressdata));
	players_btn->SetSize(63, 24);
	players_btn->SetName("pp");
	players_btn->SetLocation(KillCounter_bg->GetLocation().X + 40, KillCounter_bg->GetLocation().Y + 3); 
	players_btn->GetClickEvent() += ClickEventHandler([&](Control* sender)
		{
			players_btn->UpdateImage(Image::FromMemory(btn_ftw_player_pressdata));
			guilds_btn->UpdateImage(Image::FromMemory(btn_ftw_guild_data));
			this->m_guild1->SetVisible(false);
			this->m_guild2->SetVisible(false);
			this->m_guild3->SetVisible(false);
			this->m_guild4->SetVisible(false);
			this->m_guild5->SetVisible(false);
			this->m_gkillcount1->SetVisible(false);
			this->m_gkillcount2->SetVisible(false);
			this->m_gkillcount3->SetVisible(false);
			this->m_gkillcount4->SetVisible(false);
			this->m_gkillcount5->SetVisible(false);
			this->m_player1->SetVisible(true);
			this->m_player2->SetVisible(true);
			this->m_player3->SetVisible(true);
			this->m_player4->SetVisible(true);
			this->m_player5->SetVisible(true);
			this->m_pkillcount1->SetVisible(true);
			this->m_pkillcount2->SetVisible(true);
			this->m_pkillcount3->SetVisible(true);
			this->m_pkillcount4->SetVisible(true);
			this->m_pkillcount5->SetVisible(true);
		});
	this->AddControl(players_btn);

	guilds_btn = new CustomButton(Image::FromMemory(btn_ftw_guild_data), Image::FromMemory(btn_ftw_guild_focusdata), Image::FromMemory(btn_ftw_guild_pressdata));
	guilds_btn->SetSize(63, 24);
	guilds_btn->SetName("ggp");
	guilds_btn->SetLocation((KillCounter_bg->GetLocation().X + 40) + 73, KillCounter_bg->GetLocation().Y + 3);
	guilds_btn->GetClickEvent() += ClickEventHandler([&](Control* sender)
		{
			guilds_btn->UpdateImage(Image::FromMemory(btn_ftw_guild_pressdata));
			players_btn->UpdateImage(Image::FromMemory(btn_ftw_player_data));

			this->m_player1->SetVisible(false);
			this->m_player2->SetVisible(false);
			this->m_player3->SetVisible(false);
			this->m_player4->SetVisible(false);
			this->m_player5->SetVisible(false);
			this->m_pkillcount1->SetVisible(false);
			this->m_pkillcount2->SetVisible(false);
			this->m_pkillcount3->SetVisible(false);
			this->m_pkillcount4->SetVisible(false);
			this->m_pkillcount5->SetVisible(false);
			this->m_guild1->SetVisible(true);
			this->m_guild2->SetVisible(true);
			this->m_guild3->SetVisible(true);
			this->m_guild4->SetVisible(true);
			this->m_guild5->SetVisible(true);
			this->m_gkillcount1->SetVisible(true);
			this->m_gkillcount2->SetVisible(true);
			this->m_gkillcount3->SetVisible(true);
			this->m_gkillcount4->SetVisible(true);
			this->m_gkillcount5->SetVisible(true);
		});
	this->AddControl(guilds_btn);  
}
void Top5FTWKillCounterWindow::Start(CMsgStreamBuffer* packet)
{
	auto players_size = packet->Read<uint8_t>();
	if (players_size != 0)
	{
		auto name1 = packet->ReadStringA();
		this->m_player1->SetText(name1);
		auto kill1 = packet->Read<int>();
		this->m_pkillcount1->SetText(std::to_string(kill1));
		auto name2 = packet->ReadStringA();
		this->m_player2->SetText(name2);
		auto kill2 = packet->Read<int>();
		this->m_pkillcount2->SetText(std::to_string(kill2));
		auto name3 = packet->ReadStringA();
		this->m_player3->SetText(name3);
		auto kill3 = packet->Read<int>();
		this->m_pkillcount3->SetText(std::to_string(kill3));
		auto name4 = packet->ReadStringA();
		this->m_player4->SetText(name4);
		auto kill4 = packet->Read<int>();
		this->m_pkillcount4->SetText(std::to_string(kill4));
		auto name5 = packet->ReadStringA();
		this->m_player5->SetText(name5);
		auto kill5 = packet->Read<int>();
		this->m_pkillcount5->SetText(std::to_string(kill5));
	}
	auto guilds_size = packet->Read<uint8_t>();
	if (guilds_size != 0)
	{
		auto name1 = packet->ReadStringA();
		this->m_guild1->SetText(name1);
		auto kill1 = packet->Read<int>();
		this->m_gkillcount1->SetText(std::to_string(kill1));
		auto name2 = packet->ReadStringA();
		this->m_guild2->SetText(name2);
		auto kill2 = packet->Read<int>();
		this->m_gkillcount2->SetText(std::to_string(kill2));
		auto name3 = packet->ReadStringA();
		this->m_guild3->SetText(name3);
		auto kill3 = packet->Read<int>();
		this->m_gkillcount3->SetText(std::to_string(kill3));
		auto name4 = packet->ReadStringA();
		this->m_guild4->SetText(name4);
		auto kill4 = packet->Read<int>();
		this->m_gkillcount4->SetText(std::to_string(kill4));
		auto name5 = packet->ReadStringA();
		this->m_guild5->SetText(name5);
		auto kill5 = packet->Read<int>();
		this->m_gkillcount5->SetText(std::to_string(kill5));
	}
}