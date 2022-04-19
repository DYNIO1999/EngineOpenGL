#ifndef DENGINE_EMITTER_H
#define DENGINE_EMITTER_H
#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "core/Types.h"
#include "renderer/Shader.h"

namespace DEngine {


    struct ParticleProps{
        glm::vec4 color;
        float size;
        float lifeTime = 1.0f;
        glm::vec3 velocity;
        uint workGroups;
    };
    enum class EmitterType: uint{
        PointEmitter,
        RainEmitter,
        SnowEmitter,
        SmokeEmitter,
        FogEmitter,
    };

    class Emitter {
    public:
        Emitter(){

        }
        virtual ~Emitter() {

        }
        glm::ivec3 numberOfParticles;
        uint totalParticles;
        uint particlesVao;
        std::vector<float> initialPositions;
        std::vector<float> initialVelocities;
        virtual void init(const ParticleProps& _particleProps) =0;
        virtual void update(Shader& _computeShader) =0;
        virtual void emit(const ParticleProps& _particleProps)=0;
        virtual void emit(Shader& _particleShader,const glm::mat4& _mvp) =0;
    protected:
    };
}
#endif
