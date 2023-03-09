#include "Scene.hpp"
#include "Engine.hpp"
#include "PhysicsServer.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &&node : nodes)
        target.draw(*node, states);
}

void Scene::process(sf::Time delta)
{
    for (auto &&node : nodes)
        node->process(delta);

    Engine::instance().physicsServer.collide();

    resolveCollisions();
}

void Scene::onStart()
{
    for (auto &&node : nodes)
        node->onStart();
}

void Scene::onDestroy()
{
    for (auto &&node : nodes)
        node->onDestroy();
}

void Scene::onInit()
{
    if (nodes.empty())
        init();
}

void Scene::resolveCollisions()
{
    for (auto &&manifold : manifolds)
    {
        manifold->fst->collisionCallback();
        manifold->snd->collisionCallback();

        if (ccbTable.contains(manifold->fst->mask))
            if (ccbTable[manifold->fst->mask].contains(manifold->snd->mask))
                ccbTable[manifold->fst->mask][manifold->snd->mask](manifold);
    }
    manifolds.clear();
}