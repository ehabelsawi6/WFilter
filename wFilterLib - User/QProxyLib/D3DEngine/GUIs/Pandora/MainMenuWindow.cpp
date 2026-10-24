#include "MainMenuWindow.h"
#include "../Helpers/CustomButton.h"
#include "../../../GameMain/GameMain.h"
#include "../TitleManager.h"
#include "../UniqueStatus.h"
#include "../../../GameStuff/CGInterface/CGInterface.h"
#include "../GrantNameWindow.h"
#include "../CustomTitleWindow.h"
#include "../RankingWindow.h"
#include "../EventManager.h"
#include "../EventTimesWindow.h"
#include "../AccountLockWindow.h"
#include "../../../Defines.h"
#include <shellapi.h>
#include "../DynamicShop.h"

extern CIFEdit* g_CIFEdit;
//extern Misc::RawDataContainer main_menu_bgdata;
//Close Button
extern Misc::RawDataContainer main_menu_button_closedata;
extern Misc::RawDataContainer main_menu_button_close_hoverdata;
extern Misc::RawDataContainer main_menu_button_close_pressdata;
////Title Manager Button
//extern Misc::RawDataContainer main_menu_tmanagerbutton_data;
//extern Misc::RawDataContainer main_menu_tmanagerbutton_hoverdata;
//extern Misc::RawDataContainer main_menu_tmanagerbutton_pressdata;
////Unique Status Button
//extern Misc::RawDataContainer main_menu_ustatusbutton_data;
//extern Misc::RawDataContainer main_menu_ustatusbutton_hoverdata;
//extern Misc::RawDataContainer main_menu_ustatusbutton_pressdata;
////Event Manager Button
//extern Misc::RawDataContainer main_menu_eventmgrbutton_data;
//extern Misc::RawDataContainer main_menu_eventmgrbutton_hoverdata;
//extern Misc::RawDataContainer main_menu_eventmgrbutton_pressdata;
////Event Manager Button
//extern Misc::RawDataContainer main_menu_grantnamebutton_data;
//extern Misc::RawDataContainer main_menu_grantnamebutton_hoverdata;
//extern Misc::RawDataContainer main_menu_grantnamebutton_pressdata;
////Custom Title Button
//extern Misc::RawDataContainer main_menu_custom_titlebutton_data;
//extern Misc::RawDataContainer main_menu_custom_titlebutton_hoverdata;
//extern Misc::RawDataContainer main_menu_custom_titlebutton_pressdata;
////Ranking Button
//extern Misc::RawDataContainer main_menu_rankingbutton_data;
//extern Misc::RawDataContainer main_menu_rankingbutton_hoverdata;
//extern Misc::RawDataContainer main_menu_rankingbutton_pressdata;


//New Look

extern Misc::RawDataContainer customTitle_btn;
extern Misc::RawDataContainer customTitle_btn_hover;
extern Misc::RawDataContainer customTitle_btn_press;
extern Misc::RawDataContainer customTitle_btn_disable;

extern Misc::RawDataContainer discord_btn;
extern Misc::RawDataContainer discord_btn_hover;
extern Misc::RawDataContainer discord_btn_press;
extern Misc::RawDataContainer discord_btn_disable;

extern Misc::RawDataContainer eventTimes_btn;
extern Misc::RawDataContainer eventTimes_btn_hover;
extern Misc::RawDataContainer eventTimes_btn_press;
extern Misc::RawDataContainer eventTimes_btn_disable;

extern Misc::RawDataContainer facebook_btn;
extern Misc::RawDataContainer facebook_btn_hover;
extern Misc::RawDataContainer facebook_btn_press;
extern Misc::RawDataContainer facebook_btn_disable;

extern Misc::RawDataContainer grantName_btn;
extern Misc::RawDataContainer grantName_btn_hover;
extern Misc::RawDataContainer grantName_btn_press;
extern Misc::RawDataContainer grantName_btn_disable;

extern Misc::RawDataContainer dynamicShop_btn;
extern Misc::RawDataContainer dynamicShop_btn_hover;
extern Misc::RawDataContainer dynamicShop_btn_press;
extern Misc::RawDataContainer dynamicShop_btn_disable;

