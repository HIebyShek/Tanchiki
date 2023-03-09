#ifndef SCENE_HPP
#define SCENE_HPP

#include <functional>
#include <list>
#include <memory>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Time.hpp>

#include "Postman.hpp"
#include "defines.hpp"

struct SceneNode : sf::Drawable
{
    virtual void onStart() {}
    virtual void onDestroy() {}

    virtual void process(sf::Time delta) = 0;
    virtual void subcribeToEvents() {}

    virtual ~SceneNode() {}

    using TypeMask = uint64_t;
    TypeMask mask = 0;

    enum MaskBitProperty
    {
        COLLIDABLE = 1u << 0u,
        MOVEABLE = 1u << 1u,
    };

    void raiseMaskBit(MaskBitProperty property)
    {
        mask |= (1 << (property - 1));
    }

    void dropMaskBit(MaskBitProperty property)
    {
        mask |= ~(1 << property);
    }
};

struct Manifold;

struct Scene : SceneNode
{
    std::list<ref<SceneNode>> nodes;
    std::list<ref<Manifold>> manifolds;
    std::unordered_map<TypeMask,
                       std::unordered_map<TypeMask,
                                          void (*)(ref<Manifold>)>>
        ccbTable; // collision callback table

    virtual void init() = 0;
    virtual void defineCallbacks() = 0;

    virtual void onPause() {}
    virtual void onResume() {}

    void onInit();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void process(sf::Time delta) override;
    virtual void resolveCollisions();
    void onStart() override;
    void onDestroy() override;

    virtual ~Scene() {}
};

#endif // SCENE_HPP