#ifndef DENGINE_MATERIAL_H
#define DENGINE_MATERIAL_H
#include "Texture.h"
#include <glm/glm.hpp>

namespace  DEngine {
    class Material {
    public:
        Material() = default;
        ~Material() = default;
        Material(const Material &) = default;

        float opacity = 1.0f;
        float occlusion = 0.5f;
        float roughness = 0.8f;
        float metalness = 0.1f;
        float diffuseScale = 1.0f;
        float emissiveScale = 1.0f;

        Texture diffuseMap;
        Texture heightMap;
        Texture normalMap;
        Texture opacityMap;
        Texture emissiveMap;
        Texture occlusionMap;
        Texture roughnessMap;
        Texture metalnessMap;

        glm::vec3 diffuseColor = glm::vec3(0.0f);
        glm::vec3 emissiveColor = glm::vec3(0.0f);
    private:
    };
}
#endif
