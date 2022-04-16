#include "Mesh.h"
#include "core/LogManager.h"
namespace DEngine{

    void Mesh::initMesh(){
        vertexBufferObj =  std::make_shared<VertexBuffer>(vertices.data(), vertices.size() *sizeof(VertexData), vertices.size());
        vertexBufferLayoutObj =  std::make_shared<VertexBufferLayout>();
        vertexBufferLayoutObj->push<float>(3);  // position
        vertexBufferLayoutObj->push<float>(3);  // normals
        vertexBufferLayoutObj->push<float>(3);  // colors
        vertexBufferLayoutObj->push<float>(2);  // texture cordinates
        if(!indices.empty()){
            indexBufferObj = std::make_shared<IndexBuffer>(indices.data(), indices.size());
        }
        vertexArrayObj = std::make_shared<VertexArray>();
        vertexArrayObj->addBuffer(*vertexBufferObj, *vertexBufferLayoutObj);
    }
}