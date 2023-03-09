#include "Tank.hpp"
#include <iostream>
#include "LevelScene.hpp"

Tank::Tank(const sf::Vector2f &position,
           config::tankControls _controls,
           const sf::Texture *texture)
    : CollisionBody()
{
    mask = LevelScene::TANK;
    controls = _controls;

    body = std::make_shared<sf::RectangleShape>(sf::Vector2f{14, 16});
    body->setTexture(texture);
    body->setPosition(position);
    auto [xsize, ysize] = texture->getSize();
    body->setTextureRect({0, 0, xsize / 5, ysize});
    body->setScale({2.5, 2.5});
    body->setOrigin(xsize / 5 / 2 - 1, ysize / 2 - 1);

    bullet = std::make_shared<Bullet>();

    subcribeToEvents();
}

void Tank::subcribeToEvents()
{
    using kb = sf::Keyboard;
    using et = sf::Event::EventType;

    auto &postman = Engine::instance().postman;

    sf::Event event;
    event.type = et::KeyPressed;
    event.key.alt = false;
    event.key.control = false;
    event.key.shift = false;
    event.key.system = false;

    event.key.code = controls.UP;
    postman.subscribe(event,
                      [this]()
                      {
                          this->body->setRotation(0);
                          this->velocity = {0, -100};
                      });

    event.key.code = controls.DOWN;
    postman.subscribe(event,
                      [this]()
                      {
                          this->body->setRotation(180);
                          this->velocity = {0, 100};
                      });

    event.key.code = controls.LEFT;
    postman.subscribe(event,
                      [this]()
                      {
                          this->body->setRotation(270);
                          this->velocity = {-100, 0};
                      });

    event.key.code = controls.RIGHT;
    postman.subscribe(event,
                      [this]()
                      {
                          this->body->setRotation(90);
                          this->velocity = {100, 0};
                      });

    auto keyReleasedHandlerX = [this]()
    {
        this->velocity.x = 0.f;
    };

    auto keyReleasedHandlerY = [this]()
    {
        this->velocity.y = 0.f;
    };

    event.type = et::KeyReleased;

    event.key.code = controls.UP;
    postman.subscribe(event,
                      keyReleasedHandlerY);

    event.key.code = controls.DOWN;
    postman.subscribe(event,
                      keyReleasedHandlerY);

    event.key.code = controls.LEFT;
    postman.subscribe(event,
                      keyReleasedHandlerX);

    event.key.code = controls.RIGHT;
    postman.subscribe(event,
                      keyReleasedHandlerX);

    event.type = et::KeyPressed;
    event.key.code = controls.SHOOT;
    postman.subscribe(event, [this]()
                      { this->shoot(); });
}

void Tank::onDestroy()
{
    Engine::instance()
        .sceneController
        .currentScene
        ->nodes
        .remove_if([this](auto node)
                   { return this == node.get(); });
    
    using kb = sf::Keyboard;
    using et = sf::Event::EventType;

    auto &postman = Engine::instance().postman;

    sf::Event event;
    event.type = et::KeyPressed;
    event.key.alt = false;
    event.key.control = false;
    event.key.shift = false;
    event.key.system = false;

    event.key.code = controls.UP;
    postman.unsubscribe(event);

    event.key.code = controls.DOWN;
    postman.unsubscribe(event);

    event.key.code = controls.LEFT;
    postman.unsubscribe(event);

    event.key.code = controls.RIGHT;
    postman.unsubscribe(event);

    event.key.code = controls.SHOOT;
    postman.unsubscribe(event);
}

void Tank::shoot()
{
    if (!bullet or !bullet->isReady)
        return;

    auto &scene = Engine::instance().sceneController.currentScene;
    if (!scene)
        return;

    bullet->isReady = false;
    scene->nodes.push_back(bullet);
    auto &pos = body->getPosition();
    float angle = body->getRotation();
    sf::Vector2f bulletPosition;
    float offset = body->getTextureRect().height / 2 * body->getScale().y +
                   bullet->body->getTextureRect().height / 2 * bullet->body->getScale().y;

    switch ((int)angle)
    {
    case 0:
        bulletPosition = {pos.x, pos.y - offset};
        bullet->velocity = {0, -500};
        break;
    case 90:
        bulletPosition = {pos.x + offset, pos.y};
        bullet->velocity = {500, 0};
        break;
    case 180:
        bulletPosition = {pos.x, pos.y + offset};
        bullet->velocity = {0, 500};
        break;
    case 270:
        bulletPosition = {pos.x - offset, pos.y};
        bullet->velocity = {-500, 0};
        break;

    default:
        break;
    }
    bullet->body->setPosition(bulletPosition);
    bullet->body->setRotation(body->getRotation());
}