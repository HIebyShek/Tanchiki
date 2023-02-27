#include "Postman.hpp"

bool Postman::deliver(sf::Keyboard::Key sym)
{
    if (recipients.contains(sym))
        recipients[sym]();
        return true;
    
    return false;
}

bool Postman::unsubscribe(sf::Keyboard::Key sym)
{
    auto event_it = recipients.find(sym);

    if (event_it != recipients.end())
        recipients.erase(event_it);
    return true;

    return false;
}

bool Postman::subscribe(sf::Keyboard::Key sym, eventHandler handler)
{
    if (recipients.contains(sym))
        return false;

    recipients[sym] = handler;
    return true;
}