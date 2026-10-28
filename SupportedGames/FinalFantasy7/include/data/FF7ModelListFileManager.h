/*
-----------------------------------------------------------------------------
Copyright (c) 07.10.2013 Tobias Peters <tobias.peters@kreativeffekt.at>

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
#ifndef __FF7ModelListFileManager_H__
#define __FF7ModelListFileManager_H__

#include <OgreResourceManager.h>

#include "QSimPrerequisites.h"

#include "FF7ModelListFile.h"

namespace QSim
{
    namespace FF7
    {
        class _QSimExport ModelListFileManager : public Ogre::ResourceManager, public Ogre::Singleton<ModelListFileManager>
        {
        public:
            ModelListFileManager();
            virtual ~ModelListFileManager();

            static ModelListFileManager &getSingleton();
            static ModelListFileManager *getSingletonPtr();

        protected:
            Ogre::Resource *createImpl( const Ogre::String &name, Ogre::ResourceHandle handle
                                        , const Ogre::String &group, bool isManual, Ogre::ManualResourceLoader *loader
                                        , const Ogre::NameValuePairList *createParams );

        private:
        };
    }
}
#endif // __FF7ModelListFileManager_H__
