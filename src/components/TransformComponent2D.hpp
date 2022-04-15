#pragma once

#include "./Component.hpp"
#include "../RenderBackend.hpp"

class TransformComponent2D : public Component
{
public:
    DEFINE_COMPONENT(TransformComponent2D);

    void OnCreate() override;
    void OnDestroy() override;
    void OnUpdate() override;

    Vector2 position;
    Vector2 rotation;
    Vector2 scale;
protected:
    bool wantsUpdate = true;
};