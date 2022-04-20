#pragma once

#include "./Component.hpp"
#include "TransformComponent2D.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>

class SpriteComponent : public Component
{
public:
    DEFINE_COMPONENT(SpriteComponent);

    void OnCreate() override;
    void OnDestroy() override;
    void OnUpdate() override;

    std::string SpriteImagePath;

protected:
    bool wantsUpdate = true;
    SDL_Texture* texture = nullptr;
};