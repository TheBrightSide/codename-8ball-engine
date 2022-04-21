#include "SpriteComponent.hpp"

void SpriteComponent::OnCreate()
{
    texture = ObjectManager::GetInstance()->CreateObject<Texture>();
    texture.lock()->LoadTexture(SpriteImagePath.c_str());
    Vec2i res = texture.lock()->GetSize();
    texture.lock()->Source = { 0, 0, res.x, res.y };
    texture.lock()->Destination = { 0, 0, res.x, res.y };
}

void SpriteComponent::OnUpdate()
{
    std::shared_ptr<TransformComponent2D> transformComponent;
    if (!GetComponent("TransformComponent2D").expired())
    {
        transformComponent =
            std::static_pointer_cast<TransformComponent2D>(GetComponent("TransformComponent2D").lock());
        
        texture.lock()->Destination.x = transformComponent->Position.x;
        texture.lock()->Destination.y = transformComponent->Position.y;
    }

    if (!(this->texture.expired()))
        this->texture.lock()->DrawTexture();
}

void SpriteComponent::OnDestroy()
{
    if (!(this->texture.expired()))
        ObjectManager::GetInstance()->DestroyObjectFromID(texture.lock()->GetID());
}

Vec2i SpriteComponent::GetSpriteSize()
{
    if (!(this->texture.expired()))
        return Vec2i { texture.lock()->Source.w, texture.lock()->Source.h };
    else return Vec2i {};
}