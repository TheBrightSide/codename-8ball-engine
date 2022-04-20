#include "GameManager.hpp"
#include "ECSManager.hpp"

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
    ObjectManager::GetInstance()->DestroyAllEntities();

    auto entity = ECSManager::CreateEntity();
    auto transformComponent = ECSManager::CreateComponent<TransformComponent2D>();
    entity.lock()->BindComponent(transformComponent);

    ObjectManager::GetInstance()->TriggerCreateEvents();
}

void GameManager::Initialize()
{
    // Initializes the windows, audio, physics and icon
    if(!InitWindow(Vec2f{ WINDOW_WIDTH, WINDOW_HEIGHT }, WINDOW_TITLE, 0, 0))
        exit(1);
    
    // InitAudioDevice();

    // // Checks if the audio devices work properly
    // if (!IsAudioDeviceReady())
    // {
    //     std::cout << "INFO: Audio device wasn't initialized properly" << std::endl;
    //     state.audio_uninitialized = true;
    // }
    // else state.audio_uninitialized = false;

    // If the audio device initialized successfully,
    // Set the master volume to max possible
    // if (!state.audio_uninitialized)
        // SetMasterVolume(state.master_volume);

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
    // Draws and updates all drawables
    ObjectManager::GetInstance()->TriggerUpdateEvents();

    EndDrawing();
}

void GameManager::Deinitialize()
{
    // Destroy any leftover drawables to prevent memory leaking
    ObjectManager::GetInstance()->DestroyAllEntities();

    // Close audio and the windows when the scene is deinitialized
    // CloseAudioDevice();
    CloseWindow();

    std::cout << "INFO: Goodbye!" << std::endl;
}

bool GameManager::ShouldQuit()
{
    // Returns if the window should quit
    return state.should_quit /* || WindowShouldClose() */;
}

void GameManager::ToggleAudio()
{}

bool GameManager::IsAudioOn()
{}