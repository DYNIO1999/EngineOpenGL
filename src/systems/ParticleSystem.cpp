#include "ParticleSystem.h"
#include "core/Engine.h"
#include "core/LogManager.h"
#include "components/Components.h"

#include <core/Random.h>
#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace  DEngine {

    uint ParticleSystem::ParticleEmittersCounter =0;

    void ParticleSystem::init() {
        for(auto const& entity:entities){
            auto& particleComponent = Engine::entitySystemManager.getComponent<ParticleComponent>(entity);
            particleComponent.emitter->init(particleComponent.particleProps);
        }
    }
    void ParticleSystem::update(float dt, const glm::mat4 _mvp) {

        for(auto const& entity:entities){
            auto& particleComponent = Engine::entitySystemManager.getComponent<ParticleComponent>(entity);
            particleComponent.emitter->update(*particleComponent.computeShader);
            particleComponent.emitter->emit(*particleComponent.particleShader,_mvp);
        }
    }
}