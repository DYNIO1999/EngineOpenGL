#ifndef DENGINE_POINTEMITTER_H
#define DENGINE_POINTEMITTER_H
#include "Emitter.h"
#include "components/Components.h"

namespace DEngine {
    class PointEmitter: public Emitter{
    public:
        PointEmitter(glm::ivec3 _numberOfParticles)
        {
            numberOfParticles= _numberOfParticles;
        }
        ~PointEmitter(){

        }
        void init() override;
        void setProperties(const ParticleProps &_particleProps) override;
        void update(Shader &_computeShader, float dt) override;
        void emit(Shader &_particleShader, const glm::mat4 &_projection, const glm::mat4 &_model, const glm::mat4 &_view) override;

    private:
        ParticleProps particleProps;

    };
}
#endif
