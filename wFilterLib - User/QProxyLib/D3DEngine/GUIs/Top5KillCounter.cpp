#include "Top5KillCounter.h"
#include "../GUIs/Helpers/CustomButton.h"
#include "../../GameMain/GameMain.h"

//Title Manager main stuff (designs)
extern Misc::RawDataContainer top_5_kill_counter_bg;

void Top5KillCounterWindow::InitializeComponent()
{
	SetCaptionBar(false);
	SetSize(0, 0);
	SetBackColor(Color::Empty());
	auto font = FontManager::LoadFont("Tahoma", 8, false);

	dpsMeter_bg = new PictureBox();
	dpsMeter_bg->SetEnabled(false);
	dpsMeter_bg->SetName("ggwp");
	dpsMeter_bg->SetImage(Image::FromMemory(top_5_kill_counter_bg));
	dpsMeter_bg->SetSize(205, 134); 
	auto size = Application::Instance().GetRenderer().GetDisplaySize();
	this->SetLocation(size.Width - 400, 100);
	this->AddControl(dpsMeter_bg);
}

void Top5KillCounterWindow::Start(CMsgStreamBuffer* &packet)
{
	for each (auto control in this->GetControls())
	{
		if (control->GetName() != "ggwp")
		{
			control->SetEnabled(false);
			control->SetVisible(false);
			this->RemoveControl(control);
		}
	}

	auto len = packet->Read<uint8_t>();

	auto base_x = 48, base_y = 30;

	for (size_t i = 0; i < len; i++)
	{
		Label* AttackerName = new Label();
		Label* DamageCount = new Label();

		AttackerName->SetText(packet->ReadStringA());

		int32_t _damage = packet->Read<int32_t>();

		std::string _damageString(std::to_string(_damage));

		DamageCount->SetText(_damageString);
		AttackerName->SetLocation(base_x, base_y);
		DamageCount->SetLocation(base_x + 139, base_y);
		base_y += 19;
		this->AddControl(AttackerName);
		this->AddControl(DamageCount);
	}
	auto SelfKill = packet->Read<int8_t>();
	Label* SelfKills = new Label();
	SelfKills->SetLocation(base_x + 139, 120);
	SelfKills->SetText(std::to_string(SelfKill));
	SelfKills->SetForeColor(Color::Cyan());
	AddControl(SelfKills);
}