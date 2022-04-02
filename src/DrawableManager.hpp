#pragma once

#include <raylib/raylib.h>
#include <iostream>
#include <memory>
#include <list>

class Drawable
{
private:
    static long current_id;
    long id;

    /**
     * @brief Sets the sprites' IDs. 
     */
    
public:
    Drawable();
    virtual ~Drawable();

    virtual void Create() {}; // Gets called once whenever the program is initializing itself
    virtual void Update() {}; // Gets called once per frame
    virtual void Draw() {}; // Gets called once per frame (after Update)

    int GetID()
    {
        return id;

        /**
         * @brief Gets the IDs of the sprites.
         * 
         * @returns int id
         */
    }
};

class DrawableManager {
private:
    std::list<std::shared_ptr<Drawable>> drawable_pool;
    int current_id;

    static DrawableManager* instance;

protected:
    DrawableManager() : drawable_pool(), current_id(0) {};
    ~DrawableManager() = default;

public:
    // disallow cloning singleton
    DrawableManager(DrawableManager &other) = delete;

    // disallow assignments to singleton
    void operator=(const DrawableManager &) = delete;

    static DrawableManager* GetInstance();

    /**
     * @brief Creates a drawable based on a certain type that derives the class Drawable
     */
    template <typename DrawableType, typename... DrawableArgs>
    std::weak_ptr<DrawableType> InstantiateDrawable(DrawableArgs&&... args)
    {
        std::shared_ptr<DrawableType> current = std::make_shared<DrawableType>(args...);
        drawable_pool.push_back(current);
        return current;
    }

    /**
     * @brief Calls the Create() function for every Drawable in the drawable_pool
     */
    void CreateAll();

    /**
     * @brief Calls the Update() function for every Drawable in the drawable_pool
     */
    void UpdateAll(); 

    /**
     * @brief Calls the Draw() function for every Drawable in the drawable_pool
     */
    void DrawAll();

    /**
     * @brief Destroys every Drawable in the drawable_pool and clears drawable_pool
     */
    void DestroyAllDrawables();

    /**
     * @brief Iterates through drawable_pool and destroys the Drawable corresponding to the ID
     * 
     * @param id This describes the sprite's id
     */
    void DestroyDrawableFromID(int id);

    /**
     * @brief Get the Drawable From ID object
     * 
     * Iterates through drawable_pool and gets the Drawable corresponding to the ID (returns nullptr if ID is non-existent)
     * 
     * @param id This describes the sprite's id
     * 
     * @return std::weak_ptr<Drawable>
     */
    std::weak_ptr<Drawable> GetDrawableFromID(int id);
};