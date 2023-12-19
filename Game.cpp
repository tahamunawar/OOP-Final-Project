#include "Game.hpp"

#include "unit.hpp"
#include "Spiderman.hpp"
#include "healthpowerup.hpp"
#include "attackpowerup.hpp"
#include "goblin.hpp"

//initalising global objects
Spiderman spooder;
Goblin gg;
int backgroundX = 0;

//constructor call
Game::Game() : quit(false), gameStarted(false), showInstructions(false), instructionsStartTime(0), instructionsDisplayDuration(2000), gamestate(STARTUP) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        quit = true;
        return;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        clean();
        quit = true;
        return;
    }
    //loading background music
    backgroundMusic = Mix_LoadMUS("home screen.mp3");
    if (backgroundMusic == nullptr) {
        std::cerr << "Mix_LoadMUS Error: " << Mix_GetError() << std::endl;
        clean();
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

    //load platform texture
    platformTexture = IMG_LoadTexture(renderer, "platform.png");
    if (platformTexture == nullptr) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        clean();
        quit = true;
        return;
    }

    // Load font
    font = TTF_OpenFont("font2.ttf", 24);
    if (font == nullptr) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        clean();
        quit = true;
        return;
    }

    // Create texture for instructions message
    SDL_Color textColor = { 255, 255, 255 }; // White color
    SDL_Surface* firstSentenceSurface = TTF_RenderText_Solid(font, "Move via WASD movements. Shoot Goblin via P.", textColor);
    firstSentenceTexture = SDL_CreateTextureFromSurface(renderer, firstSentenceSurface);
    firstSentenceRect = { 100, 400, firstSentenceSurface->w, firstSentenceSurface->h };
    SDL_FreeSurface(firstSentenceSurface);

    // Create texture for second sentence of instructions message
    SDL_Surface* secondSentenceSurface = TTF_RenderText_Solid(font, "Avoid goblin's attacks and get powerups for an extra boost.", textColor);
    secondSentenceTexture = SDL_CreateTextureFromSurface(renderer, secondSentenceSurface);
    secondSentenceRect = { 100, 430, secondSentenceSurface->w, secondSentenceSurface->h };
    SDL_FreeSurface(secondSentenceSurface);

    // Button rectangles
    startButtonRect = { 350, 150, 300, 100 };
    instructionsButtonRect = { 350, 300, 300, 50 };
    platformRect = {160, 760, 2000, 70};

    //adding powerups to our vector
    PowerUp* att1 = new AttackPowerUp(renderer, 660, 250);
    PowerUp* att2 = new AttackPowerUp(renderer, 360, 370);
    PowerUp* health1 = new HealthPowerUp(renderer, 850, 500);
    powerUps.push_back(att1);
    powerUps.push_back(att2);
    powerUps.push_back(health1);

    spooder = Spiderman(renderer);
    gg = Goblin(renderer);
}

Game::~Game() {
    clean();
}

//initialising powerups
void Game::initializePowerUps()
{   
    /*
    if (SDL_GetTicks() % 5000 == 0){
        PowerUp* p;
        switch(rand() % 2){
            case 0: p = new AttackPowerUp(renderer, 600 + 100, 100); break; 
            case 1: p = new HealthPowerUp(renderer, 600 + 100, 100); break; 
        }
        powerUps.push_back(p);
    }
    */
    for (auto it = powerUps.begin(); it != powerUps.end(); )
    {   
        if ((*it)->isMarkedForDeletion())
        {
            delete *it;  
            it = powerUps.erase(it);
        }
        else
        {
            it++;
        }
    }
}

//checking for collisions between two objects
bool Game::checkCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) 
{
    return rect1.x < rect2.x + rect2.w &&
           rect1.x + rect1.w > rect2.x &&
           rect1.y < rect2.y + rect2.h &&
           rect1.y + rect1.h > rect2.y;
}

//checking for collision between an object and a platform
bool Game::checkPlatformCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) 
{
    return rect1.x < rect2.x + rect2.w &&
           rect1.x + rect1.w > rect2.x &&
           rect1.y < rect2.y + rect2.h &&
           rect1.y + rect1.h >= rect2.y;
}

//running the game
void Game::run() {
    while (!quit) {
        handleEvents();
        update();
        if (gamestate == STARTUP) renderStartup();
        else if (gamestate == level1){
            spooder.update();
            renderLevel1();
        }
        else if (gamestate == gameOver)
        {
            renderGameOver();
        }
        else if (gamestate == gameWon)
        {
            renderGameWon();
        } 
    }
}

bool Game::isPointInsideRect(int x, int y, SDL_Rect rect) {
    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}

//handling for events
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
                }
                break;
            case SDL_KEYDOWN:
                // Check for keydown events to move Spiderman
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        spooder.moveLeft();
                        break;
                    case SDLK_d:
                        spooder.moveRight();
                        break;
                    case !SDLK_d && !SDLK_a:
                        spooder.resetVelocity();
                        break;
                    case SDLK_w:
                        spooder.jump();
                        break;
                    case SDLK_p:
                        spooder.shootWeb();
                        break;
                    }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        spooder.resetVelocity();
                        break;
                    case SDLK_d:
                        spooder.resetVelocity();
                        break;
                    }
                break;
        }
    }
}

