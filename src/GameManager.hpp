#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <raylib/raylib.h>
#include <raylib/rlgl.h>

#include "config.h"
#include "imgui/imgui.h"
#include "imgui/rlImGui.h"

#include "DrawableManager.hpp"
#include "Sprite.hpp"

class Scene
{
public:
    Scene() {};
    virtual ~Scene() = default;

    virtual void Initialize() {};
};

class GameManager
{
private:
    struct GameState
    {
        bool scene_update;
        bool should_quit;
        bool audio_uninitialized;
        float master_volume;
        Scene scene;
    } state;

    static GameManager* instance;

    void ReinitializeScene();

protected:
    GameManager() : state { false, false, false, 1.f, {} } {};
    ~GameManager() = default;

public:
    // disallow cloning singleton
    GameManager(GameManager &other) = delete;

    // disallow assignments to singleton
    void operator=(const GameManager &) = delete;

    static GameManager* GetInstance();

    /**
     * @brief Initializes the program
     * 
     * @note Meant to be used in main.cpp
     */
    void Initialize();

    /**
     * @brief Deinitializes the program
     * 
     * @note Meant to be used in main.cpp
     */
    void Deinitialize();

    /**
     * @brief Steps or updates the program
     * 
     * @note Meant to be used in main.cpp
     */
    void Update();

    /**
     * @brief Similar to the WindowShouldClose() function in raylib.h
     * 
     * @note Meant to be used in main.cpp
     * 
     * @return bool
     */
    bool ShouldQuit();

    /**
     * @brief An API function, which triggers a boolean telling the program it should quit;
     * 
     * @attention Meant to be used at any point in the code (unlike functions like initialize and deinitialize)
     */
    void Quit();

    /**
     * @brief An API function, which changes the current scene
     * 
     * @param scene This describes the current scene
     * 
     * @note Meant to be used at any point in the code
     */
    void ChangeScene(Scene scene); 

    /**
     * @brief An API function, which turns audio on or off
     */
    void ToggleAudio();

    /**
     * @brief An API function which checks the game manager's last stored master volume and tells if the audio is on or not
     * 
     * @return bool
     */
    bool IsAudioOn();
};