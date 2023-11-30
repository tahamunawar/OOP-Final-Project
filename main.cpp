// #include <SDL2/SDL.h>
// #include <SDL2_image/SDL_image.h>
// #include <SDL2_ttf/SDL_ttf.h>
// #include <iostream>

// bool isPointInsideRect(int x, int y, SDL_Rect rect) {
//     return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
// }

// int main(int argc, char* argv[]) {
//     // Initialize SDL
//     if (SDL_Init(SDL_INIT_VIDEO) != 0) {
//         std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
//         return 1;
//     }

//     // Initialize SDL_image
//     if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
//         std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
//         SDL_Quit();
//         return 1;
//     }

//     // Initialize SDL_ttf
//     if (TTF_Init() == -1) {
//         std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
//         return 1;
//     }

//     // Create a window
//     SDL_Window* window = SDL_CreateWindow("SDL PNG Background", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600, SDL_WINDOW_SHOWN);
//     if (window == nullptr) {
//         std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
//         IMG_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     // Create a renderer
//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//     if (renderer == nullptr) {
//         std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
//         SDL_DestroyWindow(window);
//         IMG_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     // Load background PNG image
//     SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "background.png");
//     if (backgroundTexture == nullptr) {
//         std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
//         SDL_DestroyRenderer(renderer);
//         SDL_DestroyWindow(window);
//         IMG_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     // Load start button PNG image
//     SDL_Texture* startButtonTexture = IMG_LoadTexture(renderer, "start.png");
//     if (startButtonTexture == nullptr) {
//         std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
//         SDL_DestroyTexture(backgroundTexture);
//         SDL_DestroyRenderer(renderer);
//         SDL_DestroyWindow(window);
//         IMG_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     // Load instructions button PNG image
//     SDL_Texture* instructionsButtonTexture = IMG_LoadTexture(renderer, "instructions.png");
//     if (instructionsButtonTexture == nullptr) {
//         std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
//         SDL_DestroyTexture(startButtonTexture);
//         SDL_DestroyTexture(backgroundTexture);
//         SDL_DestroyRenderer(renderer);
//         SDL_DestroyWindow(window);
//         IMG_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     // Load font
//     TTF_Font* font = TTF_OpenFont("/Users/tahamunawar/Desktop/EDUCATION/1) HABIB UNIVERSITY (VERY IMPORTANT FOLDER)/Sem 3/OOPLECTURE/project stuff/retro.ttf", 24);
//     if (font == nullptr) {
//         std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
//         SDL_DestroyTexture(instructionsButtonTexture);
//         SDL_DestroyTexture(startButtonTexture);
//         SDL_DestroyTexture(backgroundTexture);
//         SDL_DestroyRenderer(renderer);
//         SDL_DestroyWindow(window);
//         IMG_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     // Create texture for instructions message
//     SDL_Color textColor = { 255, 255, 255 }; // White color
//     SDL_Surface* firstSentenceSurface = TTF_RenderText_Solid(font, "This is the first sentence", textColor);
//     SDL_Texture* firstSentenceTexture = SDL_CreateTextureFromSurface(renderer, firstSentenceSurface);
//     SDL_Rect firstSentenceRect = { 100, 400, firstSentenceSurface->w, firstSentenceSurface->h };
//     SDL_FreeSurface(firstSentenceSurface);

//     // Create texture for second sentence of instructions message
//     SDL_Surface* secondSentenceSurface = TTF_RenderText_Solid(font, "This is the second sentence", textColor);
//     SDL_Texture* secondSentenceTexture = SDL_CreateTextureFromSurface(renderer, secondSentenceSurface);
//     SDL_Rect secondSentenceRect = { 100, 430, secondSentenceSurface->w, secondSentenceSurface->h };
//     SDL_FreeSurface(secondSentenceSurface);

//     // Button rectangles
//     SDL_Rect startButtonRect = { 350, 150, 300, 100 };
//     SDL_Rect instructionsButtonRect = { 350, 300, 300, 50 };

// // Main loop
//     bool quit = false;
//     bool gameStarted = false;
//     bool showInstructions = false;
//     Uint32 instructionsStartTime = 0;
//     Uint32 instructionsDisplayDuration = 2000; // Duration in milliseconds (adjust as needed)

//     while (!quit) {
//         SDL_Event event;
//         while (SDL_PollEvent(&event)) {
//             switch (event.type) {
//                 case SDL_QUIT:
//                     quit = true;
//                     break;
//                 case SDL_MOUSEBUTTONDOWN:
//                     if (event.button.button == SDL_BUTTON_LEFT) {
//                         int mouseX = event.button.x;
//                         int mouseY = event.button.y;

//                         if (isPointInsideRect(mouseX, mouseY, startButtonRect)) {
//                             gameStarted = true;
//                         } else if (isPointInsideRect(mouseX, mouseY, instructionsButtonRect)) {
//                             showInstructions = true;
//                             instructionsStartTime = SDL_GetTicks(); // Record the start time
//                         }
//                     }
//                     break;
//             }
//         }

//         // Clear the renderer
//         SDL_RenderClear(renderer);

//         // Render the background texture
//         SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

//         // Render start button
//         SDL_RenderCopy(renderer, startButtonTexture, nullptr, &startButtonRect);

//         // Render instructions button
//         SDL_RenderCopy(renderer, instructionsButtonTexture, nullptr, &instructionsButtonRect);

//         if (showInstructions) {
//             // Render the first sentence of instructions
//             SDL_RenderCopy(renderer, firstSentenceTexture, nullptr, &firstSentenceRect);

//             // Render the second sentence of instructions
//             SDL_RenderCopy(renderer, secondSentenceTexture, nullptr, &secondSentenceRect);

//             Uint32 currentTime = SDL_GetTicks();
//             if (currentTime - instructionsStartTime >= instructionsDisplayDuration) {
//                 showInstructions = false; // Hide instructions after the specified duration
//             }
//         }

//         // Update the window
//         SDL_RenderPresent(renderer);


        
//     }

//     // Clean up
//     SDL_DestroyTexture(backgroundTexture);
//     SDL_DestroyTexture(startButtonTexture);
//     SDL_DestroyTexture(instructionsButtonTexture);
//     TTF_CloseFont(font);
//     SDL_DestroyTexture(firstSentenceTexture);
//     SDL_DestroyTexture(secondSentenceTexture);
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     IMG_Quit();
//     SDL_Quit();

//     return 0;
// }

#include "Game.hpp"

int main(int argc, char* argv[]) {
    Game game;
    game.run();
    return 0;
}
