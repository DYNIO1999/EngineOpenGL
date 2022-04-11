#ifndef DENGINE_COMPONENTCONTAINER_H
#define DENGINE_COMPONENTCONTAINER_H

#include <memory>
#include <unordered_map>
#include "ComponentArray.h"
namespace DEngine {
    class ComponentContainer {
    private:
        std::unordered_map<const char *, ComponentType> ComponentTypes{};
        std::unordered_map<const char *, std::shared_ptr<IComponentArray>> ComponentArrays{};
        ComponentType NextComponentType{};

        template<typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray() {
            const char *typeName = typeid(T).name();
            assert(ComponentTypes.find(typeName) != ComponentTypes.end() && "Component not registered before use.");
            return std::static_pointer_cast<ComponentArray<T>>(ComponentArrays[typeName]);
        }

    public:
        template<typename T>
        void registerComponent() {
            const char *typeName = typeid(T).name();
            assert(ComponentTypes.find(typeName) == ComponentTypes.end() &&
                   "Registering component type more than once.");
            ComponentTypes.insert({typeName, NextComponentType});
            ComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
            NextComponentType++;
        }

        template<typename T>
        ComponentType getComponentType() {
            const char *typeName = typeid(T).name();
            assert(ComponentTypes.find(typeName) != ComponentTypes.end() && "Component not registered before use.");
            return ComponentTypes[typeName];
        }

        template<typename T>
        void addComponent(Entity _entity, T _component) {
            getComponentArray<T>()->insertData(_entity, _component);
        }

        template<typename T>
        T &getComponent(Entity _entity) {
            return getComponentArray<T>()->getData(_entity);
        }

        template<typename T>
        bool hasComponent(Entity _entity) {
            return getComponentArray<T>()->hasData(_entity);
        }

        void entityDestroyed(Entity _entity) {
            for (auto const &pair: ComponentArrays) {
                auto const &comp = pair.second;
                comp->entityDestroyed(_entity);
            }
        }

        template<typename T>
        void removeComponent(Entity _entity) {
            getComponentArray<T>()->removeData(_entity);
        }
    };
}
#endif