void Game::update() {
    if (gamestate == STARTUP)
    {
        if (showInstructions) {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - instructionsStartTime >= instructionsDisplayDuration) {
                showInstructions = false;
            }
        }
        Mix_PlayMusic(backgroundMusic, -1);
    }
    else if (gamestate == level1)
    {
        SDL_DestroyTexture(startButtonTexture);
        SDL_DestroyTexture(instructionsButtonTexture);
        SDL_DestroyTexture(firstSentenceTexture);
        SDL_DestroyTexture(secondSentenceTexture);
        if (spooder.getHealth() <= 0) {
            gamestate = gameOver;

        }
        if (gg.getHealth() <=0) {
            gamestate = gameWon;
        }
        {
            const int backgroundScrollSpeed = 1;
            backgroundX += backgroundScrollSpeed;

            if (backgroundX >= 1000) {
                backgroundX = 0;
            }
        }
                
        // Check collision between Spiderman and projectiles
        for (auto& projectile : gg.getProjectiles()) {
            if (checkCollision(spooder.getMoverRect(), projectile->getMoverRect())) {
                spooder - 8;
                
                projectile->markForDeletion();
            }
            else if (checkPlatformCollision(projectile->getMoverRect(), {300, 420, 200, 25}) 
                  || checkPlatformCollision(projectile->getMoverRect(), {600, 300, 200, 25})) 
                projectile->markForDeletion();
        }
        // Check if spiderman picked up the powerups or not
        for (auto& powerUp : powerUps) {
        if (checkCollision(spooder.getMoverRect(), powerUp->getMoverRect())) {
           
            powerUp->applyPowerUp(spooder);
            
            powerUp->MarkForDeletion();
            }
        }
        // Check if spiderman's webs collide with goblin or not
        for (auto& web : spooder.getWebs()) {
            if ((checkCollision(gg.getMoverRect(), web->getMoverRect())) or (checkCollision(gg.getMoverRect(), {300, 470, 200, 20}))) 
            {
                gg.takeDamage(spooder.getDamage());
                
                web->markForDeletion();
            }
            else if (checkPlatformCollision(web->getMoverRect(), {300, 420, 200, 25}) 
                  || checkPlatformCollision(web->getMoverRect(), {600, 300, 200, 25})) 
                web->markForDeletion();
        }

        // Update spiderman attack boost
        spooder.updateAttackBoost();
        spooder.updateWeb();
        gg.update();

       
        if (checkPlatformCollision(spooder.getMoverRect(), {300, 420, 200, 25})) {
       
        spooder.handleCollision({300, 420, 200, 25});
        }

        if (checkPlatformCollision(spooder.getMoverRect(), {600, 300, 200, 25})) {
        
        spooder.handleCollision({600, 300, 200, 25});
        }
    }
}

void Game::renderLevel1() {
    SDL_RenderClear(renderer);

    // Render the background texture
    SDL_Rect backgroundRect = { backgroundX, 0, 1000, 600 };
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, &backgroundRect);

    SDL_Rect backgroundRectExtra = { backgroundX - 1000, 0, 1000, 600 };
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, &backgroundRectExtra);

    // Render the ground platform
    SDL_Rect groundPlatformCoords = {-20, 550, 1200, 100};
    SDL_RenderCopy(renderer, platformTexture, &platformRect, &groundPlatformCoords);

    // Render the first elevated platform
    SDL_Rect elevatedPlatform1Coords = {300, 420, 200, 20}; // Adjust the position and size
    SDL_RenderCopy(renderer, platformTexture, &platformRect, &elevatedPlatform1Coords);

    // Render the second elevated platform
    SDL_Rect elevatedPlatform2Coords = {600, 300, 200, 20}; // Adjust the position and size
    SDL_RenderCopy(renderer, platformTexture, &platformRect, &elevatedPlatform2Coords);

    initializePowerUps();

    // Render all things in this level
    spooder.render();
    gg.render();
    gg.updateProjectiles();
    for (auto& powerUp : powerUps) {
            powerUp->render();
        }
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

void Game::renderGameOver()
{
    SDL_RenderClear(renderer);
    SDL_DestroyTexture(backgroundTexture);
    SDL_Texture* overScreenTexture = IMG_LoadTexture(renderer, "gameOverMaster.png");
    if (overScreenTexture == nullptr) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        clean();
        quit = true;
        return;
    }
    SDL_RenderCopy(renderer, overScreenTexture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void Game::renderGameWon()
{
    SDL_RenderClear(renderer);
    SDL_DestroyTexture(backgroundTexture);
    SDL_Texture* wonScreenTexture = IMG_LoadTexture(renderer, "gameWon.png");
    if (wonScreenTexture == nullptr) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        clean();
        quit = true;
        return;
    }
    SDL_RenderCopy(renderer, wonScreenTexture, nullptr, nullptr);
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
    Mix_FreeMusic(backgroundMusic);
    Mix_CloseAudio();
}


