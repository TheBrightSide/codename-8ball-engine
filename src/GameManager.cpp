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

    auto entity = ECS::CreateEntity();
    auto transformComponent = ECS::CreateComponent<TransformComponent2D>();
    auto spriteComponent = ECS::CreateComponent<SpriteComponent>();
    spriteComponent.lock()->SpriteImagePath = "unnamed.png";
    entity.lock()->BindComponent(transformComponent);
    entity.lock()->BindComponent(spriteComponent);

    ObjectManager::GetInstance()->TriggerCreateEvents();
}

void GameManager::Initialize()
{
    // Initializes the windows
    if(!Graphics::InitWindow(Vec2f{ WINDOW_WIDTH, WINDOW_HEIGHT }, WINDOW_TITLE, 0, 0))
        exit(1);

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

    Graphics::BeginDrawing();
    // Draws and updates all drawables
    ObjectManager::GetInstance()->TriggerUpdateEvents();

    Graphics::EndDrawing();
}

void GameManager::Deinitialize()
{
    // Destroy any leftover drawables to prevent memory leaking
    ObjectManager::GetInstance()->DestroyAllEntities();
    Graphics::CloseWindow();

    std::cout << "INFO: Goodbye!" << std::endl;
}

bool GameManager::ShouldQuit()
{
    // Returns if the window should quit
    return state.should_quit;
}