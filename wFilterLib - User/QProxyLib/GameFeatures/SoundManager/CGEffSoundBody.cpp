#include "CGEffSoundBody.h"

CGEffSoundBody* CGEffSoundBody::GetSoundBody()
{
	CGEffSoundBody* body = *reinterpret_cast<CGEffSoundBody**>(0x0110AAD8);
	return body;
}

void CGEffSoundBody::DoSound(const wchar_t* code)
{
	reinterpret_cast<void(__thiscall*)(CGEffSoundBody*, const wchar_t*)>(0x00A72D40)(this, code);
}