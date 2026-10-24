#ifndef Q_GLOBAL_GAME_MAIN_H
#define Q_GLOBAL_GAME_MAIN_H
#include "../Helpers/CStringHelper.h"
#include "../Helpers/MemoryHelper.h"
#include "../Network/NetCustoms.h"
#include "../Network/MsgHandler.h"
#include "../Character/Character.h"
#include "../D3DEngine/D3DEngine.h"
#include "../D3DEngine/D3DMisc.h"
#include "../D3DEngine/GameCommonHooks.h"
#include "../D3DEngine/ResourceManager.h"
#include "../GameFeatures/SoundManager/CGEffSoundBody.h"
#include "../GameStuff/GlobalDataManager/GlobalDataManager.h"
#include "../Discord/Discord.h"
#include "../GameFeatures/PHBotManager/PHBotManager.h"
#include "../GameFeatures/ChatManager/ChatManager.h"
#include "../GameFeatures/GlobalItemLinking/GlobalItemLinking.h"
#include "../GameFeatures/CharacterIcons/CharacterIcons.h"


extern MemoryHelper* g_MemoryHelper;
extern CStringHelper* g_StringHelper;
extern CNetCustoms* g_NetCustoms;
extern CMsgHandler* g_MsgHandler;
extern D3DEngine* g_D3DEngine;
extern D3DMisc* g_D3DMisc;
extern GameCommonHooks* g_GameCommonHooks;
extern ResourceManager* g_ResourceMgr;
extern CGEffSoundBody* g_CGEffSoundBody;
extern Discord* g_DiscordMgrAddon;
extern PHBotManager* g_PHBotMgr;
extern ChatManager* g_ChatManager;
extern CGlobalDataManager* g_GlobalDataMgr;
extern GlobalItemLinking* g_GlobalItemLinking;
extern CharacterIcons* g_CharacterIcons;

#endif