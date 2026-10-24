#include "../stdafx.h"
#include "MsgStreamBuffer.h"
#include <cassert>
#include "NetCustoms.h"

CMsgStreamBuffer::FN_CONSTRUCTOR CMsgStreamBuffer::s_fnConstructor = reinterpret_cast<CMsgStreamBuffer::FN_CONSTRUCTOR>(0x0053CEA0);
CMsgStreamBuffer::FN_DESTRUCTOR CMsgStreamBuffer::s_fnDestructor = reinterpret_cast<CMsgStreamBuffer::FN_DESTRUCTOR>(0x005097A0);
CMsgStreamBuffer::FN_READ_BYTES CMsgStreamBuffer::s_fnReadBytes = reinterpret_cast<CMsgStreamBuffer::FN_READ_BYTES>(0x004F7220);
CMsgStreamBuffer::FN_WRITE_BYTES CMsgStreamBuffer::s_fnWriteBytes = reinterpret_cast<CMsgStreamBuffer::FN_WRITE_BYTES>(0x00508FE0);
CMsgStreamBuffer::FN_SEND_TO_SERVER CMsgStreamBuffer::s_fnSendToServer = reinterpret_cast<CMsgStreamBuffer::FN_SEND_TO_SERVER>(0x008418D0);
CMsgStreamBuffer::FN_SEND_TO_CLIENT CMsgStreamBuffer::s_fnSendToClient = reinterpret_cast<CMsgStreamBuffer::FN_SEND_TO_CLIENT>(0x008A7630);

CMsgStreamBuffer::CMsgStreamBuffer(uint16_t id)
{
	s_fnConstructor(this, id);
	return;

	m_id = id;
	m_offset = 0;
	m_length = 0;
	m_used = TRUE;
	m_pNodeFront = new SMsgStreamBufferNode();
	m_pNodeCurrent = m_pNodeFront;
}

CMsgStreamBuffer::~CMsgStreamBuffer()
{
	s_fnDestructor(this);
}

uint32_t CMsgStreamBuffer::GetOffset() const { return m_offset; }
uint32_t CMsgStreamBuffer::GetLength() const { return m_length; }
BOOL CMsgStreamBuffer::GetIsUsed() const { return m_used; }
uint32_t CMsgStreamBuffer::GetRemain() const { return (m_length - m_offset); }
uint32_t CMsgStreamBuffer::GetID() const { return m_id; }
SMsgStreamBufferNode* CMsgStreamBuffer::GetFrontNode() const { return m_pNodeFront; }
SMsgStreamBufferNode* CMsgStreamBuffer::GetCurrentNode() const { return m_pNodeCurrent; }

uint32_t CMsgStreamBuffer::GetNodeCount() const
{
	int count = (GetLength() / MSG_NODE_BUFFER_SIZE);
	int tail = (GetLength() % MSG_NODE_BUFFER_SIZE);
	if (tail > 0)
		++count;
	return count;
}

void CMsgStreamBuffer::SetMsgID(uint16_t id) { m_id = id; }

DWORD CMsgStreamBuffer::Read(uintptr_t dest, uint32_t count)
{
	assert((count <= GetRemain()) && "cannot read beyound msg data bounds");
	return s_fnReadBytes(this, dest, count);
}

std::string CMsgStreamBuffer::ReadStringA()
{
	auto len = Read<uint16_t>();
	auto bufLen = len + 1;
	char* buffer = new char[bufLen]();

	Read((uintptr_t)(buffer), len);

	std::string result(buffer);

	delete[] buffer;

	return result;
}

void CMsgStreamBuffer::WriteStringA(const std::string& str)
{
	Write<uint16_t>(str.length());
	Write((uintptr_t)str.c_str(), str.length());
}

std::wstring CMsgStreamBuffer::ReadStringW()
{
	auto len = Read<uint16_t>();
	auto bufLen = len + 1;
	wchar_t* buffer = new wchar_t[bufLen]();

	Read((uintptr_t)(buffer), len * 2);
	std::wstring result(buffer);
	delete[] buffer;
	return result;
}

void CMsgStreamBuffer::WriteStringW(const std::wstring& str)
{
	Write<uint16_t>(str.length());
	Write((uintptr_t)str.c_str(), str.length() * 2);
}

uintptr_t CMsgStreamBuffer::Write(uintptr_t src, uint32_t count)
{
	return s_fnWriteBytes(this, src, count);
}

void CMsgStreamBuffer::Seek(uint32_t offset)
{
	assert((offset <= GetLength()) && "cannot seek beyound msg data bounds");
	m_offset = offset;
}

void CMsgStreamBuffer::Skip(uint32_t count)
{
	assert((m_offset + count) <= GetLength() && "cannot skip beyound msg data bounds");
	m_offset += count;
}

uintptr_t CMsgStreamBuffer::SendToServer() { return s_fnSendToServer(this); };

void CMsgStreamBuffer::SendToClient()
{
	class CDummyScene;
	#define g_CurrentScene (*((CDummyScene**)0x00EECEA4))
	CNetCustoms::s_fnRecvMsg(g_CurrentScene, this);
}