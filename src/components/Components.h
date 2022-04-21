#ifndef DENGINE_COMPONENTS_H
#define DENGINE_COMPONENTS_H
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/VertexArray.h"

#include "renderer/Mesh.h"
#include "renderer/Texture.h"
#include "particles/Emitter.h"

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
        std::vector<Mesh> mesh;
        std::vector<std::shared_ptr<Mesh>> meshes;
        std::vector<std::shared_ptr<Texture>> textures;
    };

    struct ParticleComponent {
        ParticleComponent()=default;
        ParticleComponent(const ParticleComponent&) =default;
        ParticleProps particleProps;
        std::shared_ptr<Texture> texture;
        std::shared_ptr<Emitter> emitter;
        std::shared_ptr<Shader> computeShader;
        std::shared_ptr<Shader> particleShader;
    };
}
#endif
