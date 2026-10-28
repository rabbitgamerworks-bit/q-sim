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
#ifndef __QSimManualRenderable_H__
#define __QSimManualRenderable_H__

#include <OgreMaterial.h>
#include <OgreMatrix4.h>
#include <OgreRenderable.h>
#include <OgreRenderOperation.h>
#include <OgreSceneManager.h>

namespace QSim
{
    /**
     * Draws a RenderOperation from inside a RenderQueueListener.
     *
     * Shader based render systems (Vulkan, GL3+) ignore the fixed function
     * matrices set through RenderSystem::_setWorldMatrix & co, so the
     * transforms have to reach the GPU programs through a Renderable and
     * SceneManager::_injectRenderWithPass.
     */
    class ManualRenderable : public Ogre::Renderable
    {
    public:
        /// Renders op with material using the current camera's view & projection.
        static void renderWithCamera( Ogre::SceneManager* scene_manager
                                    , Ogre::RenderOperation& op
                                    , const Ogre::MaterialPtr& material
                                    , const Ogre::Matrix4& world = Ogre::Matrix4::IDENTITY );

        /// Renders op with material where world transforms straight to clip space.
        static void renderInClipSpace( Ogre::SceneManager* scene_manager
                                     , Ogre::RenderOperation& op
                                     , const Ogre::MaterialPtr& material
                                     , const Ogre::Matrix4& world = Ogre::Matrix4::IDENTITY );

        const Ogre::MaterialPtr& getMaterial() const override { return m_material; }
        void getRenderOperation( Ogre::RenderOperation& op ) override { op = *m_operation; }
        void getWorldTransforms( Ogre::Matrix4* xform ) const override { *xform = m_world; }
        Ogre::Real getSquaredViewDepth( const Ogre::Camera* ) const override { return 0; }
        const Ogre::LightList& getLights() const override;

    private:
        static void render( Ogre::SceneManager* scene_manager
                          , Ogre::RenderOperation& op
                          , const Ogre::MaterialPtr& material
                          , const Ogre::Matrix4& world
                          , bool identity_view_projection );

        Ogre::RenderOperation*  m_operation = nullptr;
        Ogre::MaterialPtr       m_material;
        Ogre::Matrix4           m_world = Ogre::Matrix4::IDENTITY;
    };
}

#endif // __QSimManualRenderable_H__
