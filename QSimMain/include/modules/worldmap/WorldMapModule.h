#ifndef _WORLD_MAP_MODULE_H_
#define _WORLD_MAP_MODULE_H_

#include <OgreSingleton.h>
#include "common/TypeDefine.h"

BEGIN_QSIM

class WorldMapModule : public Ogre::Singleton< WorldMapModule >
{
public:
    void Init();
};

END_QSIM

#endif // _WORLD_MAP_MODULE_H_
