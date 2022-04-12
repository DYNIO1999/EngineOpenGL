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
        struct Particle{
            glm::vec3 position;
            glm::vec3 velocity;
            glm::vec4 colorBegin, colorEnd;
            float rotationDegrees;
            float size;
            float lifeTime = 1.0f;
            float lifeRemaining = 0.0f;
            bool active;
        };
        ParticleSystem(){
            particles.resize(1000);
        }
        ~ParticleSystem(){
            
        }
        void init(int _start);
        void update(float dt);
        void draw();
    private:
        std::vector<Particle> particles;
        uint32_t particleIndex = 999;
    };
}
#endif