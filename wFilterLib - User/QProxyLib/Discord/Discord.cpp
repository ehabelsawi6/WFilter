#include "Discord.h"
#include "../GameStuff/CICPlayer/CICPlayer.h"

extern std::string g_DiscordLargeImageText;
extern std::string g_DiscordStatusMessage;
extern std::string g_DiscordDetails;
extern std::string g_Discord_App_Id;



void Discord::Initialize()
{
	/*DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	handlers.ready = handleDiscordReady;
	handlers.disconnected = handleDiscordDisconnected;
	handlers.errored = handleDiscordError;
	handlers.joinGame = handleDiscordJoin;
	handlers.spectateGame = handleDiscordSpectate;
	handlers.joinRequest = handleDiscordJoinRequest;*/
	Discord_Initialize(g_Discord_App_Id.c_str(),NULL /*&handlers*/, 1, NULL);
}

void Discord::Update()
{
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		);
	memset(&m_discordPresence, 0, sizeof(m_discordPresence));
	m_discordPresence.state = g_DiscordStatusMessage.c_str();
	m_discordPresence.details = g_DiscordDetails.c_str();
	m_discordPresence.startTimestamp = ms.count();
	m_discordPresence.largeImageKey = "logox";
	m_discordPresence.largeImageText = g_DiscordLargeImageText.c_str();
	m_discordPresence.smallImageKey = "logo";
	m_discordPresence.smallImageText = "";
	//m_discordPresence.
	Discord_UpdatePresence(&m_discordPresence);
}

void Discord::UpdateState(std::string State)
{
	if (g_DiscordStatusMessage != State)
	{
#ifdef DevConsole
		g_DiscordStatusMessage = "Stage: Development";
#endif
#ifndef DevConsole
		g_DiscordStatusMessage = State;
#endif
		if (g_CICPlayer && g_CICPlayer->GetJobStatus() == 4)
		{
			// Set keyword image
			if (g_DiscordStatusMessage == "Jangan")
				m_discordPresence.largeImageKey = "loading_zangan";
			
			else if (g_DiscordStatusMessage == "Western China Donwhang") 
				m_discordPresence.largeImageKey = "loading_dunwhang";
			
			else if (g_DiscordStatusMessage == "Hotan") 
				m_discordPresence.largeImageKey = "loading_hotan";
			
			else if (g_DiscordStatusMessage == "Samarkand") 
				m_discordPresence.largeImageKey = "loading_samarkand";
			
			else if (g_DiscordStatusMessage == "Constantinople") 
				m_discordPresence.largeImageKey = "loading_constantinople";
			
			else if (g_DiscordStatusMessage == "Alexandria") 
				m_discordPresence.largeImageKey = "loading_alex";
			
			else if (g_DiscordStatusMessage == "Baghdad") 
				m_discordPresence.largeImageKey = "loading_baghdad_2011";
			
			else if (g_DiscordStatusMessage == "Donwhang Stone Cave") 
				m_discordPresence.largeImageKey = "loading_dungeons_donwhang";
			
			else if (str_starts_with(g_DiscordStatusMessage, "Underground Level")) 
				m_discordPresence.largeImageKey = "loading_royalmausoleum";
			
			else if (g_DiscordStatusMessage == "Pharaoh tomb") 
				m_discordPresence.largeImageKey = "loading_pharaoh";
			
			else if (g_DiscordStatusMessage == "Togui Village") 
				m_discordPresence.largeImageKey = "loading_togui_2011";
			
			else if (g_DiscordStatusMessage == "Flame Mountain") 
				m_discordPresence.largeImageKey = "loading_flame_2011";
			
			else if (str_ends_with(g_DiscordStatusMessage, " of the Shipwreck")) 
				m_discordPresence.largeImageKey = "loading_wreck_2011";
			
			else if (g_DiscordStatusMessage == "Jupiter Temple") 
				m_discordPresence.largeImageKey = "loading_jupiter_field_2011";
			
			else if (str_ends_with(g_DiscordStatusMessage, "'s Room")) 
				m_discordPresence.largeImageKey = "loading_hall_2011";
			
			else if (g_DiscordStatusMessage == "Zealots Hideout") 
				m_discordPresence.largeImageKey = "loading_hideout_2011";
			
			else if (g_DiscordStatusMessage == "Petra (Dungeon)") 
				m_discordPresence.largeImageKey = "loading_petra_2011";
			
			else if (g_DiscordStatusMessage == "Devil's Garden (Dungeon)") 
				m_discordPresence.largeImageKey = "loading_garden_2011";
			
			else if (g_DiscordStatusMessage == "In Game")
				m_discordPresence.largeImageKey = "logo";
			
		}
		else
		{
			m_discordPresence.largeImageKey = "logo";
		}

		m_discordPresence.state = g_DiscordStatusMessage.c_str();
		m_discordPresence.details = g_DiscordDetails.c_str();
		m_discordPresence.largeImageText = g_DiscordLargeImageText.c_str();
		Discord_UpdatePresence(&m_discordPresence);
	}
}

void Discord::UpdateDetails(std::string Detail)
{
	if (g_DiscordDetails != Detail)
	{
#ifdef DevConsole
		g_DiscordDetails = "Stage: Development";
#endif
#ifndef DevConsole
		g_DiscordDetails = Detail;
#endif
		m_discordPresence.state = g_DiscordStatusMessage.c_str();
		m_discordPresence.details = g_DiscordDetails.c_str();
		m_discordPresence.largeImageText = g_DiscordLargeImageText.c_str();
		Discord_UpdatePresence(&m_discordPresence);
	}
}
// String helpers!
// Check if the string starts equal to the given string
bool Discord::str_starts_with(std::string const& value, std::string const& preffix) {
	return value.rfind(preffix, 0) == 0;
}
// Check if the string ends equal to the given string
bool Discord::str_ends_with(std::string const& value, std::string const& suffix) {
	if (value.length() >= suffix.length())
		return value.compare(value.length() - suffix.length(), suffix.length(), suffix) == 0;
	return false;
}
