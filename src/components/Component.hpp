#pragma once

#include <memory>
#include <cassert>

#include "../ObjectManager.hpp"

class Component : public Object
{
public:
    DEFINE_OBJECT(Component);

    virtual ~Component() = default;
    virtual const char* ComponentName() { return nullptr; }

    bool Active = true;
    bool IsUsed = false;

    virtual void OnCreate() {}
    virtual void OnDestroy() {}
    virtual void OnUpdate() {}

    inline bool WantsUpdate() { return wantsUpdate; }
    void BindToEntity(std::weak_ptr<Object> object)
    {
        assert(!object.expired() && "Passed an expired pointer");
        assert(ObjectManager::CheckBaseName(object, "Entity") && "The passed object was not an Entity");
        IsUsed = true;
        boundEntity = object;
    }

    void BindObject(uint64_t id)
    {
        auto object = ObjectManager::GetInstance()->GetObjectFromID(id);
        BindToEntity(object);
    }

protected:
    std::weak_ptr<Object> boundEntity;
    bool wantsUpdate = false;
};

#define DEFINE_COMPONENT(TYPE) \
    TYPE(uint64_t id) : Component(id) {}; \
    const char* ComponentName() override { return #TYPE; };

#define DEFINE_DERIVED_COMPONENT(TYPE, BASETYPE) \
    TYPE(uint64_t) : BASETYPE(id) {}; \
    const char* ComponentName() override { return #TYPE; };