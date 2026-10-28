/*
-----------------------------------------------------------------------------
Copyright (c) 15.10.2013 Tobias Peters <tobias.peters@kreativeffekt.at>

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
#ifndef __QSimAFileManager_H__
#define __QSimAFileManager_H__

#include <OgreResourceManager.h>

#include "QSimPrerequisites.h"

#include "QSimAFile.h"

namespace QSim
{
    class _QSimExport AFileManager : public Ogre::ResourceManager, public Ogre::Singleton<AFileManager>
    {
    public:
        AFileManager();
        virtual ~AFileManager();

        static AFileManager& getSingleton();
        static AFileManager* getSingletonPtr();

    protected:
        virtual Ogre::Resource *createImpl( const Ogre::String &name, Ogre::ResourceHandle handle
          , const Ogre::String &group, bool isManual, Ogre::ManualResourceLoader *loader
          , const Ogre::NameValuePairList *createParams ) override final;

    private:
    };
}

#endif // __QSimAFileManager_H__
