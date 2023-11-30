#include "Game.hpp"
#include "unit.hpp"
#include "Spiderman.hpp"
#include "healthpowerup.hpp"
#include "attackpowerup.hpp"
#include "goblin.hpp"

Spiderman spooder;

Game::Game() : quit(false), gameStarted(false), showInstructions(false), instructionsStartTime(0), instructionsDisplayDuration(2000), gamestate(STARTUP) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        quit = true;
        return;
    }

    // Initialize SDL_image
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        quit = true;
        return;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        quit = true;
        return;
    }

    // Create a window
    window = SDL_CreateWindow("SDL PNG Background", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        quit = true;
        return;
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        quit = true;
        return;
    }

    // Load background PNG image
    backgroundTexture = IMG_LoadTexture(renderer, "background.png");
    if (backgroundTexture == nullptr) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        clean();
        quit = true;
        return;
    }

    // Load start button PNG image
    startButtonTexture = IMG_LoadTexture(renderer, "start.png");
    if (startButtonTexture == nullptr) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        clean();
        quit = true;
        return;
    }

    // Load instructions button PNG image
    instructionsButtonTexture = IMG_LoadTexture(renderer, "instructions.png");
    if (instructionsButtonTexture == nullptr) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        clean();
        quit = true;
        return;
    }

    // Load font
    font = TTF_OpenFont("/Users/tahamunawar/Desktop/EDUCATION/1) HABIB UNIVERSITY (VERY IMPORTANT FOLDER)/Sem 3/OOPLECTURE/project stuff/retro.ttf", 24);
    if (font == nullptr) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        clean();
        quit = true;
        return;
    }

    // Create texture for instructions message
    SDL_Color textColor = { 255, 255, 255 }; // White color
    SDL_Surface* firstSentenceSurface = TTF_RenderText_Solid(font, "This is the first sentence", textColor);
    firstSentenceTexture = SDL_CreateTextureFromSurface(renderer, firstSentenceSurface);
    firstSentenceRect = { 100, 400, firstSentenceSurface->w, firstSentenceSurface->h };
    SDL_FreeSurface(firstSentenceSurface);

    // Create texture for second sentence of instructions message
    SDL_Surface* secondSentenceSurface = TTF_RenderText_Solid(font, "This is the second sentence", textColor);
    secondSentenceTexture = SDL_CreateTextureFromSurface(renderer, secondSentenceSurface);
    secondSentenceRect = { 100, 430, secondSentenceSurface->w, secondSentenceSurface->h };
    SDL_FreeSurface(secondSentenceSurface);

    // Button rectangles
    startButtonRect = { 350, 150, 300, 100 };
    instructionsButtonRect = { 350, 300, 300, 50 };

    spooder = Spiderman(renderer);
}

Game::~Game() {
    clean();
}

void Game::run() {
    while (!quit) {
        handleEvents();
        update();
        if (gamestate == STARTUP) renderStartup();
        else if (gamestate == level1) renderLevel1();
    }
}

bool Game::isPointInsideRect(int x, int y, SDL_Rect rect) {
    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    if (gamestate == STARTUP) {
                        if (isPointInsideRect(mouseX, mouseY, startButtonRect)) {
                            gamestate = level1;
                        } else if (isPointInsideRect(mouseX, mouseY, instructionsButtonRect)) {
                            showInstructions = true;
                            instructionsStartTime = SDL_GetTicks();
                        }
                    }
                    // Add more conditions for other states if needed
                }
                break;
        }
    }
}

void Game::update() {
    if (showInstructions) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - instructionsStartTime >= instructionsDisplayDuration) {
            showInstructions = false;
        }
    }

    // Add more logic for other states if needed
}

void Game::renderLevel1() {
    // Clear the renderer
    SDL_RenderClear(renderer);

    // Render the background texture
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

    Goblin gg = Goblin(renderer);
    AttackPowerUp firstAttack = AttackPowerUp(renderer, 400, 400);
    AttackPowerUp secondAttack = AttackPowerUp(renderer, 300, 300);
    HealthPowerUp firstHealth = HealthPowerUp(renderer, 100, 100);
    HealthPowerUp secondHealth = HealthPowerUp(renderer, 200, 200);

    // Render all things in this level
    gg.render();
    spooder.render();
    firstAttack.render();
    secondAttack.render();
    firstHealth.render();
    secondHealth.render();

    // Update the window
    SDL_RenderPresent(renderer);
}

void Game::renderStartup(){
    // Clear the renderer
    SDL_RenderClear(renderer);

    // Render the background texture
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

    // Render start button
    SDL_RenderCopy(renderer, startButtonTexture, nullptr, &startButtonRect);

    // Render instructions button
    SDL_RenderCopy(renderer, instructionsButtonTexture, nullptr, &instructionsButtonRect);

    if (showInstructions) {
        // Render the first sentence of instructions
        SDL_RenderCopy(renderer, firstSentenceTexture, nullptr, &firstSentenceRect);

        // Render the second sentence of instructions
        SDL_RenderCopy(renderer, secondSentenceTexture, nullptr, &secondSentenceRect);
    }

    // Update the window
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(startButtonTexture);
    SDL_DestroyTexture(instructionsButtonTexture);
    TTF_CloseFont(font);
    SDL_DestroyTexture(firstSentenceTexture);
    SDL_DestroyTexture(secondSentenceTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

