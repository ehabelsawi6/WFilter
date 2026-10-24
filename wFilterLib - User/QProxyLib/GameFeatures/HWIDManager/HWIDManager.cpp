#include "HWIDManager.h"
#include "../../Character/Character.h"
#include "../../Helpers/md5.h"
#include "RegistryManager.h"
#include "../../Helpers/Random.h"

using namespace winreg;


CMsgStreamBuffer* replacerPacket(CMsgStreamBuffer* old_packet)
{
	CMsgStreamBuffer* output = new CMsgStreamBuffer(old_packet->GetID());

	auto end = old_packet->GetLength();

	auto split = (end / 8);

	if (split > 0)
	{
		for (size_t i = 0; i < split; i++)
		{
			output->Write<uint64_t>(old_packet->Read<uint64_t>());
		}
		auto remaining = end - (split * 8);

		auto split_ushort = (remaining / 2);

		for (size_t i = 0; i < split_ushort; i++)
		{
			output->Write<uint16_t>(old_packet->Read<uint16_t>());
		}

		auto lastbytes = (remaining - (split_ushort * 2));

		for (size_t i = 0; i < lastbytes; i++)
		{
			output->Write<uint8_t>(old_packet->Read<uint8_t>());
		}
	}

	return output;
}



void HWIDManager::Initialize()
{
	int nSize = VMProtectGetCurrentHWID(NULL, 0);
	char* hwid = new char[nSize];
	VMProtectGetCurrentHWID(hwid, nSize);
	std::string temp_hwid(hwid);
	std::free(hwid);

	/*if (nSize <= 58)
	{
		int for_loop = (58 - nSize);
		for (size_t i = 0; i < for_loop; i++)
		{
			temp_hwid.append("1");
		}
	}*/

	std::wstring directory = VMProtectDecryptStringW(L"SOFTWARE\\Microsoft\\.NETFramework");

	RegKey key{ HKEY_LOCAL_MACHINE, directory };

	auto CurrentHwid = key.GetStringValue(VMProtectDecryptStringW(L"DbgHashSetData"));

	if (CurrentHwid.length() == 0) // its the first time that player opens the client.
	{
		key.SetStringValue(VMProtectDecryptStringW(L"DbgHashSetData"), VMProtectDecryptStringW(std::wstring(temp_hwid.begin(), temp_hwid.end()).c_str()));
		CurrentHwid = key.GetStringValue(VMProtectDecryptStringW(L"DbgHashSetData"));

		if (CurrentHwid.length() == 0)
		{
			CurrentHwid = std::wstring(temp_hwid.begin(), temp_hwid.end()).c_str();

			MessageBoxW(NULL, VMProtectDecryptStringW(L"Error occured while initializing the client, Please run the game or bots as administrator or contact with Game admins. [Error Code : 5]"), VMProtectDecryptStringW(L"ERROR"), NULL);
			exit(0);
			return;
		}
	}
	
	this->packet = new CMsgStreamBuffer(std::stoi(VMProtectDecryptStringA("34962")));

	int total1 = 147483647, total2 = 147483647, total3 = 147483647;

	for (uint8_t i = 0; i < 5; i++)
	{
		uint8_t rnd = Random::Generate(1, 255);
		packet->Write<uint8_t>(rnd);
		total1 += (rnd * 3);
	}

	packet->Write<uint32_t>(total1);

	packet->Write<uint16_t>(30241 + (uint16_t)CurrentHwid.length());

	for (size_t i = 0; i < CurrentHwid.length(); i++)
	{
		packet->Write<uint8_t>(CurrentHwid[i]);
		total2 += CurrentHwid[i] * 2;
	}

	packet->Write<uint32_t>(total2);


	for (size_t i = 0; i < 10; i++)
	{
			int rnd_num = 151;
			//else its not a phbot but still, do check here also.
			rnd_num = Random::Generate(151, 255);
			packet->Write<uint8_t>(rnd_num);
			total3 += (rnd_num * 2);
	}

	packet->Write<uint32_t>(total3);

	std::stringstream DynamicHwidInfo;
	DynamicHwidInfo << std::to_string(g_Character->Info->RefObjID)
					<< std::to_string(g_Character->Info->CurLevel)
					<< std::to_string(g_Character->Info->ServerTime)
					<< std::to_string(g_Character->Info->ExpOffset)
					<< std::to_string(g_Character->Info->SExpOffset)
					<< std::to_string(g_Character->Info->Gold)
					<< std::to_string(g_Character->Info->SkillPoint);

	int total_dynamic = 147483647;

	std::string encoded_hwid = md5(DynamicHwidInfo.str());

	for (size_t i = 0; i < encoded_hwid.length(); i++)
	{
		packet->Write<uint8_t>(encoded_hwid[i] + 1);

		total_dynamic += (encoded_hwid[i] * 2);
	}

	packet->Write<uint32_t>(total_dynamic);

	packet = replacerPacket(packet);

	packet->SendToServer();

}
void HWIDManager::Free()
{
	std::free(packet);
}