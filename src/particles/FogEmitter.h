#ifndef DENGINE_FOGEMITTER_H
#define DENGINE_FOGEMITTER_H

#include "Emitter.h"
#include "components/Components.h"
namespace DEngine {
    class FogEmitter: public Emitter{
    public:
        FogEmitter(int _numberOfParticles)
        {
            numberOfParticles.x=_numberOfParticles;
        }
        ~FogEmitter(){

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
