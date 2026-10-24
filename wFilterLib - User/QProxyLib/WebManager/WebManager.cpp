#include "WebManager.h"
#include "../Includes/includes.h"
#include "../GameMain/GameMain.h"
//#define CURL_STATICLIB
//#include "../../curl/curl.h"
//#pragma comment(lib, "libcurl_a.lib")
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "advapi32.lib")


void WebManager::Initialize()
{
	std::thread t([&] {
		while (true)
		{
			Sleep(500);
			Update();
		}
		});
	t.detach();
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}


void WebManager::Update()
{
	try
	{
		/*CURL* curl;
		CURLcode res;
		std::string readBuffer;

		curl = curl_easy_init();
		if (curl) {
			std::string url = VMProtectDecryptStringA("http://worldtimeapi.org/api/timezone/europe/berlin.txt");
			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			std::vector<std::string> vecta;
			auto list = g_StringHelper->split(readBuffer, '\n');
			for (auto index : list)
			{
				if (index._Starts_with("unixtime:"))
					g_GlobalDataMgr->currDate = std::stoul(index.erase(0, 10));
			}
		}*/
	}
	catch (const std::exception & e)
	{
		std::cerr << "Request failed, error: " << e.what() << '\n';
	}
}