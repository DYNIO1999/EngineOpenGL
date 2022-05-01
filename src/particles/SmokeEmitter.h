#ifndef DENGINE_SMOKEEMITTER_H
#define DENGINE_SMOKEEMITTER_H
#include "Emitter.h"
#include "components/Components.h"
namespace DEngine {
    class SmokeEmitter: public Emitter{
    public:
        SmokeEmitter(int _numberOfParticles)
        {
            numberOfParticles.x=_numberOfParticles;
        }
        ~SmokeEmitter(){

        }

        void init() override;
        void setProperties(const ParticleProps &_particleProps) override;
        void update(Shader &_computeShader, float dt) override;
        void emit(Shader &_particleShader, const glm::mat4 &_projection, const glm::mat4 &_view,const glm::mat4 &_model);
    private:
        ParticleProps particleProps;
    };
}
#endif
