#include "D3DMisc.h"

extern HMODULE g_hModule;

LPDIRECT3DDEVICE9 D3DMisc::GetDevice()
{
	this->SetDevice(reinterpret_cast<LPDIRECT3DDEVICE9>(*(DWORD*)Q_LPDIRECT3DDEVICE9_PTR));
	return this->m_Direct3DDevice9;
}
void D3DMisc::SetDevice(LPDIRECT3DDEVICE9 device)
{
	if(!this->m_Direct3DDevice9)
		this->m_Direct3DDevice9 = device;
	
}

OSHGui::Misc::RawDataContainer D3DMisc::GetResource(const int ResID)
{
	HRESULT hr = S_OK;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void* pImageFile = NULL;
	DWORD imageFileSize = 0;

	imageResHandle = FindResourceW(g_hModule, MAKEINTRESOURCEW(ResID), L"PNG");
	if (imageResHandle == NULL) {
		// resource not found
		//printf("1 is nullptr\n");
	}

	imageResDataHandle = LoadResource(g_hModule, imageResHandle);
	if (imageResDataHandle == NULL) {
		// could not load resource
		//printf("2 is nullptr\n");
	}

	pImageFile = LockResource(imageResDataHandle);
	if (pImageFile == NULL) {
		// could not lock resource
		//printf("3 is nullptr\n");

	}

	if (pImageFile)
	{
		imageFileSize = SizeofResource(g_hModule, imageResHandle);

		auto test = reinterpret_cast<uint8_t*>(pImageFile);
		std::vector<uint8_t> vec;
		for (size_t i = 0; i < imageFileSize; i++)
		{
			vec.push_back(test[i]);
		}

		auto _container = OSHGui::Misc::RawDataContainer(vec);
		return _container;
	}

	return NULL;
}