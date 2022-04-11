#ifndef DENGINE_PARTICLESYSTEM_H
#define DENGINE_PARTICLESYSTEM_H
#include "ecs/System.h"
namespace  DEngine {
    class ParticleSystem : public System{

    public:
        ParticleSystem(){
        }
        void init();
        void update(float dt);
    private:
    };
}
#endif