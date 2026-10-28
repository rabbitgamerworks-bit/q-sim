/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2013-07-30 Tobias Peters <tobias.peters@kreativeffekt.at>

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
#ifndef __QSimTexCodec_H__
#define __QSimTexCodec_H__

#include <OgreImageCodec.h>
#include <OgreCodec.h>

#include "QSimPrerequisites.h"

namespace QSim
{
    class _QSimExport TexCodec : public Ogre::ImageCodec
    {
    public:
        TexCodec();
        virtual ~TexCodec();

        /// @copydoc Ogre::ImageCodec::getType
        Ogre::String getType() const override;

        /// @copydoc Ogre::Codec::decode
        void decode( const Ogre::DataStreamPtr& input, const Ogre::Any& output ) const override;

        /// @copydoc Ogre::Codec::magicNumberToFileExt
        Ogre::String magicNumberToFileExt(const char *magicNumberPtr, size_t maxbytes) const override;

        static Ogre::String ms_type_name;

        /// @copydoc Ogre::Plugin::install
        static void install();

        /// @copydoc Ogre::Plugin::initialise
        static void initialise();

        /// @copydoc Ogre::Plugin::shutdown
        static void shutdown();

        /// @copydoc Ogre::Plugin::uninstall
        static void uninstall();

      private:
        static TexCodec *ms_tex_codex;
    };
}

#endif // __QSimTexCodec_H__
