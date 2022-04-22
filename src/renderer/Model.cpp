#include "Model.h"
namespace  DEngine {

    static std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec)
    {
        std::vector<glm::vec2> vectors;
        for (int i = 0; i < floatVec.size(); i)
        {
            vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
        }
        return vectors;
    }
    static std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec)
    {
        std::vector<glm::vec3> vectors;
        for (int i = 0; i < floatVec.size(); i)
        {
            vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
        }
        return vectors;
    }
    static std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec)
    {
        std::vector<glm::vec4> vectors;
        for (int i = 0; i < floatVec.size(); i)
        {
            vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
        }
        return vectors;
    }
    static std::vector<VertexData> assembleVertices
            (
                    std::vector<glm::vec3> _positions,
                    std::vector<glm::vec3> _normals,
                    std::vector<glm::vec2> _textureCordinates
            )
    {
        std::vector<VertexData> vertices;
        for (int i = 0; i < _positions.size(); i++)
        {
            vertices.push_back(VertexData{ _positions[i], _normals[i], glm::vec3(1.0f, 1.0f, 1.0f), _textureCordinates[i]});
        }
        return vertices;
    }


    std::vector<uint> Model::getIndices(json _accessor)
    {
        std::vector<uint> indices;

        uint buffViewInd = _accessor.value("bufferView", 0);
        uint count = _accessor["count"];
        uint accByteOffset = _accessor.value("byteOffset", 0);
        uint componentType = _accessor["componentType"];

        json bufferView = json_file["bufferViews"][buffViewInd];
        uint byteOffset = bufferView["byteOffset"];

        uint beginningOfData = byteOffset + accByteOffset;
        if (componentType == 5125)
        {
            for (uint i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i)
            {
                uchar bytes[] = { data[i++], data[i++], data[i++], data[i++] };
                uint value;
                std::memcpy(&value, bytes, sizeof(uint));
                indices.push_back(value);
            }
        }
        else if (componentType == 5123)
        {
            for (uint i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
            {
                uchar bytes[] = { data[i++], data[i++] };
                unsigned short value;
                std::memcpy(&value, bytes, sizeof(unsigned short));
                indices.push_back((uint)value);
            }
        }
        else if (componentType == 5122)
        {
            for (uint i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
            {
                uchar bytes[] = { data[i++], data[i++] };
                short value;
                std::memcpy(&value, bytes, sizeof(short));
                indices.push_back((uint)value);
            }
        }

        return indices;
    }

    std::vector<float> Model::getFloats(json _accessor)
    {
        std::vector<float> floatVec;

        uint buffViewInd = _accessor.value("bufferView", 1);
        uint count = _accessor["count"];
        uint accByteOffset = _accessor.value("byteOffset", 0);
        std::string type = _accessor["type"];

        json bufferView = json_file["bufferViews"][buffViewInd];
        uint byteOffset = bufferView["byteOffset"];

        uint numPerVert;
        if (type == "SCALAR") numPerVert = 1;
        else if (type == "VEC2") numPerVert = 2;
        else if (type == "VEC3") numPerVert = 3;
        else if (type == "VEC4") numPerVert = 4;
        else throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3, or VEC4)");

        uint beginningOfData = byteOffset + accByteOffset;
        uint lengthOfData = count * 4 * numPerVert;
        for (uint i = beginningOfData; i < beginningOfData + lengthOfData; i)
        {
            uchar bytes[] = { data[i++], data[i++], data[i++], data[i++] };
            float value;
            std::memcpy(&value, bytes, sizeof(float));
            floatVec.push_back(value);
        }

        return floatVec;
    }

    std::vector<uchar> Model::getData() {
        std::string bytesText;
        std::string uri = json_file["buffers"][0]["uri"];
        std::string fileDirectory = pathFile.substr(0,pathFile.find_last_of('/')+1);
        bytesText = DEngine::readFile(fileDirectory+uri);
        std::vector<uchar> tempData(bytesText.begin(), bytesText.end());
        return tempData;
    }

    void Model::loadMesh(uint _meshIndex) {
        uint positionAccessorsIndex = json_file["meshes"][_meshIndex]["primitives"][0]["attributes"]["POSITION"];
        uint normalAccessorsIndex = json_file["meshes"][_meshIndex]["primitives"][0]["attributes"]["NORMAL"];
        uint textureAccessorsIndex = json_file["meshes"][_meshIndex]["primitives"][0]["attributes"]["TEXCOORD_0"];
        uint indicesAccessorsIndex = json_file["meshes"][_meshIndex]["primitives"][0]["indices"];

        std::vector<float> posVec = getFloats(json_file["accessors"][positionAccessorsIndex]);
        std::vector<glm::vec3> positions = DEngine::groupFloatsVec3(posVec);
        std::vector<float> normalVec = getFloats(json_file["accessors"][normalAccessorsIndex]);
        std::vector<glm::vec3> normals = DEngine::groupFloatsVec3(normalVec);
        std::vector<float> texVec = getFloats(json_file["accessors"][textureAccessorsIndex]);
        std::vector<glm::vec2> texUVs = DEngine::groupFloatsVec2(texVec);

        std::vector<VertexData> vertices = assembleVertices(positions, normals, texUVs);
        std::vector<uint> indices = getIndices(json_file["accessors"][indicesAccessorsIndex]);
        //std::vector<Texture> textures = getTextures();
        meshes.emplace_back(Mesh(vertices,indices));
    }

    void Model::traverseNode(uint _nextNode, glm::mat4 _matrix) {

        json currentNode = json_file["nodes"][_nextNode];

        glm::vec3 translationVector(0);
        if(currentNode.find("translation")!=currentNode.end()){
                float temp[3];
                for(uint i =0; i < currentNode["translation"].size(); i++){
                    temp[i] = (currentNode["translation"][i]);
                }
                translationVector = glm::vec3(temp[0],temp[1], temp[2]);
        }

        glm::quat rotationQuaternion = glm::quat(1.0f, 0.0f, 0.0f ,0.0f);
        if(currentNode.find("rotation")!=currentNode.end()){
            rotationQuaternion = glm::quat{currentNode["rotation"][3],
                                           currentNode["rotation"][0],
                                           currentNode["rotation"][1],
                                           currentNode["rotation"][2]};
        }

        glm::vec3 scaleVector(1);
        if(currentNode.find("scale")!=currentNode.end()){
            float temp[3];
            for(uint i =0; i < currentNode["scale"].size(); i++){
                temp[i] = (currentNode["scale"][i]);
            }
            scaleVector = glm::vec3(temp[0],temp[1], temp[2]);
        }


        glm::mat4 transformCurrentNode(1.0f);
        if(currentNode.find("matrix")!=currentNode.end()){
            float temp[16];
            for(uint i =0; i < currentNode["matrix"].size(); i++) {
                temp[i] = (currentNode["matrix"][i]);
            }
            transformCurrentNode = glm::make_mat4(temp);
        }

        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 rot = glm::mat4(1.0f);
        glm::mat4 sca = glm::mat4(1.0f);

        trans = glm::translate(trans, translationVector);
        rot = glm::mat4_cast(rotationQuaternion);
        sca = glm::scale(sca, scaleVector);


        glm::mat4 transformMatrixNextNode = _matrix * transformCurrentNode * trans * rot * sca;

        if (currentNode.find("mesh") != currentNode.end()){
            DENGINE_INFO("TRAVERSE!!!");
            translationsMeshes.push_back(translationVector);
            rotationsMeshes.push_back(rotationQuaternion);
            scalesMeshes.push_back(scaleVector);
            matricesMeshes.push_back(transformMatrixNextNode);
            loadMesh(currentNode["mesh"]);
        }
        if (currentNode.find("children") != currentNode.end())
        {
            for (uint i = 0; i < currentNode["children"].size(); i++) {
                traverseNode(currentNode["children"][i], transformMatrixNextNode);
            }
        }

    }
}