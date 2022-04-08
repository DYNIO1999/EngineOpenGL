#ifndef DENGINE_ENTITYCONTAINER_H
#define DENGINE_ENTITYCONTAINER_H
#include <array>
#include <cassert>
#include <queue>
#include "Entity.h"
#include "Component.h"
class EntityContainer
{
private:
    std::queue<Entity> availableEntities{};
    std::array<ComponentsSignature, MAX_ENTITIES> signatures{};
    std::uint32_t aliveEntityCount{};

public:
    EntityContainer()
    {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        {
            availableEntities.push(entity);
        }
    }
    ~EntityContainer()
    {
    }
    Entity createEntity()
    {
        assert(aliveEntityCount < MAX_ENTITIES && "Too many entities in existence.");
        Entity id = availableEntities.front();
        availableEntities.pop();
        aliveEntityCount++;
        return id;
    }

    void destroyEntity(Entity _entity)
    {
        assert(_entity < MAX_ENTITIES && "Entity out of range.");
        signatures[_entity].reset();
        availableEntities.push(_entity);
        aliveEntityCount--;
    }
    void setSignature(Entity _entity, ComponentsSignature _signature)
    {
        assert(_entity < MAX_ENTITIES && "Entity out of range.");
        signatures[_entity] = _signature;
    }
    ComponentsSignature getSignature(Entity _entity)
    {
        assert(_entity < MAX_ENTITIES && "Entity out of range.");
        return signatures[_entity];
    }
};
#endif
