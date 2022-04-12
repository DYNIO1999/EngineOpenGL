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
    void ParticleSystem::init(int _start) {
        for(auto const& entity: entities) {
            auto const &transform = Engine::entitySystemManager.getComponent<TransformComponent>(entity);
            auto const &emitter = Engine::entitySystemManager.getComponent<ParticleCPUEmitterComponent>(entity);
            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;
            glm::vec3 skew;
            glm::vec4 perspective;
            glm::decompose(transform.transform, scale, rotation, translation, skew, perspective);

            for(int i = 0;i<_start;i++){

                Particle& particle = particles[particleIndex];
                particle.position = translation;
                particle.rotationDegrees = Random::generateRandom<float>() * 2 * glm::pi<float>();
                particle.velocity = emitter.velocity;
                particle.velocity.x += 1* (Random::generateRandom<float>() - 0.5f);
                particle.velocity.y +=  -2 * (Random::generateRandom<float>() - 0.5f);
                particle.velocity.z +=  3* (Random::generateRandom<float>() - 0.5f);

                particle.colorBegin = emitter.colorBegin;
                particle.colorEnd = emitter.colorEnd;
                particle.lifeTime = emitter.lifeTime;
                particle.lifeRemaining =  emitter.lifeTime;
                particle.size  = emitter.size;
                particle.active = true;
                particleIndex = --particleIndex % particles.size();
            }
        }

    }
    void ParticleSystem::update(float dt) {
        for (auto const &entity: entities) {
            for (auto &particle: particles) {
                if (!particle.active) {
                    continue;
                }
                if (particle.lifeRemaining <= 0.0f) {
                    particle.active = false;
                }
                particle.lifeRemaining -= dt;
                particle.position += particle.velocity * dt;
                particle.rotationDegrees += 0.1f * dt;

            }
        }
    }
    void ParticleSystem::draw() {


            for (auto &particle: particles) {
                if (!particle.active) {
                    continue;
                }
                float life = particle.lifeRemaining / particle.lifeRemaining;
                glm::vec4 color = glm::lerp(particle.colorEnd, particle.colorBegin, life);
                float size = glm::lerp(particle.size, particle.size, life);
                glm::mat4 transform =
                        glm::translate(glm::mat4(1.0f), {particle.position.x, particle.position.y, particle.position.z})
                        * glm::rotate(glm::mat4(1.0f), particle.rotationDegrees, {0.0f, 0.0f, 1.0f})
                        * glm::scale(glm::mat4(1.0f), {size, size, 1.0f});

            }
        }
}