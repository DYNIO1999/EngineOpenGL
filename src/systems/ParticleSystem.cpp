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
            particleComponent.emitter->init();
        }
    }
    void ParticleSystem::update(float dt, const glm::mat4 &_projection, const glm::mat4 &_view){
        for(auto const& entity:entities){
            auto& particleComponent = Engine::entitySystemManager.getComponent<ParticleComponent>(entity);
            auto& transformComponent = Engine::entitySystemManager.getComponent<TransformComponent>(entity);
            auto& particlePropertiesComponent = Engine::entitySystemManager.getComponent<ParticlePropertiesComponent>(entity);

            particleComponent.emitter->setProperties(particlePropertiesComponent.particleProps);
            particleComponent.emitter->update(*particleComponent.computeShader,dt);
            if(particleComponent.texture) {
                particleComponent.texture->bind();
                particleComponent.emitter->emit(*particleComponent.particleShader, _projection, _view, transformComponent.transform);
                particleComponent.texture->unbind();
            }else{
                particleComponent.emitter->emit(*particleComponent.particleShader, _projection, _view, transformComponent.transform);
            }
        }
    }
    void ParticleSystem::update(float dt, const glm::mat4 &_projection, const glm::mat4 &_view, const std::string& tag){
        for(auto const& entity:entities){

            auto& particleComponent = Engine::entitySystemManager.getComponent<ParticleComponent>(entity);
            auto& tagComponent = Engine::entitySystemManager.getComponent<TagComponent>(entity);
            auto& transformComponent = Engine::entitySystemManager.getComponent<TransformComponent>(entity);
            auto& particlePropertiesComponent = Engine::entitySystemManager.getComponent<ParticlePropertiesComponent>(entity);

            if(tagComponent.tag == tag) {
                particleComponent.emitter->setProperties(particlePropertiesComponent.particleProps);
                particleComponent.emitter->update(*particleComponent.computeShader, dt);
                if (particleComponent.texture) {
                    particleComponent.texture->bind();
                    particleComponent.emitter->emit(*particleComponent.particleShader, _projection, _view, transformComponent.transform);
                    particleComponent.texture->unbind();
                } else {
                    particleComponent.emitter->emit(*particleComponent.particleShader, _projection, _view, transformComponent.transform);
                }
            }
        }
    }
}