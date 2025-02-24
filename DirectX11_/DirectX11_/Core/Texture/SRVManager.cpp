#include "framework.h"
#include "SRVManager.h"

SRVManager* SRVManager::_instance = nullptr;

SRVManager::SRVManager()
{
}

SRVManager::~SRVManager()
{
    _srvTable.clear();
}

shared_ptr<SRV> SRVManager::AddSRV(wstring path)
{
    if(_srvTable.count(path) != 0)
        return _srvTable[path];

    shared_ptr<SRV> srv = make_shared<SRV>(path);
    _srvTable[path] = srv;

    return _srvTable[path];
}
