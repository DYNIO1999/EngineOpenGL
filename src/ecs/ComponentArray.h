#ifndef DENGINE_COMPONENTARRAY_H
#define DENGINE_COMPONENTARRAY_H
#include <array>
#include <unordered_map>
#include <cassert>

#include <iostream>

#include "Entity.h"
#include "Component.h"

class IComponentArray
{
public:
    virtual void entityDestroyed(Entity _entity) = 0;
    virtual ~IComponentArray() = default;
};
template <typename T>
class ComponentArray : public IComponentArray
{
private:
    std::array<T, MAX_ENTITIES> componentsArray;
    std::unordered_map<Entity, size_t> EntityToIndexMap;
    std::unordered_map<size_t, Entity> IndexToEntityMap;
    size_t size;

public:
    ComponentArray() : size(0)
    {
    }
    void insertData(Entity _entity, T _component)
    {
        assert(EntityToIndexMap.find(_entity) == EntityToIndexMap.end() && "Component added to same entity more than once.");
        size_t index = size;
        EntityToIndexMap[_entity] = index;
        IndexToEntityMap[index] = _entity;
        componentsArray[index] = _component;
        size++;
    }
    void removeData(Entity _entity)
    {
        assert(EntityToIndexMap.find(_entity) != EntityToIndexMap.end() && "Removing non-existent component.");
        size_t indexRemovedEntity = EntityToIndexMap[_entity];
        size_t indexLastElement = size - 1;

        Entity entityLastElement = IndexToEntityMap[indexLastElement];
        EntityToIndexMap[entityLastElement] = indexRemovedEntity;
        IndexToEntityMap[indexRemovedEntity] = entityLastElement;
        EntityToIndexMap.erase(_entity);
        IndexToEntityMap.erase(indexLastElement);
        size--;
    }
    void entityDestroyed(Entity _entity) override
    {
        if (EntityToIndexMap.find(_entity) != EntityToIndexMap.end())
        {
            removeData(_entity);
        }
    }
    T &getData(Entity _entity)
    {
        assert(EntityToIndexMap.find(_entity) != EntityToIndexMap.end() && "Retriving non-existent component.");
        return componentsArray[EntityToIndexMap[_entity]];
    }
    bool hasData(Entity _entity)
    {
        if(EntityToIndexMap.find(_entity) == EntityToIndexMap.end()){
            std::cout << "ENDNDNDNNDND" << '\n';
            return false;
        }
        return true;
    }
};
#endif
