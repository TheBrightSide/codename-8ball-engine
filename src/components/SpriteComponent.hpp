#pragma once

#include "./Component.hpp"
#include "./TransformComponent2D.hpp"
#include "../util/graphics.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <memory>

class SpriteComponent : public Component
{
public:
    DEFINE_COMPONENT(SpriteComponent);

    void OnCreate() override;
    void OnDestroy() override;
    void OnUpdate() override;

    Vec2i GetSpriteSize();

    std::string SpriteImagePath;

protected:
    bool wantsUpdate = true;
    std::weak_ptr<Texture> texture;
};