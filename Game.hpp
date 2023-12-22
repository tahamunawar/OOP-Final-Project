#ifdef __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <SDL2_ttf/SDL_ttf.h>
    #include <SDL2_mixer/SDL_mixer.h>
#else
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
#endif

#include "powerup.hpp"
#include <iostream>
#include <vector>

enum GameState {
    STARTUP,
    level1, 
    gameOver,
    gameWon
};

class Game {
public:
    Game();
    ~Game();
    void run();
    void initializePowerUps();

private:
    bool isPointInsideRect(int x, int y, SDL_Rect rect);
    void handleEvents();
    void update();
    void renderStartup();
    void renderLevel1();
    void renderGameOver();
    void renderGameWon();
    void clean();
    GameState gamestate;

    Mix_Music* backgroundMusic;
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

    SDL_Texture* platformTexture;
    SDL_Rect platformRect;

    bool quit;
    bool gameStarted;
    bool showInstructions;
    Uint32 instructionsStartTime;
    Uint32 instructionsDisplayDuration;
    bool checkCollision(const SDL_Rect& rect1, const SDL_Rect& rect2);
    bool checkPlatformCollision(const SDL_Rect& rect1, const SDL_Rect& rect2);
    std::vector<PowerUp*> powerUps;
};

