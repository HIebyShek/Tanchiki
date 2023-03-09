#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Sleep.hpp>

#include "PhysicsServer.hpp"
#include "SceneController.hpp"
#include "defines.hpp"

class Engine
{
public:
    SceneController sceneController;
    Postman postman;
    sf::RenderWindow window;
    sf::Clock clock;
    PhysicsServer physicsServer;

    Engine() {}
    ~Engine() {}

    Engine(const Engine& other) = delete;
    Engine(Engine&& other) = delete;
    Engine &operator=(const Engine& other) = delete;
    Engine &operator=(Engine&& other) = delete;

    static Engine &instance()
    {
        static Engine engine;
        return engine;
    }

    void mainloop(size_t frameLimit = 0);
    
};

#endif // ENGINE_HPP