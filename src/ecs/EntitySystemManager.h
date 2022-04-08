#ifndef DENGINE_ENTITYSYSTEMMANAGER_H
#define DENGINE_ENTITYSYSTEMMANAGER_H
#include <memory>
#include "EntityContainer.h"
#include "ComponentContainer.h"

class EntitySystemManager {
private:
    std::unique_ptr<ComponentContainer> componentContainer;
    std::unique_ptr<EntityContainer> entityContainer;

public:
    EntitySystemManager() :
            componentContainer(std::make_unique <ComponentContainer>()),
            entityContainer(std::make_unique<EntityContainer>())
    {

    }
    Entity createEntity(){
        return entityContainer->createEntity();
    }
    void destroyEntity(Entity _entity){
        entityContainer->destroyEntity(_entity);
        componentContainer->entityDestroyed(_entity);
    }
    template <typename T>
    void registerComponent(){
        componentContainer->registerComponent<T>();
    }
    template <typename T>
    void addComponent(Entity _entity, T _component){
        componentContainer->addComponent<T>(_entity, _component);

        auto signature = entityContainer->getSignature(_entity);
        signature.set(componentContainer->getComponentType<T>(), true);
        entityContainer->setSignature(_entity, signature);
    }
    template <typename T>
    void removeComponent(Entity _entity){
        componentContainer->removeComponent<T>(_entity);
        auto signature = entityContainer->getSignature(_entity);
        signature.set(componentContainer->getComponentType<T>(), false);
        entityContainer->setSignature(_entity,signature);
    }
    template <typename T>
    T& getComponent(Entity _entity){
        return componentContainer->getComponent<T>(_entity);
    }
    template <typename T>
    ComponentType getComponentType()
    {
        return componentContainer->getComponentType<T>();
    }
    template <typename T>
    bool hasComponent(Entity _entity){
        return componentContainer->hasComponent<T>(_entity);
    }
};
#endif