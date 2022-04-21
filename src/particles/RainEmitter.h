#ifndef DENGINE_RAINEMITTER_H
#define DENGINE_RAINEMITTER_H
#include "Emitter.h"
#include "components/Components.h"

namespace DEngine {
    class RainEmitter: public Emitter{
    public:
        RainEmitter(glm::ivec3 _numberOfParticles)
        {
            numberOfParticles= _numberOfParticles;
        }
        ~RainEmitter(){

        }
        void init(const ParticleProps& _particleProps) override;
        void update(Shader& _computeShader) override;
        void update(Shader &_computeShader, float dt) override;
        void emit(const ParticleProps& _particleProps) override;
        void emit(Shader& _particleShader, const glm::mat4& _mvp) override;
    private:
        ParticleProps particleProps;

    };
}
#endif
