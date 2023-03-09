#ifndef SCENECONTROLLER_HPP
#define SCENECONTROLLER_HPP

#include <list>

#include "Scene.hpp"

struct SceneController
{
    std::list<ref<Scene>> scenes;
    ref<Scene> currentScene = nullptr;

    void pushScene(ref<Scene> scene)
    {
        scenes.push_back(scene);
        if (currentScene)
            currentScene->onPause();

        currentScene = scene;
        currentScene->onStart();
    }

    void popScene()
    {
        if (currentScene)
        {
            currentScene->onDestroy();
            scenes.pop_back();
        }

        currentScene = scenes.back();
        currentScene->onResume();
    }
};

#endif // SCENECONTROLLER_HPP