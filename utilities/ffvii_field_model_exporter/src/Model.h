#ifndef MODEL_H
#define MODEL_H

#include <Ogre.h>
#include "common/TypeDefine.h"


struct BonePosition
{
    float rotation_x;
    float rotation_y;
    float rotation_z;

    float translation_x;
    float translation_y;
    float translation_z;
};



struct Frame
{
    std::vector<BonePosition> bone;
};



struct Animation
{
    std::vector<Frame> frame;
};



struct Model
{
    Model(void);
    ~Model(void);
    void Update(const QSim::uint32 delta_time);
    void DrawHierarchy(const QSim::sint8 level) const;
    void AddBone(const QSim::sint16 length, const QSim::sint8 parent_id);
    //void AddPart(const TotalGeometry& geometry, const int parent_bone);
    void AddAnimation(const Animation& animation);
    void SetAnimation(QSim::uint32 animation_id);
    int GetNumberOfBones(void) const;

    QSim::uint32 m_CurrentFrame;
    QSim::uint32 m_PlayedAnimation;
    QSim::uint32 m_AnimationWait;
    float m_Scale;

    struct Bone
    {
        QSim::sint16 length;
        QSim::sint8  parent_id;
    };
    std::vector<Bone>             m_Skeleton;
};



#endif // MODEL_H
