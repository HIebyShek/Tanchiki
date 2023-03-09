#include "Bullet.hpp"
#include "Engine.hpp"
#include "LevelScene.hpp"
#include "config.h"

Bullet::Bullet() : CollisionBody()
{
    mask = LevelScene::BULLET;

    body = std::make_shared<sf::RectangleShape>(sf::Vector2f{4, 6});
    body->setTexture(&config::bulletTex);
    auto size = body->getLocalBounds();
    body->setOrigin(size.width / 2., size.height / 2.);
    body->setScale(2, 2);
}

void Bullet::onDestroy()
{
    auto scene = Engine::instance()
                     .sceneController
                     .currentScene;
    if (!scene)
        return;

    isReady = true;
    velocity = {0, 0};
    scene->nodes
        .remove_if([this](auto node)
                   { return this == node.get(); });
}