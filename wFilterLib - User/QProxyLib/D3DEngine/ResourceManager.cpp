#include "ResourceManager.h"
#include "D3DEngine.h"
#include "../resource.h"
#include "../GameMain/GameMain.h"
#include "../Defines.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

//Form
Misc::RawDataContainer right_up_borderdata;
Misc::RawDataContainer left_up_borderdata;
Misc::RawDataContainer up_centerdata;
Misc::RawDataContainer left_bottom_begindata;
Misc::RawDataContainer right_bottom_enddata;
Misc::RawDataContainer bottom_centerdata;
Misc::RawDataContainer left_borderdata;
Misc::RawDataContainer right_borderdata;
Misc::RawDataContainer contentdata;
Misc::RawDataContainer com_windowclosedata;
Misc::RawDataContainer com_windowclose_focusdata;
Misc::RawDataContainer com_windowclose_pressdata;

//Panel
Misc::RawDataContainer com_bg_tile_cdata;
Misc::RawDataContainer ub_pet_wnd_left_downdata;
Misc::RawDataContainer ub_pet_wnd_left_sidedata;
Misc::RawDataContainer ub_pet_wnd_left_updata;
Misc::RawDataContainer ub_pet_wnd_mid_downdata;
Misc::RawDataContainer ub_pet_wnd_mid_updata;
Misc::RawDataContainer ub_pet_wnd_right_downdata;
Misc::RawDataContainer ub_pet_wnd_right_sidedata;
Misc::RawDataContainer ub_pet_wnd_right_updata;

Misc::RawDataContainer com_button_centerdata;
Misc::RawDataContainer com_button_center_focusdata;
Misc::RawDataContainer com_button_leftdata;
Misc::RawDataContainer com_button_left_focusdata;
Misc::RawDataContainer com_button_rightdata;
Misc::RawDataContainer com_button_right_focusdata;


Misc::RawDataContainer menu_main_icondata;
Misc::RawDataContainer menu_main_icon_hoverdata;

Misc::RawDataContainer menu_discord_foucs;
Misc::RawDataContainer menu_discord_icon_hover;

Misc::RawDataContainer facebook_icondata;
Misc::RawDataContainer facebook_icon_hoverdata;

Misc::RawDataContainer menu_chest_icon;
Misc::RawDataContainer menu_chest_icon_hoverdata;

Misc::RawDataContainer menu_chest_button_take_hover;
Misc::RawDataContainer menu_chest_button_take_normal;
Misc::RawDataContainer menu_chest_button_take_press;
Misc::RawDataContainer menu_chest_content;
Misc::RawDataContainer menu_chest_items_tab;

Misc::RawDataContainer menu_chest_item_take;
Misc::RawDataContainer menu_chest_item_take_hover;
Misc::RawDataContainer menu_chest_item_take_press;

Misc::RawDataContainer menu_pandora_bg;


Misc::RawDataContainer com_scroll_bar_bg_data;
Misc::RawDataContainer com_scroll_arrow_up_data;
Misc::RawDataContainer com_scroll_arrow_up_focus_data;
Misc::RawDataContainer com_scroll_arrow_down_data;
Misc::RawDataContainer com_scroll_arrow_down_focus_data;
Misc::RawDataContainer com_scroll_button_data;
Misc::RawDataContainer com_scroll_button_focus_data;


Misc::RawDataContainer com_left_arrowdata;
Misc::RawDataContainer com_left_arrow_disabledata;
Misc::RawDataContainer com_left_arrow_focusdata;
Misc::RawDataContainer com_left_arrow_pressdata;
Misc::RawDataContainer com_right_arrowdata;
Misc::RawDataContainer com_right_arrow_disabledata;
Misc::RawDataContainer com_right_arrow_focusdata;
Misc::RawDataContainer com_right_arrow_pressdata;
Misc::RawDataContainer paginator_bgdata;

