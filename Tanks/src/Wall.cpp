#include "Wall.hpp"

Wall::Wall(const sf::Vector2f &position,
           const sf::Texture *texture,
           bool _isDestoryable)
    : CollisionBody()
{
    mask = LevelScene::WALL;
    isDestroyable = _isDestoryable;

    body = std::make_shared<sf::RectangleShape>(sf::Vector2f{20.f, 20.f});
    body->setTexture(texture);

    body->setPosition(position);
}

void Wall::onDestroy()
{
    Engine::instance()
        .sceneController
        .currentScene
        ->nodes
        .remove_if([this](auto node)
                   { return this == node.get(); });
}