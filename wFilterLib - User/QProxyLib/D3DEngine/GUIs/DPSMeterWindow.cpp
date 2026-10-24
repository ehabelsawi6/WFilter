#include "DPSMeterWindow.h"
#include "../GUIs/Helpers/CustomButton.h"
#include "../../GameMain/GameMain.h"

extern Misc::RawDataContainer dps_meter_windowdata;
int g_interval = 0;
void DPSMeterWindow::InitializeComponent()
{
	SetCaptionBar(false);
	SetSize(0, 0);
	SetBackColor(Color::Empty());
	auto font = FontManager::LoadFont("Tahoma", 8, false);

	dpsMeter_bg = new PictureBox();
	dpsMeter_bg->SetEnabled(false);
	dpsMeter_bg->SetName("ggwp");
	dpsMeter_bg->SetImage(Image::FromMemory(dps_meter_windowdata));
	dpsMeter_bg->SetSize(233, 210); 
	auto size = Application::Instance().GetRenderer().GetDisplaySize();
	this->SetLocation(size.Width - 580, -5);
	this->AddControl(dpsMeter_bg);
}

void DPSMeterWindow::Start(CMsgStreamBuffer* &packet)
{
	g_interval = 0;
	for each (auto control in this->GetControls())
	{
		if (control->GetName() != "ggwp")
		{
			control->SetEnabled(false);
			control->SetVisible(false);
			this->RemoveControl(control);
		}
	}

	Label* UniqueName = new Label();
	auto mobid = packet->Read<uint32_t>();

	auto objclass = g_GlobalDataMgr->GetGenericObjectDataByID(mobid);
	auto objshit = g_GlobalDataMgr->GetObjectName(objclass);
	auto objstring = std::string(objshit.begin(), objshit.end());
	auto objname = objstring;
	UniqueName->SetText(objname);
	auto loc = dpsMeter_bg->GetLocation();
	UniqueName->SetLocation(loc.X + 46, loc.Y + 18);
	this->AddControl(UniqueName);

	auto len = packet->Read<uint32_t>();

	auto base_x = 52, base_y = 45;

	for (size_t i = 0; i < len; i++)
	{
		Label* AttackerName = new Label();
		Label* DamageCount = new Label();
		auto name = packet->ReadStringA();

		AttackerName->SetText(name);

		uint32_t _damage = packet->Read<uint32_t>();

		std::string _damageString(std::to_string(_damage));

		size_t DamageLength = _damageString.length();

		std::string returnString = "";

		if (DamageLength <= 3)
		{
			returnString = _damageString;
		}
		if (DamageLength >= 4 && DamageLength <= 6) //K, binküsurdmg
		{
			returnString = _damageString.substr(0, DamageLength - 3) + "K";
		}
		if (DamageLength >= 7 && DamageLength <= 9) //M, milyondmg
		{
			returnString = _damageString.substr(0, DamageLength - 6) + "," + _damageString.substr(DamageLength - 6, 2) + "M";
		}
		else if (DamageLength == 10)
		{
			returnString = _damageString.substr(0, 1) + "," + _damageString.substr(1, 3) + "B";
		}

		DamageCount->SetText(returnString);
		AttackerName->SetLocation(base_x, base_y);
		DamageCount->SetLocation(base_x + 114, base_y);
		base_y += 18;
		this->AddControl(AttackerName);
		this->AddControl(DamageCount);
	}
	auto timer = new Timer();
	timer->SetInterval(1000);
	timer->GetTickEvent() += TickEventHandler([this](Control* sender) {
		if (g_interval == 7)
		{
			g_interval = 0;
			this->Close();
		}
		g_interval++;
		});
	timer->Start();
	this->AddControl(timer);
}