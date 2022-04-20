#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GameManager.hpp"

int main(int, char **)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    GameManager* game_manager = GameManager::GetInstance();
    game_manager->Initialize();

    while (!game_manager->ShouldQuit())
    {
        game_manager->Update();
    }

    game_manager->Deinitialize();

    SDL_Quit();
    return 0;
}