#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include "config.h"

namespace config
{
    sf::Texture backgroundTex,
        tank1Tex,
        tank2Tex,
        bulletTex,
        immortalWallTex,
        wallTex;
    

    const int MAP_WIDTH = 65;
    const int MAP_HEIGHT = 36;
    char map[MAP_HEIGHT][MAP_WIDTH] =
    {
        "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii",
        "i                                                      wwwwwiiii",
        "i                                                        wwwwiii",
        "i                  b                                        wwwi",
        "i                                                             wi",
        "i         iiiwwiiiiiiwww                                       i",
        "i            wwwiiiiiwwii                                      i",
        "i       iiiiww                                                 i",
        "i                                               w              i",
        "i                                       iiiiwwwwwwi            i",
        "i                                                              i",
        "i                                                              i",
        "i                                                              i",
        "i                iiiwwiiiiiiiii                                i",
        "i              iiiiiwwwwiiiiiiiiiiii                           i",
        "i               iiiiwwwwwiiiiii                                i",
        "i                 iiwwwwwiiii                                  i",
        "i                                                              i",
        "i                                                              i",
        "i                                                              i",
        "i                                               wwiiiiii       i",
        "i               iiiiwwwwiiiiiiiii    iiiiiiiiww                i",
        "i                       wiiiiiiiwwwiiiii                       i",
        "i                                                              i",
        "i                                                              i",
        "i                                                              i",
        "i                                                        wwwww i",
        "i                                                     wwww     i",
        "i                              iwwwwwiiiiiii                   i",
        "i                   iiiiiiiiiiiiiww                            i",
        "i                                                              i",
        "i                                                              i",
        "i                                          r                   i",
        "i                                                              i",
        "i                                                              i",
        "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii",
    };

    using kb = sf::Keyboard;
    tankControls controls1 = {
        .UP = kb::W,
        .DOWN = kb::S,
        .LEFT = kb::A,
        .RIGHT = kb::D,
        .SHOOT = kb::Space};

    tankControls controls2 = {
        .UP = kb::Up,
        .DOWN = kb::Down,
        .LEFT = kb::Left,
        .RIGHT = kb::Right,
        .SHOOT = kb::Slash};

    std::string relativeAssetsPath = "assets/";

    void prepare()
    {
        if (!backgroundTex.loadFromFile(relativeAssetsPath + "bg.png"))
            std::cout << "cant load bg.png" << std::endl;

        backgroundTex.setRepeated(true);

        if (!tank1Tex.loadFromFile(relativeAssetsPath + "tankBlue.png"))
            std::cerr << "cant load tankBlue.png" << std::endl;

        if (!tank2Tex.loadFromFile(relativeAssetsPath + "tankRed.png"))
            std::cerr << "cant load tankRed.png" << std::endl;

        if (!bulletTex.loadFromFile(relativeAssetsPath + "bullet.png"))
            std::cerr << "cant load bullet.png" << std::endl;

        if (!immortalWallTex.loadFromFile(relativeAssetsPath + "immortalWall.png"))
            std::cerr << "cant load immortalWall.png" << std::endl;

        if (!wallTex.loadFromFile(relativeAssetsPath + "Wall.png"))
            std::cerr << "cant load Wall.png" << std::endl;
    }

} // namespace config
