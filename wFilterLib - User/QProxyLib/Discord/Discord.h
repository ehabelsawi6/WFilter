#ifndef Q_DISCORD_ADDON
#define Q_DISCORD_ADDON
#endif

#include "../stdafx.h"
#include <discord_rpc.h>
class Discord
{
public:
	void Initialize();
	void Update();
	void UpdateState(std::string State);
	void UpdateDetails(std::string Detail);
	bool Discord::str_ends_with(std::string const& value, std::string const& suffix);
	bool Discord::str_starts_with(std::string const& value, std::string const& preffix);

private:
	DiscordRichPresence m_discordPresence;
};
