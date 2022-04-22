#ifndef DENGINE_MODEL_H
#define DENGINE_MODEL_H
#include <nlohmann/json.hpp>

#include "core/LogManager.h"
#include "core/Helpers.h"
#include "core/Types.h"


#include "Mesh.h"
#include "Texture.h"

namespace  DEngine {
    using json = nlohmann::json;
    class Model {
    public:
        Model(const std::string& _pathFile):pathFile(_pathFile){
            std::string text = DEngine::readFile(_pathFile);

            DENGINE_INFO("{}",text);
            json_file = json::parse(text);
            pathFile = _pathFile;
            data = getData();
            traverseNode(0);
        }


        std::vector<Mesh> meshes;
        std::vector<glm::vec3> translationsMeshes;
        std::vector<glm::quat> rotationsMeshes;
        std::vector<glm::vec3> scalesMeshes;
        std::vector<glm::mat4> matricesMeshes;

        std::vector<std::string> loadedTextureNames;
        std::vector<Texture> textures;

    private:

        std::vector<uint> getIndices(json _accessor);
        std::vector<float> getFloats(json _accessor);
        void loadMesh(uint _meshIndex);
        void traverseNode(uint _nextNode, glm::mat4  _matrix = glm::mat4(1));

        std::vector<uchar> getData();
        std::string pathFile;
        std::vector<uchar> data;
        json json_file;
    };
}
#endif

