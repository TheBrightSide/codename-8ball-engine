#include "./graphics.hpp"
#include "../GameManager.hpp"

// suggestion: maybe this library could open more than one window in the future??

SDL_Window *winHandle = nullptr;
SDL_Renderer *winRenderer = nullptr;

bool Graphics::InitWindow(
    Vec2f winDimensions, const char* title,
    SDL_WindowFlags winFlags, SDL_RendererFlags rendFlags)
{
    if (winFlags == 0)
        winFlags = static_cast<SDL_WindowFlags>(SDL_WINDOW_SHOWN);

    if (rendFlags == 0)
        rendFlags = static_cast<SDL_RendererFlags>(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    
    if (winHandle != nullptr)
    {
        printf("WARN: Window has already been initialized\n");
        return false;
    }

    if (SDL_WasInit(SDL_INIT_VIDEO) == 0)
    {
        printf("WARN: SDL probably wasn't initialized properly!\n");
        SDL_Init(SDL_INIT_VIDEO);
    }

    SDL_DisplayMode dm;

    // get information about the first screen
    SDL_GetCurrentDisplayMode(0, &dm);

    Vec2f winPos {
        dm.w / 2 - winDimensions.x / 2,
        dm.h / 2 - winDimensions.y / 2
    };

    bool success = false;
    
    winHandle = SDL_CreateWindow(
        title, winPos.x, winPos.y,
        winDimensions.x, winDimensions.y,
        winFlags);
    

    if (winHandle == nullptr)
    {
        printf("ERROR: Could not create window: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        printf("INFO: Successfully initalized window!\n");
        printf("INFO: Window Dimensions: %.0f, %.0f\n", winDimensions.x, winDimensions.y);
        printf("INFO: Screen Dimensions: %d, %d\n", dm.w, dm.h);
        success = true;
    }

    winRenderer = SDL_CreateRenderer(winHandle, -1, rendFlags);
    
    if (winRenderer == nullptr)
    {
        printf("ERROR: Could not create a renderer: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        printf("INFO: Successfully initialized renderer!\n");
        success = true;

        SDL_RendererInfo rendInfo{};
        if(SDL_GetRendererInfo(winRenderer, &rendInfo) != 0)
            printf("WARN: Could not get information about the renderer: %s\n", SDL_GetError());
        else
        {
            printf("INFO: Renderer Name: %s\n", rendInfo.name);
            printf("INFO: Max texture height: %d\n", rendInfo.max_texture_height);
            printf("INFO: Max texture width: %d\n", rendInfo.max_texture_width);
        }
    }

    return success;
}

bool Graphics::CloseWindow()
{
    if (winHandle == nullptr)
    {
        printf("WARN: Tried to destroy a window that was not opened\n");
        return false;
    }
    else
    {
        SDL_DestroyWindow(winHandle);
        
        printf("INFO: Successfully closed window!\n");
        winHandle = nullptr;
        winRenderer = nullptr;
        return true;
    }
}

void Graphics::BeginDrawing()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch(e.type)
        {
        case SDL_QUIT:
            GameManager::GetInstance()->Quit();
        }
    }

    SDL_RenderClear(winRenderer);
}

void Graphics::EndDrawing()
{
    SDL_RenderPresent(winRenderer);
}

void Graphics::SetWindowPosition(Vec2f pos)
{
    if (winHandle == nullptr)
    {
        printf("ERROR: No main window initalized to change its position\n");
        return;
    }

    SDL_SetWindowPosition(winHandle, (int)pos.x, (int)pos.y);
}

void Texture::LoadTexture(const char *path)
{
    if (winHandle == nullptr || winRenderer == nullptr)
    {
        printf("ERROR: Cannot create texture without a renderer");
    }
    
    SDL_Texture *texture = IMG_LoadTexture(winRenderer, path);

    if (texture == nullptr)
    {
        printf("FATAL: Couldn't load image \"%s\"", path);
        printf("FATAL: Error message: %s", SDL_GetError());
        exit(1);
    }

    this->texture = texture;
}

void Texture::UnloadTexture()
{
    if (this->texture != nullptr)
    {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}

void Texture::DrawTexture()
{
    if (this->texture != nullptr)
    {
        SDL_RenderCopy(winRenderer, this->texture, 
            &Source, &Destination);
    }
}

Vec2i Texture::GetSize()
{
    Vec2i out{};
    if (this->texture != nullptr)
        SDL_QueryTexture(this->texture, NULL, NULL, &out.x, &out.y);
    
    return out;
}

Texture::~Texture()
{
    this->UnloadTexture();
}