/*
-----------------------------------------------------------------------------
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
#ifndef __QSimLegacyScripts_H__
#define __QSimLegacyScripts_H__

#include <OgreScriptCompiler.h>

namespace QSim
{
    /**
     * Accepts the Ogre 1.9 style font definitions found in the game data.
     *
     * Ogre 1.9 allowed "MyFont { ... }" in .fontdef files, newer Ogre versions
     * require the object type: "font MyFont { ... }". This listener adds the
     * missing type before the script gets translated.
     */
    class LegacyScriptListener : public Ogre::ScriptCompilerListener
    {
    public:
        void preConversion( Ogre::ScriptCompiler* compiler, Ogre::ConcreteNodeListPtr nodes ) override;

        /// Registers the listener with the ScriptCompilerManager (once).
        static void install();
    };
}

#endif // __QSimLegacyScripts_H__