extern Misc::RawDataContainer title;

extern Misc::RawDataContainer newMenu_bg;

extern Misc::RawDataContainer titleManager_btn;
extern Misc::RawDataContainer titleManager_btn_hover;
extern Misc::RawDataContainer titleManager_btn_press;
extern Misc::RawDataContainer titleManager_btn_disable;

extern Misc::RawDataContainer uniqueStatus_btn;
extern Misc::RawDataContainer uniqueStatus_btn_hover;
extern Misc::RawDataContainer uniqueStatus_btn_press;
extern Misc::RawDataContainer uniqueStatus_btn_disable;

extern Misc::RawDataContainer website_btn;
extern Misc::RawDataContainer website_btn_hover;
extern Misc::RawDataContainer website_btn_press;
extern Misc::RawDataContainer website_btn_disable;



//self pointer
extern MainMenuWindow* mainMenuWindow;

//Custom guis
TitleManagerWindow* titleManagerWindow;

UniqueStatusWindow* uniqueStatusWindow;

GrantNameWindow* grantNameWindow;

CustomTitleWindow* customTitleWindow;

AccountLockWindow* accountLockWindow;

EventManagerWindow* eventManagerWindow;

EventTimesWindow* eventTimesWindow;

DynamicShopWindow* dynamicShopWindow;


