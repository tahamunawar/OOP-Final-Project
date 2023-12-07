#ifdef __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <SDL2_ttf/SDL_ttf.h>
#else
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#endif

#include <iostream>

enum GameState {
    STARTUP,
    MAIN_GAME,
    // Add more states if needed
    level1
};

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    bool isPointInsideRect(int x, int y, SDL_Rect rect);
    void handleEvents();
    void update();
    void renderStartup();
    void renderLevel1();
    void clean();
    GameState gamestate;

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* backgroundTexture;
    SDL_Texture* startButtonTexture;
    SDL_Texture* instructionsButtonTexture;
    TTF_Font* font;

    SDL_Texture* firstSentenceTexture;
    SDL_Rect firstSentenceRect;

    SDL_Texture* secondSentenceTexture;
    SDL_Rect secondSentenceRect;

    SDL_Rect startButtonRect;
    SDL_Rect instructionsButtonRect;

    bool quit;
    bool gameStarted;
    bool showInstructions;
    Uint32 instructionsStartTime;
    Uint32 instructionsDisplayDuration;
};

