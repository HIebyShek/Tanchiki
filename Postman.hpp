#ifndef POSTMAN_HPP
#define POSTMAN_HPP

#include<map>
#include<memory>
#include<functional>

#include<SFML/Window/Event.hpp>
#include<SFML/Graphics/RenderTexture.hpp>

class Postman
{
private:
    using eventHandler = std::function<void()>;
    std::map<sf::Keyboard::Key, eventHandler> recipients;
public:
    bool subscribe(sf::Keyboard::Key sym, eventHandler handler);
    bool unsubscribe(sf::Keyboard::Key sym);
    bool deliver(sf::Keyboard::Key sym);
};

#endif // POSTMAN_HPP