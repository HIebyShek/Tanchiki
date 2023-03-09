#ifndef BULLET_HPP
#define BULLET_HPP

#include "CollisionBody.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

struct Bullet : CollisionBody
{
    bool isReady = true;

    Bullet();

    void onStart() override {}
    void onDestroy() override;
    
    void subcribeToEvents() override {}
};


#endif // BULLET_HPP