//Main Menu
Misc::RawDataContainer main_menu_bgdata;
//Menu Close Button
Misc::RawDataContainer main_menu_button_closedata;
Misc::RawDataContainer main_menu_button_close_hoverdata;
Misc::RawDataContainer main_menu_button_close_pressdata;
//Title Manager Button
Misc::RawDataContainer main_menu_tmanagerbutton_data;
Misc::RawDataContainer main_menu_tmanagerbutton_hoverdata;
Misc::RawDataContainer main_menu_tmanagerbutton_pressdata;
//Unique Status button
Misc::RawDataContainer main_menu_ustatusbutton_data;
Misc::RawDataContainer main_menu_ustatusbutton_hoverdata;
Misc::RawDataContainer main_menu_ustatusbutton_pressdata;
//Event Manager button
Misc::RawDataContainer main_menu_eventmgrbutton_data;
Misc::RawDataContainer main_menu_eventmgrbutton_hoverdata;
Misc::RawDataContainer main_menu_eventmgrbutton_pressdata;
//Grant Name button
Misc::RawDataContainer main_menu_grantnamebutton_data;
Misc::RawDataContainer main_menu_grantnamebutton_hoverdata;
Misc::RawDataContainer main_menu_grantnamebutton_pressdata;
//Custom Title button
Misc::RawDataContainer main_menu_custom_titlebutton_data;
Misc::RawDataContainer main_menu_custom_titlebutton_hoverdata;
Misc::RawDataContainer main_menu_custom_titlebutton_pressdata;
//Ranking button
Misc::RawDataContainer main_menu_rankingbutton_data;
Misc::RawDataContainer main_menu_rankingbutton_hoverdata;
Misc::RawDataContainer main_menu_rankingbutton_pressdata;
//title storage
Misc::RawDataContainer gui_title_manager_bgdata;
Misc::RawDataContainer com_button_use_title;
Misc::RawDataContainer com_button_use_title_hover;
Misc::RawDataContainer com_button_use_title_press;
//Common Buttons
Misc::RawDataContainer com_button_disabled_data;
Misc::RawDataContainer com_button_data;
Misc::RawDataContainer com_button_hover_data;
Misc::RawDataContainer com_button_press_data;
//DPS Meter
Misc::RawDataContainer dps_meter_windowdata;
//Uniques Status
Misc::RawDataContainer unique_status_head_data;
//Top5 Kill Counter
Misc::RawDataContainer top_5_kill_counter_bg;
//Fortress Kill Counter
Misc::RawDataContainer top_5_ftw_kill_counter_bg;
Misc::RawDataContainer btn_ftw_guild_data;
Misc::RawDataContainer btn_ftw_guild_focusdata;
Misc::RawDataContainer btn_ftw_guild_pressdata;
Misc::RawDataContainer btn_ftw_player_data;
Misc::RawDataContainer btn_ftw_player_focusdata;
Misc::RawDataContainer btn_ftw_player_pressdata;

// Custom Buttons
Misc::RawDataContainer btn_custom_canceldata;
Misc::RawDataContainer btn_custom_cancel_hoverdata;
Misc::RawDataContainer btn_custom_cancel_pressdata;
Misc::RawDataContainer btn_custom_changedata;
Misc::RawDataContainer btn_custom_change_hoverdata;
Misc::RawDataContainer btn_custom_change_pressdata;
// Custom Backgrounds
Misc::RawDataContainer bg_custom_grantdata;
Misc::RawDataContainer bg_custom_titledata;
//Custom TextBox
Misc::RawDataContainer custom_textbox_data;
//Custom Frame
Misc::RawDataContainer bg_top_image_bgdata;
Misc::RawDataContainer top_image_close_button;
Misc::RawDataContainer top_image_close_button_hover;
Misc::RawDataContainer top_image_close_button_press;
//Event Manager
Misc::RawDataContainer bg_event_managerdata;

Misc::RawDataContainer btn_new_canceldata;
Misc::RawDataContainer btn_new_cancel_disableddata;
Misc::RawDataContainer btn_new_cancel_hoverdata;
Misc::RawDataContainer btn_new_cancel_pressdata;

Misc::RawDataContainer btn_new_registerdata;
Misc::RawDataContainer btn_new_register_disableddata;
Misc::RawDataContainer btn_new_register_hoverdata;
Misc::RawDataContainer btn_new_register_pressdata;

//Event Manager Buttons
Misc::RawDataContainer btn_lms_eventdata;
Misc::RawDataContainer btn_lms_event_hoverdata;
Misc::RawDataContainer btn_lms_event_pressdata;

Misc::RawDataContainer btn_crew_eventdata;
Misc::RawDataContainer btn_crew_event_hoverdata;
Misc::RawDataContainer btn_crew_event_pressdata;

Misc::RawDataContainer btn_survival_eventdata;
Misc::RawDataContainer btn_survival_event_hoverdata;
Misc::RawDataContainer btn_survival_event_pressdata;

Misc::RawDataContainer btn_perennial_eventdata;
Misc::RawDataContainer btn_perennial_event_hoverdata;
Misc::RawDataContainer btn_perennial_event_pressdata;

