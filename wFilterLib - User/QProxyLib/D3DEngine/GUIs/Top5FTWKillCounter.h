#ifndef Q_GUI_FTW_KILL_COUNTER_MANAGER_H
#define Q_GUI_FTW_KILL_COUNTER_MANAGER_H
#include "../D3DEngine.h"
#include "../../Network/MsgStreamBuffer.h"
#include "../GUIs/Helpers/CustomButton.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;
struct Top5Data
{
	std::string Name;
	int KillsCount;
};
class Top5FTWKillCounterWindow : public Form
{
private:
	void InitializeComponent();
	PictureBox* KillCounter_bg;

	CustomButton* players_btn;
	CustomButton* guilds_btn;

public:
	Top5FTWKillCounterWindow() : Form()
	{
		InitializeComponent();
	}
	void Start(CMsgStreamBuffer* packet);


	Label* m_player1;
	Label* m_player2;
	Label* m_player3;
	Label* m_player4;
	Label* m_player5;

	Label* m_pkillcount1;
	Label* m_pkillcount2;
	Label* m_pkillcount3;
	Label* m_pkillcount4;
	Label* m_pkillcount5;

	Label* m_guild1;
	Label* m_guild2;
	Label* m_guild3;
	Label* m_guild4;
	Label* m_guild5;

	Label* m_gkillcount1;
	Label* m_gkillcount2;
	Label* m_gkillcount3;
	Label* m_gkillcount4;
	Label* m_gkillcount5;
};
#endif