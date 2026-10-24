#include "IconWindow.h"
#include "../../GameMain/GameMain.h"
#include "Helpers/CustomButton.h"
#include "ChestWindow.h"
#include "Pandora/MainMenuWindow.h"
#include <shellapi.h>
#include "EventTimesWindow.h"
#include "DynamicShop.h"

#include "../../Defines.h"
#include <Drawing/Direct3D9/Direct3D9Texture.hpp>

extern Misc::RawDataContainer menu_main_icondata;
extern Misc::RawDataContainer menu_main_icon_hoverdata;

extern Misc::RawDataContainer menu_chest_icon;
extern Misc::RawDataContainer menu_chest_icon_hoverdata;

extern Misc::RawDataContainer menu_discord_foucs;
extern Misc::RawDataContainer menu_discord_icon_hover;

extern Misc::RawDataContainer facebook_icondata;
extern Misc::RawDataContainer facebook_icon_hoverdata;

#ifdef Anoha
extern Misc::RawDataContainer menudata;
extern Misc::RawDataContainer menu_pressdata;
extern Misc::RawDataContainer menu_focusdata;

extern Misc::RawDataContainer discord_guidedata;
extern Misc::RawDataContainer discord_guide_focusdata;
extern Misc::RawDataContainer discord_guide_pressdata;

extern Misc::RawDataContainer facebook_guidedata;
extern Misc::RawDataContainer facebook_guide_focusdata;
extern Misc::RawDataContainer facebook_guide_pressdata;

#endif

ChestWindow* chestWindow;
MainMenuWindow* mainMenuWindow;
//DynamicShopWindow* dynamicShopWindow;
//EventTimesWindow* testWindow;

void IconWindow::InitializeComponent()
{
	this->SetCaptionBar(false);
	this->SetPanelEnabled(false);

	this->SetSize(0, 0);
	auto rect = g_D3DMisc->GetClientRect();
	this->SetLocation(rect.X - 142, 178);


	CustomButton* chest_button = new CustomButton(Image::FromMemory(menu_chest_icon), Image::FromMemory(menu_chest_icon_hoverdata));
	chest_button->SetSize(32, 32);
	chest_button->SetLocation(120, 0);
	 
	//chest_button->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		/*if (!chestWindow)
		{
			chestWindow = new ChestWindow();
			chestWindow->SetName("chestwnd");
			chestWindow->GetFormClosingEvent() += FormClosingEventHandler([&](Control* sender, bool canClose)
				{
					g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_close");
					chestWindow = nullptr;
				});
			chestWindow->Show(std::shared_ptr<Form>(chestWindow));

			g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_open");
		}
		});*/
	/*	if (!dynamicShopWindow) {

			dynamicShopWindow = new DynamicShopWindow();
			dynamicShopWindow->GetFormClosingEvent() += FormClosingEventHandler([&](Control* sender, bool canClose)
				{
					g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_close");
					dynamicShopWindow = nullptr;
				});
			dynamicShopWindow->Show(std::shared_ptr<Form>(dynamicShopWindow));
		}});*/

//	this->AddControl(chest_button);

#ifdef  Anoha
	CustomButton* menu_button = new CustomButton(Image::FromMemory(menudata), Image::FromMemory(menu_focusdata));
	//CustomButton* menu_button = new CustomButton(
		//Image::FromBuffer(g_ResourceMgr->LoadTextureFromPk2("icon\\etc\\icon_rudiment.ddj"), Size(32, 32), Texture::PixelFormat::RGBA));


#else
	CustomButton* menu_button = new CustomButton(Image::FromMemory(menu_main_icondata), Image::FromMemory(menu_main_icon_hoverdata));
	
	/*CustomButton* menu_button = new CustomButton(
		Image::FromBuffer(g_ResourceMgr->LoadTextureFromPk2("icon\\isyutaru.ddj"), Size(32, 32), Texture::PixelFormat::DDS));*/

#endif 



	menu_button->SetSize(32, 32);
	menu_button->SetLocation(249, 0);
	menu_button->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		if (!mainMenuWindow)
		{
			mainMenuWindow = new MainMenuWindow();
			mainMenuWindow->SetName("mainwnd");
			mainMenuWindow->GetFormClosingEvent() += FormClosingEventHandler([&](Control* sender, bool canClose)
				{
					g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_close");
					mainMenuWindow = nullptr;
				});
			mainMenuWindow->Show(std::shared_ptr<Form>(mainMenuWindow));

			g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_open");
		}
		else if (mainMenuWindow)
		{
			mainMenuWindow->Close();
			mainMenuWindow = nullptr;
		}

		});
	this->AddControl(menu_button);

//
//#ifdef  Anoha
//	CustomButton* discord_button = new CustomButton(Image::FromMemory(discord_guidedata), Image::FromMemory(discord_guide_focusdata));
//#else
//	CustomButton* discord_button = new CustomButton(Image::FromMemory(menu_discord_foucs), Image::FromMemory(menu_discord_icon_hover));
//#endif 
//
//	discord_button->SetSize(32, 32);
//	discord_button->SetLocation(211, 0);
//	discord_button->GetClickEvent() += ClickEventHandler([&](Control* sender) {
//		ShellExecute(0, 0, DISCORD_LINK, 0, 0, SW_SHOW);
//
//		});
//	this->AddControl(discord_button);
//
//#ifdef  Anoha
//	CustomButton* facebook_button = new CustomButton(Image::FromMemory(facebook_guidedata), Image::FromMemory(facebook_guide_focusdata));
//#else
//	CustomButton* facebook_button = new CustomButton(Image::FromMemory(facebook_icondata), Image::FromMemory(facebook_icon_hoverdata));
//#endif 
//	facebook_button->SetSize(32, 32);
//	facebook_button->SetLocation(169, 0);
//	facebook_button->GetClickEvent() += ClickEventHandler([&](Control* sender) {
//		ShellExecute(0, 0, FACEBOOK_LINK, 0, 0, SW_SHOW);
//
//		});
//	this->AddControl(facebook_button);

}