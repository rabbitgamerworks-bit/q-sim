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
#include "common/QSimManualRenderable.h"

#include <OgreTechnique.h>

namespace QSim
{
    //--------------------------------------------------------------------------
    void
    ManualRenderable::renderWithCamera( Ogre::SceneManager* scene_manager
                                      , Ogre::RenderOperation& op
                                      , const Ogre::MaterialPtr& material
                                      , const Ogre::Matrix4& world )
    {
        render( scene_manager, op, material, world, false );
    }

    //--------------------------------------------------------------------------
    void
    ManualRenderable::renderInClipSpace( Ogre::SceneManager* scene_manager
                                       , Ogre::RenderOperation& op
                                       , const Ogre::MaterialPtr& material
                                       , const Ogre::Matrix4& world )
    {
        render( scene_manager, op, material, world, true );
    }

    //--------------------------------------------------------------------------
    void
    ManualRenderable::render( Ogre::SceneManager* scene_manager
                            , Ogre::RenderOperation& op
                            , const Ogre::MaterialPtr& material
                            , const Ogre::Matrix4& world
                            , bool identity_view_projection )
    {
        if( !material )
        {
            return;
        }

        ManualRenderable renderable;
        renderable.m_operation = &op;
        renderable.m_material = material;
        renderable.m_world = world;
        renderable.setUseIdentityView( identity_view_projection );
        renderable.setUseIdentityProjection( identity_view_projection );

        // getBestTechnique honours the active material scheme, which lets the
        // RTSS hand out the technique carrying the generated shaders.
        material->load();
        Ogre::Technique* technique( material->getBestTechnique( 0, &renderable ) );
        if( technique == nullptr )
        {
            return;
        }

        for( Ogre::Pass* pass : technique->getPasses() )
        {
            scene_manager->_injectRenderWithPass( pass, &renderable, false );
        }
    }

    //--------------------------------------------------------------------------
    const Ogre::LightList&
    ManualRenderable::getLights() const
    {
        static const Ogre::LightList no_lights;
        return no_lights;
    }

    //--------------------------------------------------------------------------
}
