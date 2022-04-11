#ifndef DENGINE_PHYSICSSYSTEM_H
#define DENGINE_PHYSICSSYSTEM_H
#include "ecs/System.h"
namespace DEngine {
    class PhysicsSystem : public System {
    public:
        void init();
        void update(float dt);
    private:
    };
}
#endif
