#ifndef WALL_HPP
#define WALL_HPP

#include "CollisionBody.hpp"
#include "LevelScene.hpp"

struct Wall : CollisionBody
{

    Wall(const sf::Vector2f &position,
         const sf::Texture *texture,
         bool _isDestoryable = true);

    void onDestroy() override;
};

#endif // WALL_HPP