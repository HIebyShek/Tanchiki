#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "Scene.hpp"
#include "Engine.hpp"
#include "defines.hpp"
#include "config.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

struct Background : SceneNode
{
    sf::Sprite bg;

    Background()
    {
        bg.setTexture(config::backgroundTex);

        auto winSize = Engine::instance().window.getSize();
        auto winPos = Engine::instance().window.getPosition();
        bg.setTextureRect(sf::IntRect(winPos.x, winPos.y, winSize.x, winSize.y));
    }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(bg, states);
    }

    virtual void onStart() override{

    };
    virtual void onDestroy() override{};
    virtual void process(sf::Time delta) override{};
    virtual void subcribeToEvents() override{};
};

#endif // BACKGROUND_HPP