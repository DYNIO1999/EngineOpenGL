#ifndef DENGINE_MATERIAL_H
#define DENGINE_MATERIAL_H
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>

namespace  DEngine {
    class Material {
    public:
        Material() = default;
        ~Material() = default;
        Material(const Material &) = default;
        Material(glm::vec3 _albedo, float _metalic,  float _roughness,  float _ambientOclusion):
        albedo(_albedo), metalic(_metalic), roughness(_roughness), ambientOclusion(_ambientOclusion)
        {

        }

        float roughness  =1.0f;
        float metalic = 0.0f;
        float ambientOclusion = 1.0f;
        glm::vec3 albedo = glm::vec3(0.6f);

        Texture AmbientOclusionMap;
        Texture NormalMap;
        Texture AlbedoMap;
        Texture MetallicMap;
        Texture RoughnessMap;

        void SetUniforms(Shader& _shader){
            _shader.bind();
            _shader.setUniform1f("material.ambientOclusion", ambientOclusion);
            _shader.setUniformVec3f("material.albedo", albedo);
            _shader.setUniform1f("material.metalic", metalic);
            _shader.setUniform1f("material.roughness", roughness);
            AmbientOclusionMap.bind(0);
            AlbedoMap.bind(1);
            NormalMap.bind(2);
            MetallicMap.bind(3);
            RoughnessMap.bind(4);

            AmbientOclusionMap.unbind();
            AlbedoMap.unbind();
            NormalMap.unbind();
            MetallicMap.unbind();
            RoughnessMap.unbind();
        }
    private:
    };
}
#endif