Misc::RawDataContainer btn_madness_eventdata;
Misc::RawDataContainer btn_madness_event_hoverdata;
Misc::RawDataContainer btn_madness_event_pressdata;



//Unique Status
Misc::RawDataContainer btn_reloaddata;
Misc::RawDataContainer btn_reload_hoverdata;
Misc::RawDataContainer btn_reload_pressdata;
Misc::RawDataContainer unique_status_bg;

// Pagination
Misc::RawDataContainer btn_paginator_leftdata;
Misc::RawDataContainer btn_paginator_rightdata;
Misc::RawDataContainer btn_paginator_left_hoverdata;
Misc::RawDataContainer btn_paginator_left_pressdata;
Misc::RawDataContainer btn_paginator_right_hoverdata;
Misc::RawDataContainer btn_paginator_right_pressdata;


//EventTime
Misc::RawDataContainer event_times_bg;

//LockSystem
Misc::RawDataContainer AccountLocked_bg;
Misc::RawDataContainer AccountLock;

//Check Box
Misc::RawDataContainer com_checkbutton_offdata;
Misc::RawDataContainer com_checkbutton_ondata;


//New Look

Misc::RawDataContainer customTitle_btn;
Misc::RawDataContainer customTitle_btn_hover;
Misc::RawDataContainer customTitle_btn_press;
Misc::RawDataContainer customTitle_btn_disable;

Misc::RawDataContainer discord_btn;
Misc::RawDataContainer discord_btn_hover;
Misc::RawDataContainer discord_btn_press;
Misc::RawDataContainer discord_btn_disable;

Misc::RawDataContainer eventTimes_btn;
Misc::RawDataContainer eventTimes_btn_hover;
Misc::RawDataContainer eventTimes_btn_press;
Misc::RawDataContainer eventTimes_btn_disable;

Misc::RawDataContainer facebook_btn;
Misc::RawDataContainer facebook_btn_hover;
Misc::RawDataContainer facebook_btn_press;
Misc::RawDataContainer facebook_btn_disable;

Misc::RawDataContainer grantName_btn;
Misc::RawDataContainer grantName_btn_hover;
Misc::RawDataContainer grantName_btn_press;
Misc::RawDataContainer grantName_btn_disable;

Misc::RawDataContainer dynamicShop_btn;
Misc::RawDataContainer dynamicShop_btn_hover;
Misc::RawDataContainer dynamicShop_btn_press;
Misc::RawDataContainer dynamicShop_btn_disable;

Misc::RawDataContainer title;

Misc::RawDataContainer newMenu_bg;

Misc::RawDataContainer titleManager_btn;
Misc::RawDataContainer titleManager_btn_hover;
Misc::RawDataContainer titleManager_btn_press;
Misc::RawDataContainer titleManager_btn_disable;

Misc::RawDataContainer uniqueStatus_btn;
Misc::RawDataContainer uniqueStatus_btn_hover;
Misc::RawDataContainer uniqueStatus_btn_press;
Misc::RawDataContainer uniqueStatus_btn_disable;

Misc::RawDataContainer website_btn;
Misc::RawDataContainer website_btn_hover;
Misc::RawDataContainer website_btn_press;
Misc::RawDataContainer website_btn_disable;



//sro interface
Misc::RawDataContainer frame_g_action_left_downdata;
Misc::RawDataContainer frame_g_action_left_sidedata;
Misc::RawDataContainer frame_g_action_left_updata;
Misc::RawDataContainer frame_g_action_mid_downdata;
Misc::RawDataContainer frame_g_action_mid_updata;
Misc::RawDataContainer frame_g_action_right_downdata;
Misc::RawDataContainer frame_g_action_right_sidedata;
Misc::RawDataContainer frame_g_action_right_updata;

Misc::RawDataContainer com_newdata;
Misc::RawDataContainer com_new_tab_disable_leftdata;
Misc::RawDataContainer com_new_tab_disable_middata;
Misc::RawDataContainer com_new_tab_disable_rightdata;
Misc::RawDataContainer com_new_tab_off_leftdata;
Misc::RawDataContainer com_new_tab_off_middata;
Misc::RawDataContainer com_new_tab_off_rightdata;
Misc::RawDataContainer com_new_tab_on_leftdata;
Misc::RawDataContainer com_new_tab_on_middata;
Misc::RawDataContainer com_new_tab_on_rightdata;

Misc::RawDataContainer com_bg_tile_mdata;


