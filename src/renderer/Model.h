#ifndef DENGINE_MODEL_H
#define DENGINE_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "core/LogManager.h"
#include "core/Helpers.h"
#include "core/Types.h"


#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

namespace  DEngine {

    class Model {
    public:
        Model(const std::string& _pathFile):pathFile(_pathFile){
            loadModel(pathFile);
        }
        std::vector<Material> materials;
        std::vector<Mesh> meshes;
        std::vector<Texture> textures;

    private:
        void loadModel(const std::string& path);
        void parseNodeData(aiNode *node, const aiScene *scene);
        void parseMeshData(aiMesh* mesh);
        void parseMaterials(aiScene* scene, const std::string& directory);
        std::string directory;
        std::string pathFile;
    };
}
#endif

