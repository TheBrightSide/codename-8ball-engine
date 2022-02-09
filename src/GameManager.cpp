#include "GameManager.hpp"

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new GameManager();
    }

    return instance;
}

void GameManager::ReinitializeScene()
{
    // Destroy any leftover drawables to prevent memory leaking
    DrawableManager::GetInstance()->DestroyAllDrawables();

    DrawableManager::GetInstance()->InstantiateDrawable<Sprite>("unnamed.png", Vector2{}, 1.f, 0.f);

    // Creates all the drawables in the newly initialized scene
    DrawableManager::GetInstance()->CreateAll();
}

void GameManager::Initialize()
{
    // Initializes the windows, audio, physics and icon
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    InitAudioDevice();

    // Sets the exit key to 0 so the windows closes when the quit button is pressed
    SetExitKey(0);

    // Checks if the audio devices work properly
    if (!IsAudioDeviceReady())
    {
        std::cout << "INFO: Audio device wasn't initialized properly" << std::endl;
        state.audio_uninitialized = true;
    }
    else state.audio_uninitialized = false;

    // Sets the targetfps to 60
    SetTargetFPS(60);

    // If the audio device initialized successfully,
    // Set the master volume to max possible
    if (!state.audio_uninitialized)
        SetMasterVolume(state.master_volume);

    ReinitializeScene();
}

void GameManager::ChangeScene(Scene scene)
{
    // Changes scene to wanted scene and sets the bool to true
    state.scene = scene;
    state.scene_update = true;
}

void GameManager::Quit()
{
    // Sets the bool to true
    std::cout << "INFO: GameManager: Triggered should_quit boolean" << std::endl;
    state.should_quit = true;
}

void GameManager::Update()
{
    // If a scene has recently been changes initialize it
    if (state.scene_update)
    {
        ReinitializeScene();
        state.scene_update = false;
        std::cout << "INFO: GameManager: Scene Update!" << std::endl;
    }
    
    BeginDrawing();
        ClearBackground(BLACK);

        // Draws and updates all drawables
        DrawableManager::GetInstance()->UpdateAll();
        DrawableManager::GetInstance()->DrawAll();

        // Draws FPS
        DrawText(std::to_string(GetFPS()).c_str(), 0, WINDOW_HEIGHT - 20, 20, GREEN);
    EndDrawing();
}

void GameManager::Deinitialize()
{
    // Destroy any leftover drawables to prevent memory leaking
    DrawableManager::GetInstance()->DestroyAllDrawables();

    // Close audio and the windows when the scene is deinitialized
    CloseAudioDevice();
    CloseWindow();

    std::cout << "INFO: Goodbye!" << std::endl;
}

bool GameManager::ShouldQuit()
{
    // Returns if the window should quit
    return state.should_quit || WindowShouldClose();
}

void GameManager::ToggleAudio()
{
    // If the audio isn't initialized - initialize it
    if (!state.audio_uninitialized)
    {
        if (state.master_volume > 0.0f)
        {
            state.master_volume = 0.0f;
            SetMasterVolume(state.master_volume);
        }
        else
        {
            state.master_volume = 1.0f;
            SetMasterVolume(state.master_volume);
        }
    }
}

bool GameManager::IsAudioOn()
{
    // Returns if the audio is initialized
    if (state.audio_uninitialized) return false;
    else
    {
        if (state.master_volume > 0.0f) return true;
        else return false;
    }
}