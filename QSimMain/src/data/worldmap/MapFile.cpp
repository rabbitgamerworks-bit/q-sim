#include "data/worldmap/MapFile.h"
#include "data/worldmap/MapFileSerializer.h"

BEGIN_QSIM

/*static*/ const String WorldMapFile::RESOURCE_TYPE( "QSimWorldMap7File" );

WorldMapFile::~WorldMapFile()
{

}

void WorldMapFile::loadImpl()
{
    MapFileSerializer serializer;
    Ogre::DataStreamPtr stream( openResource() );
    serializer.importMapFile( stream, *this );
}

void WorldMapFile::unloadImpl()
{

}

END_QSIM
