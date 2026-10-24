#ifndef Q_PROXY_RESOURCE_MANAGER_H
#define Q_PROXY_RESOURCE_MANAGER_H
#include "../stdafx.h"
#include "../Helpers/CStringHelper.h"
class ResourceManager
{
public:
	void Initialize();
	void* LoadTextureFromPk2(const n_string &path);
private:

};
#endif