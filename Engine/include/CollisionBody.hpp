#ifndef COLLISIONBODY_HPP
#define COLLISIONBODY_HPP

#include <vector>
#include <ranges>
#include <algorithm>
#include <cmath>

#include "Scene.hpp"
#include <SFML/Graphics/Shape.hpp>

#include "defines.hpp"

struct CollisionBody : SceneNode
{
    sf::Vector2f velocity;
    ref<sf::Shape> body;
    bool isDestroyable = true;

    static float calculateSquare(ref<sf::Shape> shape);

    CollisionBody() : body()
    {
        raiseMaskBit(SceneNode::COLLIDABLE);
    }

    //CollisionBody(float _density = 0, float _rigidity = 1) : body()
    //{
        //density = _density;
        //rigidity = _rigidity;
    //    raiseMaskBit(SceneNode::COLLIDABLE);
    //}

    virtual void process(sf::Time delta);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    virtual void collisionCallback(){}

    virtual ~CollisionBody() {}
};

#endif // COLLISIONBODY_HPP