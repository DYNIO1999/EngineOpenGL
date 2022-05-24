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
        Model(const std::string& _pathFile, bool _withTexture=false):pathFile(_pathFile), withTexture(_withTexture){
            loadModel(pathFile);
        }
        ~Model(){
            //materials.clear();
            meshes.clear();
            textures.clear();
        }
        //std::vector<Material> materials;
        std::vector<Mesh> meshes;
        std::vector<std::shared_ptr<Texture>> textures;

    private:
        void loadModel(const std::string& path);
        void parseNodeData(aiNode *node, const aiScene *scene);
        void parseMeshData(aiMesh* mesh);
        void parseTextures();
        std::string directory;
        std::string pathFile;
        bool withTexture;
    };
}
#endif

