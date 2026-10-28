#ifndef _MAP_FILE_MANAGER_H_
#define _MAP_FILE_MANAGER_H_

#include <OgreResourceManager.h>
#include "common/TypeDefine.h"
#include "QSimPrerequisites.h"

BEGIN_QSIM

class WorldMapFile;

class _QSimExport MapFileManager
        : public Ogre::ResourceManager,
          public Ogre::Singleton<MapFileManager>
{
public:
    MapFileManager();
    virtual ~MapFileManager();

    static MapFileManager& getSingleton();
    static MapFileManager* getSingletonPtr();

private:
    virtual Ogre::Resource* createImpl(
            const Ogre::String &name,
            Ogre::ResourceHandle handle,
            const Ogre::String &group,
            bool isManual,
            Ogre::ManualResourceLoader *loader,
            const Ogre::NameValuePairList *createParams ) override final;
};

END_QSIM

#endif // _MAP_FILE_MANAGER_H_