void MainMenuWindow::InitializeComponent()
{
	this->SetSize(0, 0);
	this->SetPanelEnabled(false);
	this->SetCaptionBar(false);

	PictureBox* menu_bg = new PictureBox();

	menu_bg->SetSize(200, 400);



	menu_bg->SetImage(Image::FromMemory(newMenu_bg));
	this->AddControl(menu_bg);
	auto default_location = Application::Instance().GetRenderer().GetDisplaySize();
	this->SetLocation(default_location.Width - 300, 174);

	//CustomButton* menu_close_button = new CustomButton(Image::FromMemory(main_menu_button_closedata),
	//	Image::FromMemory(main_menu_button_close_hoverdata), Image::FromMemory(main_menu_button_close_pressdata));
	//menu_close_button->SetSize(19, 19);
	//menu_close_button->SetLocation(177, 18);
	//menu_close_button->GetClickEvent() += ClickEventHandler([&](Control* sender) { 
	//	if (mainMenuWindow)
	//	{
	//		mainMenuWindow->Close();
	//		mainMenuWindow = nullptr;
	//	}
	//	});
	//this->AddControl(menu_close_button);

	CustomButton* menu_title_manager_button;

	if (g_GlobalDataMgr->m_Settings.TitleManager)
		menu_title_manager_button = new CustomButton(Image::FromMemory(titleManager_btn),
			Image::FromMemory(titleManager_btn_hover), Image::FromMemory(titleManager_btn_press));

	else
	{
		menu_title_manager_button = new CustomButton(Image::FromMemory(titleManager_btn_disable));
		menu_title_manager_button->SetEnabled(false);
	}


	menu_title_manager_button->SetSize(177, 40);
	menu_title_manager_button->SetLocation(15, 55);
	menu_title_manager_button->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		if (!titleManagerWindow)
		{
			titleManagerWindow = new TitleManagerWindow();
			titleManagerWindow->GetFormClosingEvent() += FormClosingEventHandler([&](Control* sender, bool canClose) {
					titleManagerWindow = nullptr;
					g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_close");
				});

			g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_open");
			titleManagerWindow->Show(std::shared_ptr<Form>(titleManagerWindow));
		}
		});
	this->AddControl(menu_title_manager_button);


	CustomButton* menu_unique_status_button;

	if (g_GlobalDataMgr->m_Settings.UniqueStatus)
		menu_unique_status_button = new CustomButton(Image::FromMemory(uniqueStatus_btn),
			Image::FromMemory(uniqueStatus_btn_hover), Image::FromMemory(uniqueStatus_btn_press));

	else
	{
		menu_unique_status_button = new CustomButton(Image::FromMemory(uniqueStatus_btn_disable));
		menu_unique_status_button->SetEnabled(false);
	}


	menu_unique_status_button->SetSize(177, 40);
	menu_unique_status_button->SetLocation(15, 102);
	menu_unique_status_button->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		if (!uniqueStatusWindow)
		{
			uniqueStatusWindow = new UniqueStatusWindow();
			uniqueStatusWindow->GetFormClosingEvent() += FormClosingEventHandler([&](Control* sender, bool canClose) {
					uniqueStatusWindow = nullptr;
					g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_close");
				});
			g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_open");
			uniqueStatusWindow->Show(std::shared_ptr<Form>(uniqueStatusWindow));
		}
		});
	this->AddControl(menu_unique_status_button);


	CustomButton* menu_event_manager_button;

	if (g_GlobalDataMgr->m_Settings.EventTimes)
		menu_event_manager_button = new CustomButton(Image::FromMemory(eventTimes_btn),
			Image::FromMemory(eventTimes_btn_hover), Image::FromMemory(eventTimes_btn_press));

	else
	{
		menu_event_manager_button = new CustomButton(Image::FromMemory(eventTimes_btn_disable));
		menu_event_manager_button->SetEnabled(false);
	}


	menu_event_manager_button->SetSize(177, 40);
	menu_event_manager_button->SetLocation(15, 147);
	menu_event_manager_button->GetClickEvent() += ClickEventHandler([&](Control* sender) {
			if (!eventTimesWindow)
			{
				eventTimesWindow = new EventTimesWindow();
				eventTimesWindow->Show(std::shared_ptr<Form>(eventTimesWindow));
				eventTimesWindow->GetFormClosingEvent() += FormClosingEventHandler([&](Control* sender, bool canClose) {
						g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_close");
						eventTimesWindow = nullptr;
					});
			}
		});
	this->AddControl(menu_event_manager_button);


	CustomButton* menu_grant_name_button;

	if (g_GlobalDataMgr->m_Settings.GrantName)
		menu_grant_name_button = new CustomButton(Image::FromMemory(grantName_btn),
			Image::FromMemory(grantName_btn_hover), Image::FromMemory(grantName_btn_press));

	else
	{
		menu_grant_name_button = new CustomButton(Image::FromMemory(grantName_btn_disable));
		menu_grant_name_button->SetEnabled(false);
	}

	menu_grant_name_button->SetSize(177, 40);
	menu_grant_name_button->SetLocation(15, 193); 
	menu_grant_name_button->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		if (!grantNameWindow)
		{
			grantNameWindow = new GrantNameWindow();
			grantNameWindow->GetFormClosingEvent() += FormClosingEventHandler([&](Control* sender, bool canClose) {
				grantNameWindow = nullptr;
				g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_close");
				});
			g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_open");
			grantNameWindow->Show(std::shared_ptr<Form>(grantNameWindow));
		}
		});
	this->AddControl(menu_grant_name_button);


	CustomButton* menu_custom_title_button;

	if (g_GlobalDataMgr->m_Settings.CustomTitle)
		menu_custom_title_button = new CustomButton(Image::FromMemory(customTitle_btn),
			Image::FromMemory(customTitle_btn_hover), Image::FromMemory(customTitle_btn_press));

	else
	{
		menu_custom_title_button = new CustomButton(Image::FromMemory(customTitle_btn_disable));
		menu_custom_title_button->SetEnabled(false);
	}


	menu_custom_title_button->SetSize(177, 40);
	menu_custom_title_button->SetLocation(15, 238);	
	menu_custom_title_button->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		if (!customTitleWindow)
		{
			customTitleWindow = new CustomTitleWindow();
			customTitleWindow->GetFormClosingEvent() += FormClosingEventHandler([&](Control* sender, bool canClose) {
				customTitleWindow = nullptr;
				g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_close");
				});
			g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_open");
			customTitleWindow->Show(std::shared_ptr<Form>(customTitleWindow));
		}
		});
	this->AddControl(menu_custom_title_button);



	CustomButton* menu_dynamic_shop_button;

	if (g_GlobalDataMgr->m_Settings.DynamicShop)
		menu_dynamic_shop_button = new CustomButton(Image::FromMemory(dynamicShop_btn),
			Image::FromMemory(dynamicShop_btn_hover), Image::FromMemory(dynamicShop_btn_press));

	else
	{
		menu_dynamic_shop_button = new CustomButton(Image::FromMemory(dynamicShop_btn_disable));
		menu_dynamic_shop_button->SetEnabled(false);
	}


	menu_dynamic_shop_button->SetSize(177, 40);
	menu_dynamic_shop_button->SetLocation(15, 285);
	menu_dynamic_shop_button->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		if (!dynamicShopWindow)
		{
			dynamicShopWindow = new DynamicShopWindow();
			dynamicShopWindow->GetFormClosingEvent() += FormClosingEventHandler([&](Control* sender, bool canClose) {
				dynamicShopWindow = nullptr;
				g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_close");
				});
			g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_open");
			dynamicShopWindow->Show(std::shared_ptr<Form>(dynamicShopWindow));
		}
		});
	this->AddControl(menu_dynamic_shop_button);


	CustomButton* menu_website_button;

	if (g_GlobalDataMgr->m_Settings.Website)
		menu_website_button = new CustomButton(Image::FromMemory(website_btn),
			Image::FromMemory(website_btn_hover), Image::FromMemory(website_btn_press));

	else
	{
		menu_website_button = new CustomButton(Image::FromMemory(website_btn_disable));
		menu_website_button->SetEnabled(false);
	}

	menu_website_button->SetSize(51, 58);
	menu_website_button->SetLocation(15, 340);
	menu_website_button->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		ShellExecute(0, 0, g_GlobalDataMgr->m_Settings.WebsiteLink.c_str(), 0, 0, SW_SHOW);
		});
	this->AddControl(menu_website_button);


	CustomButton* menu_facebook_button;

	if (g_GlobalDataMgr->m_Settings.Facebook)
		menu_facebook_button = new CustomButton(Image::FromMemory(facebook_btn),
			Image::FromMemory(facebook_btn_hover), Image::FromMemory(facebook_btn_press));

	else
	{
		menu_facebook_button = new CustomButton(Image::FromMemory(facebook_btn_disable));
		menu_facebook_button->SetEnabled(false);
	}

	menu_facebook_button->SetSize(51, 58);
	menu_facebook_button->SetLocation(77, 340);
	menu_facebook_button->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		ShellExecute(0, 0, g_GlobalDataMgr->m_Settings.FacebookLink.c_str(), 0, 0, SW_SHOW);
		});
	this->AddControl(menu_facebook_button);



	CustomButton* menu_discord_button;

	if (g_GlobalDataMgr->m_Settings.Discord)
		menu_discord_button = new CustomButton(Image::FromMemory(discord_btn),
			Image::FromMemory(discord_btn_hover), Image::FromMemory(discord_btn_press));

	else
	{
		menu_discord_button = new CustomButton(Image::FromMemory(discord_btn_disable));
		menu_discord_button->SetEnabled(false);
	}

	menu_discord_button->SetSize(51, 58);
	menu_discord_button->SetLocation(140, 340);
	menu_discord_button->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		ShellExecute(0, 0, g_GlobalDataMgr->m_Settings.DiscordLink.c_str(), 0, 0, SW_SHOW);
		});
	this->AddControl(menu_discord_button);











	/*CustomButton* menu_ranking_button = new CustomButton(Image::FromMemory(main_menu_rankingbutton_data),
		Image::FromMemory(main_menu_rankingbutton_hoverdata), Image::FromMemory(main_menu_rankingbutton_pressdata));
	menu_ranking_button->SetSize(182, 40);
	menu_ranking_button->SetLocation(15, 225); 
	menu_ranking_button->GetClickEvent() += ClickEventHandler([&](Control* sender) {
			if (!accountLockWindow)
			{
				accountLockWindow = new AccountLockWindow();
				accountLockWindow->GetFormClosingEvent() += FormClosingEventHandler([&](Control* sender, bool canClose) {
					accountLockWindow = nullptr;
					
					});
				g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_window_open");

				accountLockWindow->Show(std::shared_ptr<Form>(accountLockWindow));
			}
		});
#ifndef Anoha 
	this->AddControl(menu_ranking_button);
#endif*/
}