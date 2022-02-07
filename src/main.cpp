#include <iostream>
#include <raylib.h>

#include "GameManager.hpp"

int main()
{
    GameManager::Initialize();

    while (!GameManager::ShouldQuit())
    {
        GameManager::Update();
    }

    GameManager::Deinitialize();
    return 0;
}