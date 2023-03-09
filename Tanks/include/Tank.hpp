#ifndef TANK_HPP
#define TANK_HPP

#include "Bullet.hpp"
#include "CollisionBody.hpp"
#include "Engine.hpp"
#include "config.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include <cmath>

struct Tank : CollisionBody
{
    Tank(const sf::Vector2f &position,
         config::tankControls _controls,
         const sf::Texture *texture);

    ref<Bullet> bullet;
    config::tankControls controls;

    void shoot();

    void onDestroy() override;
    void subcribeToEvents() override;
};

#endif // TANK_HPP