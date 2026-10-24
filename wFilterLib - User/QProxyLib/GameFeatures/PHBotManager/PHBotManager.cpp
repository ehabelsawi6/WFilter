#include "PHBotManager.h"
#include "../../GameMain/GameMain.h"

const DWORD cdwPHBotOffset_1 = 0x00795AE5 + 1;
const DWORD cdwPHBotOffset_2 = 0x00795AFA + 1;
const DWORD cdwPHBotOffset_3 = 0x00796160 + 1;
const DWORD cdwPHBotOffset_4 = 0x00796175 + 1;

void PHBotManager::Handle(CMsgStreamBuffer* packet)
{
	auto multipler = packet->Read<uint8_t>();
	auto splitter = packet->Read<uint8_t>();
	auto opcode = packet->Read<uint64_t>();
	auto Custom_Opcode = (opcode - splitter) / multipler;

	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(cdwPHBotOffset_1), sizeof(uint16_t));
	*(uint16_t*)(cdwPHBotOffset_1) = Custom_Opcode;
	g_MemoryHelper->ReProtect();
	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(cdwPHBotOffset_2), sizeof(uint16_t));
	*(uint16_t*)(cdwPHBotOffset_2) = Custom_Opcode;
	g_MemoryHelper->ReProtect();
	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(cdwPHBotOffset_3), sizeof(uint16_t));
	*(uint16_t*)(cdwPHBotOffset_3) = Custom_Opcode;
	g_MemoryHelper->ReProtect();
	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(cdwPHBotOffset_4), sizeof(uint16_t));
	*(uint16_t*)(cdwPHBotOffset_4) = Custom_Opcode;
	g_MemoryHelper->ReProtect();
}

PHBotManager::PHBotManager()
{
}