/*
-----------------------------------------------------------------------------
Copyright (c) 2013-09-05 Tobias Peters <tobias.peters@kreativeffekt.at>

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
#include "map/QSimWalkmeshFile.h"

#include <OgreLogManager.h>

#include "map/QSimWalkmeshFileXMLSerializer.h"

namespace QSim
{
    //---------------------------------------------------------------------
    const String    WalkmeshFile::RESOURCE_TYPE( "QSimWalkmeshFile" );

    //---------------------------------------------------------------------
    WalkmeshFile::WalkmeshFile( Ogre::ResourceManager *creator
                 ,const String &name, Ogre::ResourceHandle handle
                 ,const String &group, bool isManual
                 ,Ogre::ManualResourceLoader *loader ) :
        Resource( creator, name, handle, group, isManual, loader )
    {
    }

    //---------------------------------------------------------------------
    WalkmeshFile::~WalkmeshFile()
    {
        unload();
    }

    //---------------------------------------------------------------------
    void
    WalkmeshFile::loadImpl()
    {
        WalkmeshFileXMLSerializer serializer;
        Ogre::DataStreamPtr stream( openResource() );
        serializer.importWalkmeshFile( stream, this );
    }

    //---------------------------------------------------------------------
    void
    WalkmeshFile::unloadImpl()
    {
        m_triangles.clear();
    }

    //---------------------------------------------------------------------
    size_t
    WalkmeshFile::calculateSize() const
    {
        return sizeof(Triangle) * m_triangles.size();
    }

    //---------------------------------------------------------------------
    WalkmeshFile::TriangleList&
    WalkmeshFile::getTriangles()
    {
        return m_triangles;
    }

    //---------------------------------------------------------------------
}
