#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <ranges>
#include <string>

#include "Engine.hpp"
#include "LevelScene.hpp"
#include "config.h"

int main(int argc, char **argv)
{
    config::prepare();
    auto &window = Engine::instance().window;
    auto &controller = Engine::instance().sceneController;
    window.create(sf::VideoMode(1280, 720), "Tanks", sf::Style::None);

    sf::Event closeEvent;
    closeEvent.type = sf::Event::Closed;
    Engine::instance().postman.subscribe(closeEvent, [&window]()
                                         { window.close(); });
    window.setPosition({0, 0});

    auto mainScene = std::make_shared<LevelScene>();
    controller.pushScene(mainScene);
    Engine::instance().mainloop();

    return 0;
}

// Чтобы ивенты работали в зависимости от сцены,
// нужно выполнять subscribeToEvents в onStart и onResume,
// и unsubscribe в onDestroy и onPause