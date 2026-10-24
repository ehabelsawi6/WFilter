#ifndef Q_LIBRARY_JOB_STATUS_H
#define Q_LIBRARY_JOB_STATUS_H
#include "../D3DEngine.h"
#include "../../SilkroadWeb/SilkroadWeb.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

class RankingWindow : public Form
{
private:
	void InitializeComponent();
public:
	SilkroadWeb* m_Web;
	RankingWindow() : Form()
	{
		InitializeComponent();
	}
};
#endif