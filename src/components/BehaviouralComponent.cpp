#include "./BehaviouralComponent.hpp"

void BehaviouralComponent::OnUpdate()
{
    auto transformComponent = MGetComponent(TransformComponent2D);
    auto spriteComponent = MGetComponent(SpriteComponent);

    Vec2i mouseDelta = Input::GetMouseDelta();
    Vec2i mousePos = Input::GetMousePos();
    Vec2i spritePos = { (int)transformComponent->Position.x, (int)transformComponent->Position.y };
    Vec2i spriteSize = spriteComponent->GetSpriteSize();
    Recti spriteRect = { spritePos.x, spritePos.y, spriteSize.x + spritePos.x, spriteSize.y + spritePos.y };

    if (SDL_PointInRect(&mousePos, &spriteRect) && Input::IsMouseButtonDown(SDL_BUTTON_LEFT))
    {
        transformComponent->Position.x += mouseDelta.x;
        transformComponent->Position.y += mouseDelta.y;
    }
}