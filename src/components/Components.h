#ifndef DENGINE_COMPONENTS_H
#define DENGINE_COMPONENTS_H
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/VertexArray.h"

namespace  DEngine {
    struct TransformComponent {
        glm::mat4 transform;
        TransformComponent()=default;
        TransformComponent(const TransformComponent&) =default;
        TransformComponent(const glm::mat4& _transform):transform(_transform){
        }
        ~TransformComponent()=default;
    };

    struct GravityComponent{
        glm::vec3 gravityForce;
        GravityComponent()=default;
        GravityComponent(const GravityComponent&) =default;
        GravityComponent(const glm::vec3& _gravityForce):gravityForce(_gravityForce){
        }
        ~GravityComponent()=default;
    };

    struct RigidBodyComponent{
        glm::vec3 velocity;
        glm::vec3 acceleration;
    };

    struct MeshComponent {
        float x, y;
    };

    struct ParticleCPUEmitterComponent {
        ParticleCPUEmitterComponent()=default;
        ParticleCPUEmitterComponent(const ParticleCPUEmitterComponent&) =default;

        glm::vec3 velocity;
        glm::vec4 colorBegin;
        glm::vec4 colorEnd;

        float size;
        float lifeTime;
    };
    struct ParticleGPUEmitterComponent{

    };
}
#endif
