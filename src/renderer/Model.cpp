#include "Model.h"
namespace  DEngine {



    static glm::vec3 toVec3(const aiVector3D& v) {
        return glm::vec3(v.x, v.y, v.z);
    }

    static glm::vec4 toVec4(const aiColor4D& c) {
        return glm::vec4(c.r, c.g, c.b, c.a);
    }

    static glm::quat toQuat(const aiQuaternion& q) {
        return glm::quat(q.w, q.x, q.y, q.z);
    }

    static glm::mat4 toMat4(const aiMatrix4x4& from) {
        glm::mat4 to;
        //the a, b, c, d in assimp is the row; the 1, 2, 3, 4 is the column
        to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
        to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
        to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
        to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
        return to;
    }

    void Model::loadModel(const std::string &path) {


        uint32_t flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace |
                         aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | aiProcess_ValidateDataStructure |
                         aiProcess_ImproveCacheLocality | aiProcess_FixInfacingNormals |
                         aiProcess_GenUVCoords | aiProcess_FlipUVs;

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path,flags);
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            DENGINE_ERROR("ERROR ASSIMP {}", importer.GetErrorString());
            return;
        }

        directory = path.substr(0, path.find_last_of('/')).append("/");

        parseNodeData(scene->mRootNode, scene);

        DENGINE_ERROR("CHECK --->{}", withTexture);
        if(withTexture) {
            parseTextures();
        }
    }

    void Model::parseNodeData(aiNode *node, const aiScene *scene) {
        for (uint32_t i = 0; i < node->mNumMeshes; i++) {
            parseMeshData(scene->mMeshes[node->mMeshes[i]]);
        }

        for (uint32_t i = 0; i < node->mNumChildren; i++) {
            parseNodeData(node->mChildren[i],scene);
        }
    }

    void Model::parseMeshData(aiMesh* mesh) {
        std::vector<VertexData> vertices;
        std::vector<unsigned int> indices;

        // vertices
        for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
            VertexData vertex;
            vertex.position = glm::vec3(0.0f,0.0f,0.0f);
            vertex.normals = glm::vec3(0.0f,0.0f,0.0f);
            vertex.color = glm::vec3(0.0f,0.0f,0.0f);
            vertex.textureCords = glm::vec2(0.0f,0.0f);

            vertex.position = toVec3(mesh->mVertices[i]);


            vertex.normals = toVec3(mesh->mNormals[i]);

            if (mesh->mTextureCoords[0]) {
                vertex.textureCords.x = mesh->mTextureCoords[0][i].x;
                vertex.textureCords.y = mesh->mTextureCoords[0][i].y;
            }
            vertices.push_back(vertex);
        }
        for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
            for (uint32_t k = 0; k < mesh->mFaces[i].mNumIndices; k++) {
                indices.push_back(mesh->mFaces[i].mIndices[k]);
            }
        }

        Mesh temp{vertices,indices};
        meshes.emplace_back(temp);
    }

    void Model::parseTextures() {
        DENGINE_WARN("PATH --> {}", directory);
        textures.emplace_back(std::make_shared<Texture>(directory+"texture.png"));
    }
}