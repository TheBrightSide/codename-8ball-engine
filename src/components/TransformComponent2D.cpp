#include "./TransformComponent2D.hpp"
#include <cstdio>

void TransformComponent2D::OnCreate()
{
    this->position = Vector2 {};
    this->rotation = Vector2 {};
    this->scale = Vector2 {};
}

void TransformComponent2D::OnUpdate()
{}

void TransformComponent2D::OnDestroy()
{}