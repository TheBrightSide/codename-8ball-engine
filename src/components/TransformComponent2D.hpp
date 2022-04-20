#pragma once

#include "./Component.hpp"
#include "../util/la.hpp"

class TransformComponent2D : public Component
{
public:
    DEFINE_COMPONENT(TransformComponent2D);

    void OnCreate() override {};
    void OnDestroy() override {};
    void OnUpdate() override {};

    Vec2f position;
    Vec2f rotation;
    Vec2f scale;
protected:
    bool wantsUpdate = true;
};