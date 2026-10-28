#include "data/worldmap/TxzFile.h"
#include "data/worldmap/TxzFileSerializer.h"

BEGIN_QSIM

/*static*/ const String TxzFile::RESOURCE_TYPE( "QSimWorldMapTxzFile" );

TxzFile::~TxzFile()
{

}

void TxzFile::loadImpl()
{
    TxzFileSerializer serializer;
    Ogre::DataStreamPtr stream( openResource() );
    serializer.import( stream, *this );
}

void TxzFile::unloadImpl()
{

}

END_QSIM
