#include "./Component.hpp"
#include "../util/graphics.hpp"
#include "../util/imgui/imgui.h"

class UIComponent : public Component
{
public:
    DEFINE_COMPONENT(UIComponent);

    void OnUpdate() override;

    virtual void OnUI() {};
};