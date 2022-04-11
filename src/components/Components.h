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
        TransformComponent()=default;
        ~TransformComponent()=default;
        glm::mat4 transform;
    };

    struct MeshComponent {
        float x, y;
    };

    struct ParticleEmitterComponent {
        ParticleEmitterComponent():numberOfParticles(0){
        };
        explicit ParticleEmitterComponent(unsigned int _numberOfParticles)
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
}
#endif
