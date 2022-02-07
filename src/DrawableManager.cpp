#include "DrawableManager.hpp"

DrawableManager* DrawableManager::instance = nullptr;
long Drawable::current_id = 0;

Drawable::Drawable()
{
    id = current_id;
    ++current_id;

    // Sets the id of the current sprite as the currentId variable and then moves on to the next sprite

    std::cout << "INFO: DrawableManager: Created Drawable with ID: " << id << std::endl;
}

Drawable::~Drawable()
{
    std::cout << "INFO: DrawableManager: Destroyed Drawable with ID: " << id << std::endl;
}

DrawableManager* DrawableManager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new DrawableManager();
    }

    return instance;
}

void DrawableManager::CreateAll()
{
    for (auto& drawable : drawable_pool)
    {
        drawable->Create();
    }

    // Calls the Create() function for every drawable in the drawable_pool
}

void DrawableManager::UpdateAll()
{
    for (auto& drawable : drawable_pool)
    {
        drawable->Update();
    }

    // Calls the Update() function for every drawable in the drawable_pool
}

void DrawableManager::DrawAll()
{
    for (auto& drawable : drawable_pool)
    {
        drawable->Draw();
    }

    // Calls the Draw() function for every drawable in the drawable_pool
}

void DrawableManager::DestroyAllDrawables()
{
    for (auto& drawable : drawable_pool)
    {
        drawable.reset();
    }

    // Deletes every drawable in the drawable_pool and then clears it and sets the currentId variable to 0

    drawable_pool.clear();
}

void DrawableManager::DestroyDrawableFromID(int id)
{
    for (auto drawable = drawable_pool.begin(); drawable != drawable_pool.end(); ++drawable)
    {
        // Makes a pointer of the current drawable in the drawable_pool
        std::shared_ptr<Drawable> drawable_ptr = *drawable;

        // Checks if the drawable pointer has the id we want to destroy
        // If it is it erases it and deletes it
        if (drawable_ptr->GetID() == id)
        {
            drawable_ptr.reset();
            drawable_pool.erase(drawable);
            break;
        }
    }

    // Deletes a drawable by getting the specific id of a sprite
}

std::weak_ptr<Drawable> DrawableManager::GetDrawableFromID(int id)
{
    for (auto& drawable : drawable_pool)
    {
        // Checks every drawable in the drawable_pool
        if (drawable->GetID() == id)
        {
            // Checks if the drawable from the for loop has the id we want to destroy
            // If it is we return it

            return drawable;
        }
    }

    // If it isn't we return null
    return std::weak_ptr<Drawable>();

    // Returns a drawable by getting the specific id of a sprite
}