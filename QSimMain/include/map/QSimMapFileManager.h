/*
-----------------------------------------------------------------------------
Copyright (c) 27.10.2013 Tobias Peters <tobias.peters@kreativeffekt.at>

This file is part of Q-Sim

Q-Sim is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 2.0 (GPLv2) of the License.

Q-Sim is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
-----------------------------------------------------------------------------
*/
#ifndef __QSimMapFileManager_H__
#define __QSimMapFileManager_H__

#include <OgreResourceManager.h>

#include "QSimPrerequisites.h"

#include "QSimMapFile.h"

namespace QSim
{
    class _QSimExport MapFileManager : public Ogre::ResourceManager, public Ogre::Singleton<MapFileManager>
    {
    public:
        MapFileManager();
        virtual ~MapFileManager();
        
        static MapFileManager &getSingleton();
        static MapFileManager *getSingletonPtr();
        
    protected:
        Ogre::Resource *createImpl( const Ogre::String &name, Ogre::ResourceHandle handle
                                    , const Ogre::String &group, bool isManual, Ogre::ManualResourceLoader *loader
                                    , const Ogre::NameValuePairList *createParams );
        
    private:
    };
}

#endif // __QSimMapFileManager_H__

