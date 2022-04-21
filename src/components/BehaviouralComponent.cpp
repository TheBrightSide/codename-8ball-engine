#include "./BehaviouralComponent.hpp"

void BehaviouralComponent::OnUpdate()
{
    std::shared_ptr<TransformComponent2D> transformComponent =
        std::static_pointer_cast<TransformComponent2D>(GetComponent("TransformComponent2D").lock());
    
    std::shared_ptr<SpriteComponent> spriteComponent =
        std::static_pointer_cast<SpriteComponent>(GetComponent("SpriteComponent").lock());

    Vec2i mouseDelta = Input::GetMouseDelta();
    Vec2i mousePos = Input::GetMousePos();
    Vec2i spritePos = { transformComponent->Position.x, transformComponent->Position.y };
    Vec2i spriteSize = spriteComponent->GetSpriteSize();
    Recti spriteRect = { spritePos.x, spritePos.y, spriteSize.x + spritePos.x, spriteSize.y + spritePos.y };

    if (SDL_PointInRect(&mousePos, &spriteRect) && Input::IsMouseButtonDown(SDL_BUTTON_LEFT))
    {
        transformComponent->Position.x += mouseDelta.x;
        transformComponent->Position.y += mouseDelta.y;
    }
}