#pragma once
#ifndef MSG_STREAM_BUFFER_H
#define MSG_STREAM_BUFFER_H

#include "../stdafx.h"

#include "MemPool.h"
#include "MemPoolManager.h"
/*
* You can see there is some flag they put in the send function... seems thats some kind of
* legacy feature they used... or not complete? the addr for on/off switch is 0x00EECD50.
* Setting it to 1 seem to force client to use memory pool when sending messages,
* doing some re-allocations(copying) bla ba... pretty weird. maybe thats for massive msgs...
*/
namespace MsgOpcodes
{
	enum MsgOpcodes : uint16_t
	{
		CLIENT_CUSTOM = 0x1337,
		SERVER_CUSTOM = 0x1338,
		AFK_BUBBLES = 0x3131,
		SERVER_CHAT = 0x3026,
		SERVER_TELEPORT = 0x34B5,
		SERVER_CHARACTER_SCREEN = 0xB007,
		SERVER_CHAR_DATA_BEGIN = 0x34A5,
		SERVER_CHAR_DATA = 0x3013,
		SERVER_CHAR_DATA_END = 0x34A6,
		SERVER_INVENTORY_RESPONSE = 0xB034,
		SERVER_ENTITY_UPDATE_HWANLEVEL = 0x30DF,
		SERVER_GROUP_SPAWN_BEGIN = 0x3017,
		SERVER_GROUP_SPAWN_DATA = 0x3019,
		SERVER_GROUP_SPAWN_END = 0x3018,
		SERVER_SINGLE_OBJECT_DESPAWN = 0x3016,
		SERVER_SKILL_CASTING_DATA = 0xB070,
		SERVER_UNIQUE_NOTIFY = 0x300C,
		SERVER_ENVIROMENT_CELESTIAL_POSITION = 0x3020,
		SERVER_ENTITY_LEVEL_UP = 0x3054
	};
}
namespace MsgOpcodeTypes
{
	enum MsgOpcodeTypes : uint8_t
	{
		ClientInfo = 0x01,
		AntiPHBOT = 55,
		Chest_Response = 0x17,
		Chest_RequestItem = 0x18,
		Chest_RequestList = 0x19,
		Chest_RequestAllList = 0x20,
		TitlesList = 0x21,
		TitlesListRemoveRequest = 0x22,
		TitlesListChangeRequest = 0x23,
		UniqueStatusRequest = 0x24,
		UniqueStatusResponse = 0x25,
		OnCharacterInfoRequest = 0x40,
		OnCharacterInfo = 0x41,
		OnJobStatusInfo = 0x56,
		OnJobStatusBuyCoins = 0x57,
		OnJobStatusBuyImmo = 0x58,
		OnJobStatusBuyBox = 0x59,
		OnEventTimesRequest = 0x60,
		EventTimesResponse = 0x61,
		DShopRequest = 0x30,
		DShopResponse = 0x31

	};
} 
struct SMsgStreamBufferNode;

#define MSG_NODE_BUFFER_SIZE 4096
#define __MSG_NODE_POOL CMemPool<SMsgStreamBufferNode*>*

struct SMsgStreamBufferNode
{
private:
#pragma pack(push, 1)
	SMsgStreamBufferNode* m_pNext;
	uint8_t m_buffer[MSG_NODE_BUFFER_SIZE];
	uint8_t* m_pBuffer;
	uint32_t m_unk1;
	__MSG_NODE_POOL m_pool;
#pragma pack(pop)

public:
	SMsgStreamBufferNode()
	{
		m_pNext = nullptr;
		m_pBuffer = &m_buffer[0];
		m_unk1 = 0;
		m_pool = nullptr;
	}

	SMsgStreamBufferNode* GetNextNode() const { return m_pNext; }
	uint8_t* GetBuffer() const { return m_pBuffer; }
	__MSG_NODE_POOL GetPool() const { return m_pool; }

	void* operator new(size_t size)
	{
		auto pool = CMemPoolManager::GetPool<__MSG_NODE_POOL>();
		return pool->AllocItem();
	}
}; //sizeof = 0x100C

class CMsgStreamBuffer
{
private:
	using FN_CONSTRUCTOR = const CMsgStreamBuffer* (__thiscall*)(CMsgStreamBuffer*, uint16_t id);
	using FN_DESTRUCTOR = void(__thiscall*)(CMsgStreamBuffer*);
	using FN_READ_BYTES = uint32_t(__thiscall*)(CMsgStreamBuffer*, uintptr_t dest, uint32_t count);
	using FN_WRITE_BYTES = uintptr_t(__thiscall*)(CMsgStreamBuffer*, uintptr_t src, uint32_t count);
	using FN_SEND_TO_SERVER = uintptr_t(__cdecl*)(CMsgStreamBuffer*);
	using FN_SEND_TO_CLIENT = void(__stdcall*)(CMsgStreamBuffer*);

#pragma pack(push, 1)
	union
	{
		char storage[28];

		struct
		{
			uint32_t m_offset;
			uint32_t m_length;
			//legacy or disabled by 0x00EECD50? also can be massive msg gather related
			BOOL m_used;
			SMsgStreamBufferNode* m_pNodeFront;
			SMsgStreamBufferNode* m_pNodeCurrent;
			uint16_t m_id;
		};
	};
#pragma pack(pop)

	static FN_CONSTRUCTOR s_fnConstructor;
	static FN_DESTRUCTOR s_fnDestructor;
	static FN_READ_BYTES s_fnReadBytes;
	static FN_WRITE_BYTES s_fnWriteBytes;
	static FN_SEND_TO_SERVER s_fnSendToServer;
	static FN_SEND_TO_CLIENT s_fnSendToClient;

public:
	CMsgStreamBuffer(uint16_t id);
	virtual ~CMsgStreamBuffer();

	uint32_t GetOffset() const;
	uint32_t GetLength() const;
	BOOL GetIsUsed() const;
	uint32_t GetRemain() const;
	uint32_t GetID() const;
	SMsgStreamBufferNode* GetFrontNode() const;
	SMsgStreamBufferNode* GetCurrentNode() const;
	uint32_t GetNodeCount() const;
	void SetMsgID(uint16_t id);
	DWORD Read(uintptr_t dest, uint32_t count);
	uintptr_t Write(uintptr_t src, uint32_t count);
	void Seek(uint32_t offset);
	void Skip(uint32_t count);

	//Those are actually members of net engine prolly since none of those two are
	//thiscall.
	uintptr_t SendToServer();
	void SendToClient();

	template<typename T>
	T Read()
	{
		static_assert(std::is_fundamental<T>::value, "this function cannot read non-fundamental types");

		T value;
		Read((uintptr_t)&value, sizeof(T));
		return value;
	}

	template<typename T>
	CMsgStreamBuffer& operator >> (T& value)
	{
		Read(value);
		return *this;
	}

	template<typename T>
	uintptr_t Write(const T& value)
	{

		//???
		//ill disable check for now but u see may go wrong
		static_assert(std::is_fundamental<T>::value, "this function cannot write non-fundamental types");
		return Write((uintptr_t)&value, sizeof(T));
	}

	template<typename T>
	CMsgStreamBuffer& operator << (const T& value)
	{
		Write(value);
		return *this;
	}

	std::string ReadStringA();
	void WriteStringA(const std::string& str);

	std::wstring ReadStringW();
	void WriteStringW(const std::wstring& str);
}; //sizeof = 28

#endif