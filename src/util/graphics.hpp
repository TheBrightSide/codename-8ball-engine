#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <cassert>
#include <memory>
#include "../ObjectManager.hpp"
#include "./la.hpp"

class Texture : public Object
{
public:
    DEFINE_OBJECT(Texture)

    virtual ~Texture();

    void LoadTexture(const char *path);
    void UnloadTexture();

    void DrawTexture();
    Vec2i GetSize();
    Recti Source;
    Recti Destination;

private:
    SDL_Texture* texture = nullptr;
};

namespace Graphics
{
    bool InitWindow(Vec2f winDimensions, const char* title, SDL_WindowFlags winFlags, SDL_RendererFlags rendFlags);
    bool CloseWindow();

    void BeginDrawing();
    void EndDrawing();

    void SetWindowPosition(Vec2f);
};