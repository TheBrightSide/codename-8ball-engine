#include "ObjectManager.hpp"
#include "./Entity.hpp"
#include "./components/Component.hpp"

uint64_t ObjectManager::currentId = 0;
ObjectManager* ObjectManager::instance = nullptr;

bool ObjectManager::CheckBaseName(std::weak_ptr<Object> object, const char* name)
{
    assert(!object.expired() && "Passed an expired object in CheckBaseName");
    assert(object.lock()->ObjectBaseName() && "Passed an empty object with no BaseName");
    assert(name && "Passed nullptr on second argument name");

    if (strcmp(object.lock()->ObjectBaseName(), name) == 0)
        return true;
    return false;
}

void ObjectManager::CleanUnusedComponents()
{
    for (auto object : objectTable)
    {
        if (CheckBaseName(object.second, "Component"))
        {
            // if (!(static_cast<Component*>(&(*object.second))->IsUsed))
            if (!(std::static_pointer_cast<Component>(object.second)->IsUsed))
                objectTable.erase(object.first);
        }
    }
}

ObjectManager* ObjectManager::GetInstance()
{
    if (instance == nullptr)
        instance = new ObjectManager();

    return instance;
}

void ObjectManager::DestroyAllEntities()
{
    for (auto object : objectTable)
    {
        if (CheckBaseName(object.second, "Entity"))
        {
            // static_cast<Entity*>(&(*object.second))->OnEntityDestroy();
            std::static_pointer_cast<Entity>(object.second)->OnEntityDestroy();
            objectTable.erase(object.first);
        }
    }
}

void ObjectManager::DestroyEntityFromID(uint64_t id)
{
    if (objectTable.find(id) != objectTable.end())
    {
        if (CheckBaseName(objectTable[id], "Entity"))
        {
            // static_cast<Entity*>(&(*objectTable[id]))->OnEntityDestroy();
            std::static_pointer_cast<Entity>(objectTable[id])->OnEntityDestroy();
            objectTable.erase(id);
        }
    }
}

void ObjectManager::DestroyAllObjects()
{
    objectTable.clear();
}

void ObjectManager::DestroyObjectFromID(int id)
{
    objectTable.erase(id);
}

std::weak_ptr<Object> ObjectManager::GetObjectFromID(int id)
{
    if (objectTable.find(id) != objectTable.end())
        return objectTable[id];
    else return std::weak_ptr<Object>(); /* null */
}

void ObjectManager::TriggerCreateEvents()
{
    for (auto obj : objectTable)
    {
        if (CheckBaseName(obj.second, "Entity"))
        {
            std::static_pointer_cast<Entity>(obj.second)->OnEntityCreate();
        }
    }
}

void ObjectManager::TriggerUpdateEvents()
{
    for (auto obj : objectTable)
    {
        if (CheckBaseName(obj.second, "Entity"))
        {
            std::static_pointer_cast<Entity>(obj.second)->OnUpdateComponents();
        }
    }
}