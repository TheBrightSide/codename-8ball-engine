#include <iostream>

#define USE_RAYLIB
#include "GameManager.hpp"

int main()
{
    GameManager* game_manager = GameManager::GetInstance();
    game_manager->Initialize();

    while (!game_manager->ShouldQuit())
    {
        game_manager->Update();
    }

    game_manager->Deinitialize();
    return 0;
}