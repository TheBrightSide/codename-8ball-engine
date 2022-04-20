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

    Vec2f Position;
    Vec2f Rotation;
    Vec2f Scale;
protected:
    bool wantsUpdate = true;
};