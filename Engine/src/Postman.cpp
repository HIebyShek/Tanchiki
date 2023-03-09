#include "Postman.hpp"

bool equalEvent::operator()(const sf::Event &fst,
                            const sf::Event &snd) const
{
    if (fst.type != snd.type)
        return false;

    switch (fst.type)
    {
    case sf::Event::KeyPressed:
    case sf::Event::KeyReleased:
        return (fst.key.code == snd.key.code) and
               (fst.key.alt == snd.key.alt) and
               (fst.key.control == snd.key.control) and
               (fst.key.shift == snd.key.shift) and
               (fst.key.system == snd.key.system);

    case sf::Event::Closed:
        return fst.type == snd.type;

    default:
        return false;
    }
}

size_t hashEvent::operator()(const sf::Event &event) const
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
    case sf::Event::KeyReleased:
        return std::hash<int>()(event.type) ^
               std::hash<int>()(event.key.code) ^
               std::hash<int>()((event.key.alt ? 1 : 0) << 0) ^
               std::hash<int>()((event.key.control ? 1 : 0) << 1) ^
               std::hash<int>()((event.key.shift ? 1 : 0) << 2) ^
               std::hash<int>()((event.key.system ? 1 : 0) << 3);
        // shifts needs because hash(true) ^ hash(true) equal to zero.

    case sf::Event::Closed:
        return std::hash<int>()(event.type);

    default:
        return std::hash<int>()(event.type); // ???
    }
}

bool Postman::deliver(sf::Event event)
{
    if (recipients.contains(event))
    {
        recipients[event]();
        return true;
    }

    return false;
}

bool Postman::unsubscribe(sf::Event event)
{
    auto event_it = recipients.find(event);

    if (event_it != recipients.end())
        recipients.erase(event_it);
    return true;

    return false;
}

bool Postman::subscribe(sf::Event event, eventHandler handler)
{
    if (recipients.contains(event))
        return false;

    recipients[event] = handler;
    return true;
}