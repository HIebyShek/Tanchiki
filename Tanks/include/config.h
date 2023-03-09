namespace config
{
    extern sf::Texture
        backgroundTex,
        tank1Tex,
        tank2Tex,
        bulletTex,
        immortalWallTex,
        wallTex;
    
    extern const int MAP_WIDTH;
    extern const int MAP_HEIGHT;
    extern char map[36][65];

    extern std::string relativeAssetsPath;

#ifndef TANKCONTROLS
#define TANKCONTROLS
    struct tankControls
    {
        using kb = sf::Keyboard;
        kb::Key UP;
        kb::Key DOWN;
        kb::Key LEFT;
        kb::Key RIGHT;
        kb::Key SHOOT;
    };
#endif // TANKCONTROLS

    extern tankControls controls1;
    extern tankControls controls2;

    void prepare();

} // namespace config