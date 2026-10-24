#ifndef Q_D3D_MISC_H
#define Q_D3D_MISC_H
#define Q_LPDIRECT3DDEVICE9_PTR 0x00110F7CC
#include "../stdafx.h"
#include "../Includes/includes.h"

struct ClientRect
{
	int X;
	int Y;
};

class D3DMisc
{
public:
	void SetDevice(LPDIRECT3DDEVICE9 device);
	void SetClientRect(ClientRect rect)
	{
		this->m_ClientRect.X = rect.X;
		this->m_ClientRect.Y = rect.Y;
	}

	LPDIRECT3DDEVICE9 GetDevice();
	ClientRect GetClientRect()
	{
		return this->m_ClientRect;
	}

	OSHGui::Misc::RawDataContainer GetResource(const int ResID);

private:
	LPDIRECT3DDEVICE9 m_Direct3DDevice9;
	ClientRect m_ClientRect;
};
#endif