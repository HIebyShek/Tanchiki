#ifndef LEVELSCENE_HPP
#define LEVELSCENE_HPP

#include "Background.hpp"
#include "PhysicsServer.hpp"
#include "Scene.hpp"
#include "Tank.hpp"
#include "Wall.hpp"

struct LevelScene : Scene
{
    enum NodeType
    {
        TANK     = SceneNode::COLLIDABLE | SceneNode::MOVEABLE | (1lu << 32),
        BULLET   = SceneNode::COLLIDABLE | SceneNode::MOVEABLE | (1lu << 33),
        MWALL    = SceneNode::COLLIDABLE | SceneNode::MOVEABLE | (1lu << 34),
        WALL     = SceneNode::COLLIDABLE | (1lu << 34),
    };

    LevelScene();

    virtual void init() override;
    virtual void subcribeToEvents() override {}

    void defineCallbacks();
    
};

#endif // LEVELSCENE_HPP

// algo for calculating impulse, something like "realistic" collisions
// auto relativeVelocity = snd->velocity - fst->velocity;
// auto relativeToNormal = relativeVelocity.x * manifold->normal.x +
//                        relativeVelocity.y * manifold->normal.y; // dot product

// if (relativeToNormal > 0.f)
//     return;

// auto minRigidity = std::min(fst->rigidity, snd->rigidity);
// float impulse = -(1 + minRigidity) * relativeToNormal;

// float invmass1 = fabs(fst->mass) > 0.001f ? 1 / fst->mass : 0.f;
// float invmass2 = fabs(snd->mass) > 0.001f ? 1 / snd->mass : 0.f;
// impulse /= invmass1 + invmass2;

// fst->velocity -= invmass1 * impulse * manifold->normal;
// snd->velocity += invmass2 * impulse * manifold->normal;