#ifndef Q_PLAYER_SPAWN_DATA
#define Q_PLAYER_SPAWN_DATA
#include "../../stdafx.h"
#include "../../GameStuff/CICPlayer/CICPlayer.h"
#include "../../Network/MsgStreamBuffer.h"

class CharacterSpawn
{
public:
	static void Initialize();
	void OnSpawn(CICPlayer* player);
	void OnUpdate(CMsgStreamBuffer* packet);
	void OnRefresh(CICPlayer* player);
private:

};
extern CharacterSpawn* g_CharacterSpawn;
#endif