/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2013-08-24 Tobias Peters <tobias.peters@kreativeffekt.at>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#include <boost/test/unit_test.hpp>

#include <Ogre.h>

#include "data/QSimFLevelFileSerializer.h"

#include "data/QSimBackgroundFileManager.h"
#include "data/QSimCameraMatrixFileManager.h"
#include "data/QSimHRCFileManager.h"
#include "data/QSimPaletteFileManager.h"
#include "data/QSimLZSFLevelFileManager.h"
#include "data/FF7ModelListFileManager.h"
#include "map/QSimBackground2DFileManager.h"
#include "map/QSimWalkmeshFileManager.h"

using namespace Ogre;

BOOST_AUTO_TEST_CASE( read_file )
{
    class TestFile : public QSim::FLevelFile
    {
    public:
        TestFile() : QSim::FLevelFile( NULL, "reference.flevel", 0, "General" ) {}
    };

    class TestTexture : public Texture
    {
    public:
        TestTexture( ResourceManager* creator, const String& name, ResourceHandle handle,
                  const String& group, bool isManual = false, ManualResourceLoader* loader = 0 )
            : Texture( creator, name, handle, group, isManual, loader )
        {}

    protected:
        virtual void loadImpl() {}
        virtual void unloadImpl() {}
        virtual void createInternalResourcesImpl(){}
        virtual void freeInternalResourcesImpl(){}
    };

    class TestTextureManager : public TextureManager
    {
    public:
        virtual PixelFormat getNativeFormat( TextureType ttype, PixelFormat format, int usage )
        {
            return format;
        }
        virtual bool    isHardwareFilteringSupported( TextureType ttype, PixelFormat format, int usage, bool preciseFormatOnly=false )
        {
            return false;
        }

    protected:
        virtual Resource* createImpl( const String &name
          , ResourceHandle handle, const String &group, bool isManual
          , ManualResourceLoader *loader
          , const NameValuePairList *createParams )
        {
            return new TestTexture( this, name, handle, group, isManual, loader );
        }
    };


    LogManager                          logMgr;
    Root                                root("","");
    ResourceGroupManager               &rgm( ResourceGroupManager::getSingleton() );
    TestTextureManager                  tmgr;
    QSim::CameraMatrixFileManager     cmgr;
    QSim::WalkmeshFileManager         wmgr;
    QSim::PaletteFileManager          pmgr;
    QSim::BackgroundFileManager       bmgr;
    QSim::Background2DFileManager     b2mgr;
    QSim::FF7::ModelListFileManager   mmgr;
    QSim::HRCFileManager              hmgr;
    QSim::LZSFLevelFileManager        fmgr;
    logMgr.createLog( "Default Log", true, true, true );

    rgm.addResourceLocation( "misc", "FileSystem" );
    rgm.initialiseAllResourceGroups();

    TestFile        file;
    DataStreamPtr   stream( rgm.openResource( file.getName(), file.getGroup() ) );
    BOOST_REQUIRE( stream->isReadable() );

    QSim::FLevelFileSerializer    ser;
    ser.importFLevelFile( stream, &file );
    BOOST_CHECK_EQUAL( 757890, stream->tell() );

    QSim::BackgroundFilePtr       background   ( file.getBackground() );
    QSim::CameraMatrixFilePtr     camera_matrix( file.getCameraMatrix() );
    QSim::FF7::ModelListFilePtr   model_list   ( file.getModelList() );
    QSim::PaletteFilePtr          palette      ( file.getPalette() );
    QSim::WalkmeshFilePtr         walkmesh     ( file.getWalkmesh() );

    BOOST_REQUIRE( background );
    BOOST_REQUIRE( camera_matrix );
    BOOST_REQUIRE( model_list );
    BOOST_REQUIRE( palette );
    BOOST_REQUIRE( walkmesh );
    BOOST_CHECK_EQUAL( "reference.background", background->getName() );
    BOOST_CHECK_EQUAL( "reference.cam_matrix", camera_matrix->getName() );
    BOOST_CHECK_EQUAL( "reference.model_list", model_list->getName() );
    BOOST_CHECK_EQUAL( "reference.palette"   , palette->getName() );
    BOOST_CHECK_EQUAL( "reference.walkmesh"  , walkmesh->getName() );
    Matrix3 m3_expected(
        1, -0, -0
       ,0, -1, -0
       ,0, -0, -1
    );
    BOOST_CHECK_EQUAL( m3_expected, camera_matrix->getMatrix() );
    BOOST_CHECK_EQUAL( Vector3( -1, 2, -3 ), camera_matrix->getPosition() );
    BOOST_CHECK_EQUAL( 2, camera_matrix->getCount() );
    BOOST_CHECK_EQUAL( 12345, camera_matrix->getFocalLength() );


    Ogre::Image *image( background->createImage( palette ) );
    // TODO: FIX ME ON OSX
    //image->save( file.getName() + ".png" );
    delete image;

    QSim::FLevelFilePtr lzs_file = Ogre::static_pointer_cast<QSim::FLevelFile>(fmgr.load( "reference_compressed.flevel", "General" ));
    BOOST_CHECK( lzs_file->getPalette() );
    BOOST_CHECK( lzs_file->getBackground() );

    image = lzs_file->getBackground()->createImage( lzs_file->getPalette() );
    // TODO: FIX ME ON OSX
    //image->save( lzs_file->getName() + ".png" );
    delete image;

    lzs_file.reset();
    logMgr.destroyLog( "Default Log" );
    stream->close();
}
