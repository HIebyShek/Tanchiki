#ifndef POSTMAN_HPP
#define POSTMAN_HPP

#include <functional>
#include <memory>
#include <unordered_map>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Window/Event.hpp>

#include <cstring>

struct equalEvent
{
    bool operator()(const sf::Event &fst,
                    const sf::Event &snd) const;
}; // here equality checks only for needed event types

struct hashEvent
{
    size_t operator()(const sf::Event &event) const;
};

class Postman
{
private:
    using eventHandler = std::function<void()>;
    std::unordered_map<sf::Event,
                       eventHandler,
                       hashEvent,
                       equalEvent>
        recipients;

public:
    bool subscribe(sf::Event event, eventHandler handler);
    bool unsubscribe(sf::Event sym);
    bool deliver(sf::Event sym);
};

#endif // POSTMAN_HPP