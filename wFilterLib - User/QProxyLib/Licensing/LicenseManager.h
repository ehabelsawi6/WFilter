#pragma once
#include "../GameMain/GameMain.h"

class LicenseManager
{
public:
	void Initialize(std::string GatewayRemoteIP);
	static void gw_detour_call(const char *format, ...);
private:
	static std::string RemoteHost;
};