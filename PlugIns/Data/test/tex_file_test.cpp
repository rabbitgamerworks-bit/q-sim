/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2013-07-31 Tobias Peters <tobias.peters@kreativeffekt.at>

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

#include <fstream>

#include <OgreDataStream.h>

#include "data/QSimTexFile.h"

#define BOOST_TEST_MODULE QSimTexFile
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( header_size )
{
    BOOST_CHECK_EQUAL( 0x18, sizeof( QSim::TexFile::BitData     ) );
    BOOST_CHECK_EQUAL( 0x10, sizeof( QSim::TexFile::ImageData   ) );
    BOOST_CHECK_EQUAL( 0x14, sizeof( QSim::TexFile::PaletteData ) );
    BOOST_CHECK_EQUAL( 0x10, sizeof( QSim::TexFile::RGBAData    ) );
    BOOST_CHECK_EQUAL( 0x58, sizeof( QSim::TexFile::PixelFormat ) );
    BOOST_CHECK_EQUAL( 0xEC, sizeof( QSim::TexFile::Header      ) );

    QSim::TexFile::Header header;
    BOOST_CHECK_EQUAL( sizeof( QSim::TexFile::Header ), sizeof( header ) );
}

BOOST_AUTO_TEST_CASE( bit_data_offset )
{
    BOOST_CHECK_EQUAL( 0x00, offsetof( QSim::TexFile::BitData, color_min ) );
    BOOST_CHECK_EQUAL( 0x04, offsetof( QSim::TexFile::BitData, color_max ) );
    BOOST_CHECK_EQUAL( 0x08, offsetof( QSim::TexFile::BitData, alpha_min ) );
    BOOST_CHECK_EQUAL( 0x0C, offsetof( QSim::TexFile::BitData, alpha_max ) );
    BOOST_CHECK_EQUAL( 0x10, offsetof( QSim::TexFile::BitData, pixel_min ) );
    BOOST_CHECK_EQUAL( 0x14, offsetof( QSim::TexFile::BitData, pixel_max ) );
}

BOOST_AUTO_TEST_CASE( palette_data_offset )
{
    BOOST_CHECK_EQUAL( 0x00, offsetof( QSim::TexFile::PaletteData, flag        ) );
    BOOST_CHECK_EQUAL( 0x04, offsetof( QSim::TexFile::PaletteData, index_bits  ) );
    BOOST_CHECK_EQUAL( 0x08, offsetof( QSim::TexFile::PaletteData, index_8bit  ) );
    BOOST_CHECK_EQUAL( 0x0C, offsetof( QSim::TexFile::PaletteData, total_color_count ) );
    BOOST_CHECK_EQUAL( 0x10, offsetof( QSim::TexFile::PaletteData, colors_per_palette ) );
}

BOOST_AUTO_TEST_CASE( image_data_offset )
{
    BOOST_CHECK_EQUAL( 0x0, offsetof( QSim::TexFile::ImageData, bit_depth  ) );
    BOOST_CHECK_EQUAL( 0x4, offsetof( QSim::TexFile::ImageData, width  ) );
    BOOST_CHECK_EQUAL( 0x8, offsetof( QSim::TexFile::ImageData, height ) );
    BOOST_CHECK_EQUAL( 0xC, offsetof( QSim::TexFile::ImageData, pitch  ) );
}

BOOST_AUTO_TEST_CASE( rgba_data_offset )
{
    BOOST_CHECK_EQUAL( 0x0, offsetof( QSim::TexFile::RGBAData, red   ) );
    BOOST_CHECK_EQUAL( 0x4, offsetof( QSim::TexFile::RGBAData, green ) );
    BOOST_CHECK_EQUAL( 0x8, offsetof( QSim::TexFile::RGBAData, blue  ) );
    BOOST_CHECK_EQUAL( 0xC, offsetof( QSim::TexFile::RGBAData, alpha ) );
}

BOOST_AUTO_TEST_CASE( pixel_format_offset )
{
    BOOST_CHECK_EQUAL( 0x00, offsetof( QSim::TexFile::PixelFormat, bits_per_pixel   ) );
    BOOST_CHECK_EQUAL( 0x04, offsetof( QSim::TexFile::PixelFormat, bytes_per_pixel  ) );
    BOOST_CHECK_EQUAL( 0x08, offsetof( QSim::TexFile::PixelFormat, bit_count        ) );
    BOOST_CHECK_EQUAL( 0x18, offsetof( QSim::TexFile::PixelFormat, bit_mask         ) );
    BOOST_CHECK_EQUAL( 0x28, offsetof( QSim::TexFile::PixelFormat, bit_shift        ) );
    BOOST_CHECK_EQUAL( 0x38, offsetof( QSim::TexFile::PixelFormat, bit_count_unused ) );
    BOOST_CHECK_EQUAL( 0x48, offsetof( QSim::TexFile::PixelFormat, shades           ) );
}

