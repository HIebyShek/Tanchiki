#include "LevelScene.hpp"

LevelScene::LevelScene()
{
    init();
    defineCallbacks();
}

void LevelScene::init()
{
    nodes.push_back(std::make_shared<Background>());
    // nodes.push_back(std::make_shared<Tank>(sf::Vector2f{50.f, 50.f}, config::controls1, &config::tank1Tex));
    // nodes.push_back(std::make_shared<Tank>(sf::Vector2f{200.f, 50.f}, config::controls2, &config::tank2Tex));
    // for (float i = 0.f; i < 1280.f; i += 20.f)
    //{
    //     nodes.push_back(std::make_shared<Wall>(sf::Vector2f{i, 0.f}, &config::immortalWallTex, false));
    //     nodes.push_back(std::make_shared<Wall>(sf::Vector2f{i, 700.f}, &config::immortalWallTex, false));
    // }
    // for (float i = 20.f; i < 700.f; i += 20.f)
    //{
    //     nodes.push_back(std::make_shared<Wall>(sf::Vector2f{0.f, i}, &config::immortalWallTex, false));
    //     nodes.push_back(std::make_shared<Wall>(sf::Vector2f{1260.f, i}, &config::immortalWallTex, false));
    // }
    for (int i = 0; i < config::MAP_HEIGHT; ++i)
        for (int j = 0; j < config::MAP_WIDTH; ++j)
        {
            switch (config::map[i][j])
            {
            case 'i':
                nodes.push_back(std::make_shared<Wall>(sf::Vector2f{j * 20, i * 20}, &config::immortalWallTex, false));
                break;

            case 'b':
                nodes.push_back(std::make_shared<Tank>(sf::Vector2f{j * 20.f, i * 20.f}, config::controls1, &config::tank1Tex));
                break;

            case 'r':
                nodes.push_back(std::make_shared<Tank>(sf::Vector2f{j * 20.f, i * 20.f}, config::controls2, &config::tank2Tex));
                break;

            case 'w':
                auto wall = std::make_shared<Wall>(sf::Vector2f{j * 20, i * 20}, &config::wallTex, true);
                wall->raiseMaskBit(SceneNode::MOVEABLE);
                nodes.push_back(wall);
                break;
            }
        }
}

void LevelScene::defineCallbacks()
{
    ccbTable[TANK][TANK] =
        [](auto manifold)
    {
        auto fst = manifold->fst;
        auto snd = manifold->snd;

        if (((fst->mask & SceneNode::MOVEABLE) == SceneNode::MOVEABLE)
            and ((snd->mask & SceneNode::MOVEABLE) == SceneNode::MOVEABLE))
        {
            fst->body->move(-manifold->normal * (manifold->depth / 2));
            snd->body->move(manifold->normal * (manifold->depth / 2));
            return;
        }

        if ((snd->mask & SceneNode::MOVEABLE) == SceneNode::MOVEABLE)
            snd->body->move(manifold->normal * (manifold->depth));

        if ((fst->mask & SceneNode::MOVEABLE) == SceneNode::MOVEABLE)
            fst->body->move(-manifold->normal * (manifold->depth));
    };

    ccbTable[BULLET][BULLET] =
        [](auto manifold)
    {
        auto fst = manifold->fst;
        auto snd = manifold->snd;
        if (fst->isDestroyable)
            fst->onDestroy();
        if (snd->isDestroyable)
            snd->onDestroy();
    };

    ccbTable[BULLET][TANK] = ccbTable[BULLET][BULLET];
    ccbTable[TANK][BULLET] = ccbTable[BULLET][BULLET];
    ccbTable[BULLET][WALL] = ccbTable[BULLET][BULLET];
    ccbTable[WALL][BULLET] = ccbTable[BULLET][BULLET];
    ccbTable[WALL][TANK] = ccbTable[TANK][TANK];
    ccbTable[TANK][WALL] = ccbTable[TANK][TANK];
    ccbTable[TANK][MWALL] = ccbTable[TANK][TANK];
    ccbTable[MWALL][TANK] = ccbTable[TANK][TANK];
    ccbTable[MWALL][MWALL] = ccbTable[TANK][TANK];
    ccbTable[WALL][MWALL] = ccbTable[TANK][TANK];
    ccbTable[MWALL][WALL] = ccbTable[TANK][TANK];
    ccbTable[BULLET][MWALL] = ccbTable[BULLET][BULLET];
    ccbTable[MWALL][BULLET] = ccbTable[BULLET][BULLET];
}