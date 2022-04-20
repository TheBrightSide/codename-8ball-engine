#include <iostream>
#include <SDL2/SDL.h>

#include "GameManager.hpp"

int main(int, char **)
{
    SDL_Init(SDL_INIT_EVERYTHING);

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