BOOST_AUTO_TEST_CASE( header_offset )
{
    BOOST_CHECK_EQUAL( 0x00, offsetof( QSim::TexFile::Header, version              ) );
    BOOST_CHECK_EQUAL( 0x08, offsetof( QSim::TexFile::Header, color_key_flag       ) );
    BOOST_CHECK_EQUAL( 0x14, offsetof( QSim::TexFile::Header, bit_data             ) );
    BOOST_CHECK_EQUAL( 0x30, offsetof( QSim::TexFile::Header, palette_count        ) );
    BOOST_CHECK_EQUAL( 0x34, offsetof( QSim::TexFile::Header, palette_total_color_count  ) );
    BOOST_CHECK_EQUAL( 0x38, offsetof( QSim::TexFile::Header, image_data           ) );
    BOOST_CHECK_EQUAL( 0x4C, offsetof( QSim::TexFile::Header, palette_data         ) );
    BOOST_CHECK_EQUAL( 0x64, offsetof( QSim::TexFile::Header, pixel_format         ) );
    BOOST_CHECK_EQUAL( 0xBC, offsetof( QSim::TexFile::Header, color_key_array_flag ) );
    BOOST_CHECK_EQUAL( 0xC4, offsetof( QSim::TexFile::Header, reference_alpha      ) );
    BOOST_CHECK_EQUAL( 0xCC, offsetof( QSim::TexFile::Header, unknown_0xCC         ) );
}

BOOST_AUTO_TEST_CASE( color_offset )
{
    BOOST_CHECK_EQUAL( 0x0, offsetof( QSim::TexFile::Color, all        ) );
    BOOST_CHECK_EQUAL( 0x0, offsetof( QSim::TexFile::Color, comp       ) );
    BOOST_CHECK_EQUAL( 0x3, offsetof( QSim::TexFile::Color, comp.alpha ) );
    BOOST_CHECK_EQUAL( 0x2, offsetof( QSim::TexFile::Color, comp.red   ) );
    BOOST_CHECK_EQUAL( 0x1, offsetof( QSim::TexFile::Color, comp.green ) );
    BOOST_CHECK_EQUAL( 0x0, offsetof( QSim::TexFile::Color, comp.blue  ) );
}

BOOST_AUTO_TEST_CASE( read_file )
{
    const char* file_name( "../../../../output/data_orig/menu/menu_gm/barre.tex" );
    std::ifstream *ifs(  OGRE_NEW_T( std::ifstream, Ogre::MEMCATEGORY_GENERAL )( file_name, std::ifstream::binary ) );
    BOOST_REQUIRE( ifs->is_open() );
    Ogre::FileStreamDataStream *stream( OGRE_NEW Ogre::FileStreamDataStream( ifs ) );
    Ogre::DataStreamPtr input( stream );

    BOOST_REQUIRE( input->isReadable() );

    QSim::TexFile tex;
    tex.read( input );

    BOOST_CHECK_EQUAL( 0x80, tex.m_header.image_data.width );
    BOOST_CHECK_EQUAL( 0x80, tex.m_header.image_data.height );
    BOOST_CHECK_EQUAL(    8, tex.m_header.image_data.bit_depth );

    BOOST_CHECK_EQUAL(     1, tex.m_header.palette_count );
    BOOST_CHECK_EQUAL(     1, tex.m_header.palette_data.flag );
    BOOST_CHECK_EQUAL( 0x100, tex.m_header.palette_data.total_color_count );
    BOOST_CHECK_EQUAL( 0x80 * 0x80, tex.m_image_data.size() );

    for( size_t i(0); i < 39; ++i )
    {
        BOOST_TEST_MESSAGE( "checking color i: " << i );
        BOOST_CHECK_EQUAL( 0xFFFFFFFF, tex.m_image_data[i].all );
    }
    BOOST_CHECK_EQUAL( 0xFFF6FFF6, tex.m_image_data[39].all );
    BOOST_CHECK_EQUAL( 0xF6, tex.m_image_data[39].comp.red );
    BOOST_CHECK_EQUAL( 0xFF, tex.m_image_data[39].comp.green );
    BOOST_CHECK_EQUAL( 0xF6, tex.m_image_data[39].comp.blue );
    BOOST_CHECK_EQUAL( 0xFF, tex.m_image_data[39].comp.alpha );

    BOOST_CHECK_EQUAL( 0x7B, tex.m_image_data[40].comp.red );
    BOOST_CHECK_EQUAL( 0xA4, tex.m_image_data[40].comp.green );
    BOOST_CHECK_EQUAL( 0xA4, tex.m_image_data[40].comp.blue );
    BOOST_CHECK_EQUAL( 0xFF, tex.m_image_data[40].comp.alpha );


	Ogre::MemoryDataStreamPtr pixel_data( tex.getPixelData() );
    BOOST_CHECK_EQUAL( tex.m_image_data.size() * 4, pixel_data->size() );

	Ogre::SharedPtr<Ogre::ImageCodec::ImageData> img_data( tex.getImageData() );
    BOOST_CHECK_EQUAL( img_data->width , tex.m_header.image_data.width );
    BOOST_CHECK_EQUAL( img_data->height, tex.m_header.image_data.height );
    BOOST_CHECK_EQUAL( Ogre::PF_A8R8G8B8, img_data->format );
    BOOST_CHECK_EQUAL( 1, img_data->depth );
    BOOST_CHECK_EQUAL( 0, img_data->flags );
    BOOST_CHECK_EQUAL( 0, img_data->num_mipmaps );
    BOOST_CHECK_EQUAL( pixel_data->size(), img_data->size );
}
