#ifndef DENGINE_PHYSICSSYSTEM_H
#define DENGINE_PHYSICSSYSTEM_H
#include "ecs/EntitySystemManager.h"
#include "ecs/System.h"
namespace DEngine {
    class PhysicsSystem : public System {
    public:
        PhysicsSystem() =default;
        void init();
        void update(float dt);
    private:

    };
}
#endif
