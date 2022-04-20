#pragma once
#include <SDL2/SDL.h>
#include <cstdio>
#include <cassert>
#include <memory>
#include "./la.hpp"

bool InitWindow(Vec2f winDimensions, const char* title, SDL_WindowFlags winFlags, SDL_RendererFlags rendFlags);
bool CloseWindow();

void BeginDrawing();
void EndDrawing();

void SetWindowPosition(int x, int y);

void LoadTexture();