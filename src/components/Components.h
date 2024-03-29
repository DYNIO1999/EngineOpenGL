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
    struct TagComponent{
        std::string tag;
        TagComponent() = default;
        TagComponent(const TagComponent &) = default;
        TagComponent(const std::string &_tag) : tag(_tag)
        {
        }
        ~TagComponent() = default;
    };

    struct TransformComponent {
        glm::mat4 transform;
        glm::vec3 position;
        glm::vec3 rotarion;
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

    struct BoxCollider{
        std::shared_ptr<Mesh> debugCube;
        glm::vec3 center;
        glm::vec3 extents;
        BoxCollider()=default;
        BoxCollider(const BoxCollider&) =default;
        BoxCollider(const glm::vec3& _center, const glm::vec3& _extents ):center(_center), extents(_extents){
        }

        ~BoxCollider()=default;
    };
    struct MeshComponent {
        std::vector<Mesh> mesh;
        std::vector<Mesh> meshes;
        std::vector<std::shared_ptr<Texture>> textures;
    };
    
    struct ParticleComponent {
        ParticleComponent()=default;
        ParticleComponent(const ParticleComponent&) =default;
        std::shared_ptr<Texture> texture;
        std::shared_ptr<Emitter> emitter;
        std::shared_ptr<Shader> computeShader;
        std::shared_ptr<Shader> particleShader;
    };
    struct ParticlePropertiesComponent{
        ParticlePropertiesComponent() = default;
        ParticlePropertiesComponent(const ParticlePropertiesComponent&) =default;
        ParticleProps particleProps;
    };
}
#endif