//dynamic shop

Misc::RawDataContainer title_bardata;





#ifdef Anoha
Misc::RawDataContainer menudata;
Misc::RawDataContainer menu_pressdata;
Misc::RawDataContainer menu_focusdata;

Misc::RawDataContainer discord_guidedata;
Misc::RawDataContainer discord_guide_focusdata;
Misc::RawDataContainer discord_guide_pressdata;

Misc::RawDataContainer facebook_guidedata;
Misc::RawDataContainer facebook_guide_focusdata;
Misc::RawDataContainer facebook_guide_pressdata;

#endif

void ResourceManager::Initialize()
{
	// Form
	bottom_centerdata = g_D3DMisc->GetResource(IDB_PNG1);
	com_windowclose_focusdata = g_D3DMisc->GetResource(IDB_PNG2);
	com_windowclose_pressdata = g_D3DMisc->GetResource(IDB_PNG3);
	com_windowclosedata = g_D3DMisc->GetResource(IDB_PNG4);
	contentdata = g_D3DMisc->GetResource(IDB_PNG5);
	left_borderdata = g_D3DMisc->GetResource(IDB_PNG6);
	left_bottom_begindata = g_D3DMisc->GetResource(IDB_PNG7);
	left_up_borderdata = g_D3DMisc->GetResource(IDB_PNG8);
	right_borderdata = g_D3DMisc->GetResource(IDB_PNG9);
	right_bottom_enddata = g_D3DMisc->GetResource(IDB_PNG10);
	right_up_borderdata = g_D3DMisc->GetResource(IDB_PNG11);
	up_centerdata = g_D3DMisc->GetResource(IDB_PNG12);
	// Panel
	com_bg_tile_cdata = g_D3DMisc->GetResource(IDB_PNG13);
	ub_pet_wnd_left_downdata = g_D3DMisc->GetResource(IDB_PNG14);
	ub_pet_wnd_left_sidedata = g_D3DMisc->GetResource(IDB_PNG15);
	ub_pet_wnd_left_updata = g_D3DMisc->GetResource(IDB_PNG16);
	ub_pet_wnd_mid_downdata = g_D3DMisc->GetResource(IDB_PNG17);
	ub_pet_wnd_mid_updata = g_D3DMisc->GetResource(IDB_PNG18);
	ub_pet_wnd_right_downdata = g_D3DMisc->GetResource(IDB_PNG19);
	ub_pet_wnd_right_sidedata = g_D3DMisc->GetResource(IDB_PNG20);
	ub_pet_wnd_right_updata = g_D3DMisc->GetResource(IDB_PNG21);

	menu_main_icondata = g_D3DMisc->GetResource(IDB_PNG22);
	menu_main_icon_hoverdata = g_D3DMisc->GetResource(IDB_PNG23);

	menu_discord_foucs = g_D3DMisc->GetResource(IDB_PNG147);
	menu_discord_icon_hover = g_D3DMisc->GetResource(IDB_PNG148);

	facebook_icondata = g_D3DMisc->GetResource(IDB_PNG149);
	facebook_icon_hoverdata = g_D3DMisc->GetResource(IDB_PNG150);

	menu_chest_icon = g_D3DMisc->GetResource(IDB_PNG24);
	menu_chest_icon_hoverdata = g_D3DMisc->GetResource(IDB_PNG25);


	com_button_centerdata = g_D3DMisc->GetResource(IDB_PNG26);
	com_button_center_focusdata = g_D3DMisc->GetResource(IDB_PNG27);
	com_button_leftdata = g_D3DMisc->GetResource(IDB_PNG28);
	com_button_left_focusdata = g_D3DMisc->GetResource(IDB_PNG29);
	com_button_rightdata = g_D3DMisc->GetResource(IDB_PNG30);
	com_button_right_focusdata = g_D3DMisc->GetResource(IDB_PNG31);

	menu_chest_button_take_hover = g_D3DMisc->GetResource(IDB_PNG32);
	menu_chest_button_take_normal = g_D3DMisc->GetResource(IDB_PNG33);
	menu_chest_button_take_press = g_D3DMisc->GetResource(IDB_PNG34);

	menu_chest_content = g_D3DMisc->GetResource(IDB_PNG35);
	menu_chest_items_tab = g_D3DMisc->GetResource(IDB_PNG36);
	menu_chest_item_take = g_D3DMisc->GetResource(IDB_PNG37);
	menu_chest_item_take_hover = g_D3DMisc->GetResource(IDB_PNG38);
	menu_chest_item_take_press = g_D3DMisc->GetResource(IDB_PNG39);

	menu_pandora_bg = g_D3DMisc->GetResource(IDB_PNG40);

	com_scroll_arrow_down_data = g_D3DMisc->GetResource(IDB_PNG41);
	com_scroll_arrow_down_focus_data = g_D3DMisc->GetResource(IDB_PNG42);
	com_scroll_arrow_up_data = g_D3DMisc->GetResource(IDB_PNG43);
	com_scroll_arrow_up_focus_data = g_D3DMisc->GetResource(IDB_PNG44);
	com_scroll_bar_bg_data = g_D3DMisc->GetResource(IDB_PNG45);
	com_scroll_button_data = g_D3DMisc->GetResource(IDB_PNG46);
	com_scroll_button_focus_data = g_D3DMisc->GetResource(IDB_PNG47);

	com_left_arrowdata = g_D3DMisc->GetResource(IDB_PNG48);
	com_left_arrow_disabledata = g_D3DMisc->GetResource(IDB_PNG49);
	com_left_arrow_focusdata = g_D3DMisc->GetResource(IDB_PNG50);
	com_left_arrow_pressdata = g_D3DMisc->GetResource(IDB_PNG51);
	com_right_arrowdata = g_D3DMisc->GetResource(IDB_PNG52);
	com_right_arrow_disabledata = g_D3DMisc->GetResource(IDB_PNG53);
	com_right_arrow_focusdata = g_D3DMisc->GetResource(IDB_PNG54);
	com_right_arrow_pressdata = g_D3DMisc->GetResource(IDB_PNG55);
	paginator_bgdata = g_D3DMisc->GetResource(IDB_PNG56);

	//Main menu
	main_menu_bgdata = g_D3DMisc->GetResource(IDB_PNG57);
	//Close buttons
	main_menu_button_closedata = g_D3DMisc->GetResource(IDB_PNG58);
	main_menu_button_close_hoverdata = g_D3DMisc->GetResource(IDB_PNG59);
	main_menu_button_close_pressdata = g_D3DMisc->GetResource(IDB_PNG60);
	//TitleManager button
	main_menu_tmanagerbutton_data = g_D3DMisc->GetResource(IDB_PNG61);
	main_menu_tmanagerbutton_hoverdata = g_D3DMisc->GetResource(IDB_PNG62);
	main_menu_tmanagerbutton_pressdata = g_D3DMisc->GetResource(IDB_PNG63);
	//Unique Status button
	main_menu_ustatusbutton_data = g_D3DMisc->GetResource(IDB_PNG64);
	main_menu_ustatusbutton_hoverdata = g_D3DMisc->GetResource(IDB_PNG65);
	main_menu_ustatusbutton_pressdata = g_D3DMisc->GetResource(IDB_PNG66);
	//Event Manager button
	main_menu_eventmgrbutton_data = g_D3DMisc->GetResource(IDB_PNG67);
	main_menu_eventmgrbutton_hoverdata = g_D3DMisc->GetResource(IDB_PNG68);
	main_menu_eventmgrbutton_pressdata = g_D3DMisc->GetResource(IDB_PNG69);
	//Grant Name button
	main_menu_grantnamebutton_data = g_D3DMisc->GetResource(IDB_PNG70);
	main_menu_grantnamebutton_hoverdata = g_D3DMisc->GetResource(IDB_PNG71);
	main_menu_grantnamebutton_pressdata = g_D3DMisc->GetResource(IDB_PNG72);
	//Custom Title button
	main_menu_custom_titlebutton_data = g_D3DMisc->GetResource(IDB_PNG73);
	main_menu_custom_titlebutton_hoverdata = g_D3DMisc->GetResource(IDB_PNG74);
	main_menu_custom_titlebutton_pressdata = g_D3DMisc->GetResource(IDB_PNG75);
	//Ranking button
	main_menu_rankingbutton_data = g_D3DMisc->GetResource(IDB_PNG76);
	main_menu_rankingbutton_hoverdata = g_D3DMisc->GetResource(IDB_PNG77);
	main_menu_rankingbutton_pressdata = g_D3DMisc->GetResource(IDB_PNG78);
	//Title manager
	gui_title_manager_bgdata = g_D3DMisc->GetResource(IDB_PNG79);
	com_button_use_title = g_D3DMisc->GetResource(IDB_PNG80);
	com_button_use_title_hover = g_D3DMisc->GetResource(IDB_PNG81);
	com_button_use_title_press = g_D3DMisc->GetResource(IDB_PNG82);
	//Common Buttons
	com_button_disabled_data = g_D3DMisc->GetResource(IDB_PNG83);
	com_button_data = g_D3DMisc->GetResource(IDB_PNG84);
	com_button_hover_data = g_D3DMisc->GetResource(IDB_PNG85);
	com_button_press_data = g_D3DMisc->GetResource(IDB_PNG86);
	//DPS meter bg
	dps_meter_windowdata = g_D3DMisc->GetResource(IDB_PNG87);
	//Unique Status head
	unique_status_head_data = g_D3DMisc->GetResource(IDB_PNG88);
	//Top5 kill counter bg
	top_5_kill_counter_bg = g_D3DMisc->GetResource(IDB_PNG89);
	//Fortress Kill Counter
	top_5_ftw_kill_counter_bg = g_D3DMisc->GetResource(IDB_PNG90);
	btn_ftw_guild_data = g_D3DMisc->GetResource(IDB_PNG91);
	btn_ftw_guild_focusdata = g_D3DMisc->GetResource(IDB_PNG92);
	btn_ftw_guild_pressdata = g_D3DMisc->GetResource(IDB_PNG93);
	btn_ftw_player_data = g_D3DMisc->GetResource(IDB_PNG94);
	btn_ftw_player_focusdata = g_D3DMisc->GetResource(IDB_PNG95);
	btn_ftw_player_pressdata = g_D3DMisc->GetResource(IDB_PNG96);

	custom_textbox_data = g_D3DMisc->GetResource(IDB_PNG97);

	// Custom Buttons
	btn_custom_canceldata = g_D3DMisc->GetResource(IDB_PNG98);
	btn_custom_cancel_hoverdata = g_D3DMisc->GetResource(IDB_PNG99);
	btn_custom_cancel_pressdata = g_D3DMisc->GetResource(IDB_PNG100);
	btn_custom_changedata = g_D3DMisc->GetResource(IDB_PNG101);
	btn_custom_change_hoverdata = g_D3DMisc->GetResource(IDB_PNG102);
	btn_custom_change_pressdata = g_D3DMisc->GetResource(IDB_PNG103);

	//Custom Backgrounds
	bg_custom_grantdata = g_D3DMisc->GetResource(IDB_PNG104);
	bg_custom_titledata = g_D3DMisc->GetResource(IDB_PNG105);

	//Custom Frame
	bg_top_image_bgdata = g_D3DMisc->GetResource(IDB_PNG106);
	top_image_close_button = g_D3DMisc->GetResource(IDB_PNG107);
	top_image_close_button_hover = g_D3DMisc->GetResource(IDB_PNG108);
	top_image_close_button_press = g_D3DMisc->GetResource(IDB_PNG109);
	//Event Manager
	bg_event_managerdata = g_D3DMisc->GetResource(IDB_PNG110);

	btn_new_canceldata = g_D3DMisc->GetResource(IDB_PNG111);
	btn_new_cancel_disableddata = g_D3DMisc->GetResource(IDB_PNG112);
	btn_new_cancel_hoverdata = g_D3DMisc->GetResource(IDB_PNG113);
	btn_new_cancel_pressdata = g_D3DMisc->GetResource(IDB_PNG114);

	btn_new_registerdata = g_D3DMisc->GetResource(IDB_PNG115);
	btn_new_register_disableddata = g_D3DMisc->GetResource(IDB_PNG116);
	btn_new_register_hoverdata = g_D3DMisc->GetResource(IDB_PNG117);
	btn_new_register_pressdata = g_D3DMisc->GetResource(IDB_PNG118);


	//Unique Status
	btn_reloaddata = g_D3DMisc->GetResource(IDB_PNG122);
	btn_reload_hoverdata = g_D3DMisc->GetResource(IDB_PNG123);
	btn_reload_pressdata = g_D3DMisc->GetResource(IDB_PNG124);
	unique_status_bg = g_D3DMisc->GetResource(IDB_PNG125);

	//Paginator
	btn_paginator_leftdata = g_D3DMisc->GetResource(IDB_PNG126);
	btn_paginator_rightdata = g_D3DMisc->GetResource(IDB_PNG127);
	btn_paginator_left_hoverdata = g_D3DMisc->GetResource(IDB_PNG128);
	btn_paginator_left_pressdata = g_D3DMisc->GetResource(IDB_PNG129);
	btn_paginator_right_hoverdata = g_D3DMisc->GetResource(IDB_PNG130);
	btn_paginator_right_pressdata = g_D3DMisc->GetResource(IDB_PNG131);
	//Event Manager buttons
	btn_lms_eventdata = g_D3DMisc->GetResource(IDB_PNG135);
	btn_lms_event_hoverdata = g_D3DMisc->GetResource(IDB_PNG136);
	btn_lms_event_pressdata = g_D3DMisc->GetResource(IDB_PNG137);

	btn_crew_eventdata = g_D3DMisc->GetResource(IDB_PNG132);
	btn_crew_event_hoverdata = g_D3DMisc->GetResource(IDB_PNG133);
	btn_crew_event_pressdata = g_D3DMisc->GetResource(IDB_PNG134);

	btn_survival_eventdata = g_D3DMisc->GetResource(IDB_PNG144);
	btn_survival_event_hoverdata = g_D3DMisc->GetResource(IDB_PNG145);
	btn_survival_event_pressdata = g_D3DMisc->GetResource(IDB_PNG146);

	btn_perennial_eventdata = g_D3DMisc->GetResource(IDB_PNG141);
	btn_perennial_event_hoverdata = g_D3DMisc->GetResource(IDB_PNG142);
	btn_perennial_event_pressdata = g_D3DMisc->GetResource(IDB_PNG143);

	btn_madness_eventdata = g_D3DMisc->GetResource(IDB_PNG138);
	btn_madness_event_hoverdata = g_D3DMisc->GetResource(IDB_PNG139);
	btn_madness_event_pressdata = g_D3DMisc->GetResource(IDB_PNG140);

	//event time
	event_times_bg = g_D3DMisc->GetResource(IDB_PNG152);
	//event time

	//Lock System
	AccountLocked_bg = g_D3DMisc->GetResource(IDB_PNG162);
	AccountLock = g_D3DMisc->GetResource(IDB_PNG165);

	
	//Check Box
	com_checkbutton_offdata = g_D3DMisc->GetResource(IDB_PNG163);
	com_checkbutton_ondata = g_D3DMisc->GetResource(IDB_PNG164);



	// New Look
	customTitle_btn = g_D3DMisc->GetResource(ID_customTitle_btn);
	customTitle_btn_hover = g_D3DMisc->GetResource(ID_customTitle_btn_hover);
	customTitle_btn_press = g_D3DMisc->GetResource(ID_customTitle_btn_press);
	customTitle_btn_disable = g_D3DMisc->GetResource(ID_customTitle_btn_disable);

	discord_btn = g_D3DMisc->GetResource(ID_discord_btn);
	discord_btn_hover = g_D3DMisc->GetResource(ID_discord_btn_hover);
	discord_btn_press = g_D3DMisc->GetResource(ID_discord_btn_press);
	discord_btn_disable = g_D3DMisc->GetResource(ID_discord_btn_disable);

	eventTimes_btn = g_D3DMisc->GetResource(ID_eventTimes_btn);
	eventTimes_btn_hover = g_D3DMisc->GetResource(ID_eventTimes_btn_hover);
	eventTimes_btn_press = g_D3DMisc->GetResource(ID_eventTimes_btn_press);
	eventTimes_btn_disable = g_D3DMisc->GetResource(ID_eventTimes_btn_disable);

	facebook_btn = g_D3DMisc->GetResource(ID_facebook_btn);
	facebook_btn_hover = g_D3DMisc->GetResource(ID_facebook_btn_hover);
	facebook_btn_press = g_D3DMisc->GetResource(ID_facebook_btn_press);
	facebook_btn_disable = g_D3DMisc->GetResource(ID_facebook_btn_disable);

	grantName_btn = g_D3DMisc->GetResource(ID_grantName_btn);
	grantName_btn_hover = g_D3DMisc->GetResource(ID_grantName_btn_hover);
	grantName_btn_press = g_D3DMisc->GetResource(ID_grantName_btn_press);
	grantName_btn_disable = g_D3DMisc->GetResource(ID_grantName_btn_disable);


	dynamicShop_btn = g_D3DMisc->GetResource(ID_dynamicShop_btn);
	dynamicShop_btn_hover = g_D3DMisc->GetResource(ID_dynamicShop_btn_hover);
	dynamicShop_btn_press = g_D3DMisc->GetResource(ID_dynamicShop_btn_press);
	dynamicShop_btn_disable = g_D3DMisc->GetResource(ID_dynamicShop_btn_disable);

	title = g_D3DMisc->GetResource(ID_title);

	newMenu_bg = g_D3DMisc->GetResource(ID_newMenu_bg);

	titleManager_btn = g_D3DMisc->GetResource(ID_titleManager_btn);
	titleManager_btn_hover = g_D3DMisc->GetResource(ID_titleManager_btn_hover);
	titleManager_btn_press = g_D3DMisc->GetResource(ID_titleManager_btn_press);
	titleManager_btn_disable = g_D3DMisc->GetResource(ID_titleManager_btn_disable);

	uniqueStatus_btn = g_D3DMisc->GetResource(ID_uniqueStatus_btn);
	uniqueStatus_btn_hover = g_D3DMisc->GetResource(ID_uniqueStatus_btn_hover);
	uniqueStatus_btn_press = g_D3DMisc->GetResource(ID_uniqueStatus_btn_press);
	uniqueStatus_btn_disable = g_D3DMisc->GetResource(ID_uniqueStatus_btn_disable);

	website_btn = g_D3DMisc->GetResource(ID_website_btn);
	website_btn_hover = g_D3DMisc->GetResource(ID_website_btn_hover);
	website_btn_press = g_D3DMisc->GetResource(ID_website_btn_press);
	website_btn_disable = g_D3DMisc->GetResource(ID_website_btn_disable);

	//sro interface
	frame_g_action_left_downdata = g_D3DMisc->GetResource(ID_frame_g_action_left_down);
	frame_g_action_left_sidedata = g_D3DMisc->GetResource(ID_frame_g_action_left_side);
	frame_g_action_left_updata = g_D3DMisc->GetResource(ID_frame_g_action_left_up);
	frame_g_action_mid_downdata = g_D3DMisc->GetResource(ID_frame_g_action_mid_down);
	frame_g_action_mid_updata = g_D3DMisc->GetResource(ID_frame_g_action_mid_up);
	frame_g_action_right_downdata = g_D3DMisc->GetResource(ID_frame_g_action_right_down);
	frame_g_action_right_sidedata = g_D3DMisc->GetResource(ID_frame_g_action_right_side);
	frame_g_action_right_updata = g_D3DMisc->GetResource(ID_frame_g_action_right_up);

	com_newdata = g_D3DMisc->GetResource(ID_com_new);
	com_new_tab_disable_leftdata = g_D3DMisc->GetResource(ID_com_new_tab_disable_left);
	com_new_tab_disable_middata = g_D3DMisc->GetResource(ID_com_new_tab_disable_mid);
	com_new_tab_disable_rightdata = g_D3DMisc->GetResource(ID_com_new_tab_disable_right);
	com_new_tab_off_leftdata = g_D3DMisc->GetResource(ID_com_new_tab_off_left);
	com_new_tab_off_middata = g_D3DMisc->GetResource(ID_com_new_tab_off_mid);
	com_new_tab_off_rightdata = g_D3DMisc->GetResource(ID_com_new_tab_off_right);
	com_new_tab_on_leftdata = g_D3DMisc->GetResource(ID_com_new_tab_on_left);
	com_new_tab_on_middata = g_D3DMisc->GetResource(ID_com_new_tab_on_mid);
	com_new_tab_on_rightdata = g_D3DMisc->GetResource(ID_com_new_tab_on_right);

	com_bg_tile_mdata = g_D3DMisc->GetResource(ID_com_bg_tile_m);

	//dynamic shop

	title_bardata = g_D3DMisc->GetResource(ID_titles_bar);


#ifdef Anoha
	 menudata = g_D3DMisc->GetResource(IDB_PNG159);
	 menu_pressdata = g_D3DMisc->GetResource(IDB_PNG161);
	 menu_focusdata = g_D3DMisc->GetResource(IDB_PNG160);

	 discord_guidedata = g_D3DMisc->GetResource(IDB_PNG153);
	 discord_guide_focusdata = g_D3DMisc->GetResource(IDB_PNG154);
	 discord_guide_pressdata = g_D3DMisc->GetResource(IDB_PNG155);

	 facebook_guidedata = g_D3DMisc->GetResource(IDB_PNG156);
	 facebook_guide_focusdata = g_D3DMisc->GetResource(IDB_PNG157);
	 facebook_guide_pressdata = g_D3DMisc->GetResource(IDB_PNG158);

#endif
}

void* ResourceManager::LoadTextureFromPk2(const n_string &path)
{
	return reinterpret_cast<void*(__cdecl*)(const n_string*)>(0x005008F0)(&path);
}
