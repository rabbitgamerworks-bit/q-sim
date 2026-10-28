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
#include "common/QSimLegacyScripts.h"

#include <OgreStringConverter.h>
#include <OgreStringVector.h>

namespace QSim
{
    namespace
    {
        const Ogre::String FONT_TYPE( "font" );

        bool isFontDefinition( const Ogre::String& file )
        {
            return Ogre::StringUtil::endsWith( file, ".fontdef" );
        }
    }

    //--------------------------------------------------------------------------
    void
    LegacyScriptListener::preConversion( Ogre::ScriptCompiler*, Ogre::ConcreteNodeListPtr nodes )
    {
        if( !nodes )
        {
            return;
        }

        for( Ogre::ConcreteNodePtr& node : *nodes )
        {
            // legacy layout: <name> { ... }
            if( !isFontDefinition( node->file )
                || node->type != Ogre::CNT_WORD
                || node->token == FONT_TYPE
                || node->children.empty()
                || node->children.front()->type != Ogre::CNT_LBRACE )
            {
                continue;
            }

            // new layout: font <name> { ... }
            Ogre::ConcreteNodePtr font_node( std::make_shared<Ogre::ConcreteNode>() );
            font_node->token = FONT_TYPE;
            font_node->file = node->file;
            font_node->line = node->line;
            font_node->type = Ogre::CNT_WORD;
            font_node->parent = node->parent;

            Ogre::ConcreteNodePtr name_node( std::make_shared<Ogre::ConcreteNode>() );
            name_node->token = node->token;
            name_node->file = node->file;
            name_node->line = node->line;
            name_node->type = Ogre::CNT_WORD;
            name_node->parent = font_node.get();

            font_node->children.push_back( name_node );
            for( Ogre::ConcreteNodePtr& child : node->children )
            {
                child->parent = font_node.get();
                font_node->children.push_back( child );
            }
            node = font_node;
        }
    }

    //--------------------------------------------------------------------------
    void
    LegacyScriptListener::install()
    {
        static LegacyScriptListener s_listener;
        Ogre::ScriptCompilerManager& manager( Ogre::ScriptCompilerManager::getSingleton() );
        if( manager.getListener() == nullptr )
        {
            manager.setListener( &s_listener );
        }
    }

    //--------------------------------------------------------------------------
}
