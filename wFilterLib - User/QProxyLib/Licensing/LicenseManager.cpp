#include "LicenseManager.h"

std::string LicenseManager::RemoteHost;

void LicenseManager::gw_detour_call(const char *format, ...) {
	va_list args;
	va_start(args, format);

	char *host = va_arg(args, char*);
	// Do stuff between here
	if (strcmp(host, VMProtectDecryptStringA(RemoteHost.c_str())) != 0) {
		// epic crash
		// xDD
		if (strcmp(host, VMProtectDecryptStringA("127.0.0.1")) == 0)
		{
			return;
		}
		else
		{
			exit(EXIT_SUCCESS);
		}
	}
	va_end(args);
}
void LicenseManager::Initialize(std::string GatewayRemoteIP)
{
	this->RemoteHost = GatewayRemoteIP;
	g_MemoryHelper->replaceOffset(0x00844A87, (int)&gw_detour_call);
}
