#ifndef DENGINE_PHYSICSSYSTEM_H
#define DENGINE_PHYSICSSYSTEM_H
#include "ecs/EntitySystemManager.h"
#include "ecs/System.h"
namespace DEngine {
    class PhysicsSystem : public System {
    public:
        PhysicsSystem(EntitySystemManager& _entitySystemManager)
        :entitySystemManager(_entitySystemManager){

        }
        void init();
        void update(float dt);
    private:
        EntitySystemManager& entitySystemManager;
    };
}
#endif
