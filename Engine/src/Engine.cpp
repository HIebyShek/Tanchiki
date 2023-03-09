#include "Engine.hpp"

void Engine::mainloop(size_t frameLimit)
{
    sf::Time delta = sf::Time::Zero;
    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
            postman.deliver(event);

        delta = clock.restart();
        if (sceneController.currentScene)
        {
            sceneController.currentScene->process(delta);
            window.clear();
            window.draw(*sceneController.currentScene);
        }

        window.display();
    }
}