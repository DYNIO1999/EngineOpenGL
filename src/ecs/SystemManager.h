#ifndef DENGINE_SYSTEMMANAGER_H
#define DENGINE_SYSTEMMANAGER_H
#include <memory>
#include <unordered_map>
#include <assert.h>

#include "System.h"
#include "Component.h"

namespace DEngine{
    class SystemManager {
    public:
        template<typename T>
        std::shared_ptr<T> registerSystem(){
            const char* typeName = typeid(T).name();
            assert(systems.find(typeName) == systems.end() && "Registering system more than once!");
            auto system = std::make_shared<T>();
            systems.insert({typeName,system});
            return system;
        }
        template<typename T>
        std::shared_ptr<T> getSystem(){
            const char* typeName = typeid(T).name();
            assert(systems.find(typeName) != systems.end() && "System not found!");
            auto system = systems.find(typeName)->second;
            return system;
        }

        template<typename T>
        void setSignature(ComponentsSignature _signature){
            const char* typeName = typeid(T).name();

            assert(systems.find(typeName) != systems.end() && "System used before registered.");
            signatures.insert({typeName, _signature});
        }

        void entityDestroyed(Entity _entity){
            for(auto const& pair : systems ){
                auto const& system = pair.second;
                system->entities.erase(_entity);
            }
        }

        void entitySignatureChanged(Entity _entity, ComponentsSignature _entitySignature)
        {
            for (auto const& pair : systems)
            {
                auto const& type = pair.first;
                auto const& system = pair.second;
                auto const& systemSignature = signatures[type];

                if ((_entitySignature & systemSignature) == systemSignature)
                {
                    system->entities.insert(_entity);
                }
                else
                {
                    system->entities.erase(_entity);
                }
            }
        }
    private:
        std::unordered_map<const char*, ComponentsSignature> signatures{};
        std::unordered_map<const char*, std::shared_ptr<System>> systems{};
    };
}
#endif