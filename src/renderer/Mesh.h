#ifndef DENGINE_MESH_H
#define DENGINE_MESH_H
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <memory>


#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"


namespace DEngine {
    using Index = unsigned int;
    struct VertexData{
        glm::vec3 position;
        glm::vec3 normals;
        glm::vec3 color;
        glm::vec2 textureCords;        
    };
    
    class Mesh {    
        public:
        Mesh(){

        }
        Mesh(const std::vector<VertexData>& _vertices)
        :vertices(_vertices),
         materialIndex(0)
        {
            initMesh();

        }

        Mesh(const std::vector<VertexData>& _vertices, const std::vector<Index>&  _indices)
        :vertices(_vertices),
        indices(_indices),
         materialIndex(0)
        {
            initMesh();
        }
        virtual ~Mesh() =default;

        std::shared_ptr<VertexArray> getVertexArrayObj() const
        {
            return  vertexArrayObj;
        }

        std::shared_ptr<IndexBuffer> getIndexBufferObj() const
        {
            return indexBufferObj;
        }
        std::vector<VertexData> vertices;


        std::vector<Index> indices;

        void setMaterialIndex(uint _materialIndex){ materialIndex = _materialIndex;}
        uint getMaterialIndex() const { return materialIndex;}

        protected:

        void initMesh();

        uint materialIndex;
        std::shared_ptr<VertexBuffer> vertexBufferObj;
        std::shared_ptr<VertexBufferLayout> vertexBufferLayoutObj;
        std::shared_ptr<IndexBuffer> indexBufferObj;

        std::shared_ptr<VertexArray> vertexArrayObj;
    };
}
#endif
