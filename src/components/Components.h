#ifndef DENGINE_COMPONENTS_H
#define DENGINE_COMPONENTS_H
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "particles/Particle.h"
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
        ParticleCPUEmitterComponent():numberOfParticles(0){
        };
        explicit ParticleCPUEmitterComponent(unsigned int _numberOfParticles)
        :numberOfParticles(_numberOfParticles)
        {
            particles.resize(_numberOfParticles);

            std::vector< float > vertices;
            vertices.push_back( 0.0f );
            vertices.push_back( 0.0f );
            vertices.push_back( 0.0f );

            vertices.push_back( 1.0f );
            vertices.push_back( 0.0f );
            vertices.push_back( 0.0f );

            vertices.push_back( 0.0f );
            vertices.push_back( 1.0f );
            vertices.push_back( 0.0f );

            vertices.push_back( 1.0f );
            vertices.push_back( 1.0f );
            vertices.push_back( 0.0f );
            vbObj = std::make_unique<VertexBuffer>(vertices.data(),  (vertices.size()-1)*sizeof(float));
        }
        unsigned int numberOfParticles;
        std::vector<Particle> particles;

        std::unique_ptr<VertexBuffer> vbObj;
        std::unique_ptr<VertexBufferLayout> vlayObj;
        std::unique_ptr<VertexArray> vaObj;
    };
    struct ParticleGPUEmitterComponent{

    };
}
#endif
