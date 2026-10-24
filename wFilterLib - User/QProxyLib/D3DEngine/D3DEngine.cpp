#include "D3DEngine.h"
#include "../GameMain/GameMain.h"
#include "GUIs/IconWindow.h"
#include "GameInputHooks.h"

using namespace OSHGui;
using namespace OSHGui::Drawing;

IconWindow* g_IconWindow;

void D3DEngine::OnReset(ClientRect rect)
{
	auto &app = Application::Instance();
	app.DisplaySizeChanged(SizeF(rect.X, rect.Y));
}

D3DEngine::D3DEngine()
{

	while (*(DWORD*)(Q_LPDIRECT3DDEVICE9_PTR) == NULL)
		Sleep(1000);
	auto ptr = new Direct3D9Renderer(g_D3DMisc->GetDevice());
	auto renderer = std::unique_ptr<Direct3D9Renderer>(ptr);
	Application::Initialize(std::move(renderer));
	auto &app = Application::Instance();
	auto font = FontManager::LoadFont("Tahoma", 9, false);
	app.SetDefaultFont(font);
	app.SetCursorEnabled(false);
	g_IconWindow = new IconWindow();
	g_IconWindow->SetName("littleicons");

	g_IconWindow->Show(std::shared_ptr<Form>(g_IconWindow));

	app.Enable();
	GameInputHooks* InputHooks = new GameInputHooks();
}