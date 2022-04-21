#include "./Component.hpp"
#include "./TransformComponent2D.hpp"
#include "./SpriteComponent.hpp"
#include "../util/graphics.hpp"
#include <string>

class BehaviouralComponent : public Component
{
public:
    DEFINE_COMPONENT(BehaviouralComponent)

    void OnCreate() override {};
    void OnDestroy() override {};
    void OnUpdate() override;
};