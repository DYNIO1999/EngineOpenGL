#ifndef DENGINE_PARTICLESYSTEM_H
#define DENGINE_PARTICLESYSTEM_H
#include "ecs/System.h"
#include <glm/glm.hpp>
#include <vector>
//#include "core/Engine.h"
#include "renderer/Renderer.h"

namespace  DEngine {
    class ParticleSystem : public System{
    public:
        ParticleSystem(){
        }
        ~ParticleSystem(){
            
        }
        void init();
        void update(float dt, const glm::mat4 &_projection, const glm::mat4 &_view,const glm::mat4 &_model);
        static uint ParticleEmittersCounter;
    private:
        double time;
    };
}
#endif