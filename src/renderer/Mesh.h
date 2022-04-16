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
        Mesh(const std::vector<VertexData>& _vertices)
        :vertices(_vertices)
        {
            initMesh();

        }

        Mesh(const std::vector<VertexData>& _vertices, const std::vector<Index>&  _indices)
        :vertices(_vertices),
        indices(_indices)
        {
            initMesh();
        }
        ~Mesh() =default;

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
        private:

        void initMesh();

        std::shared_ptr<VertexBuffer> vertexBufferObj;
        std::shared_ptr<VertexBufferLayout> vertexBufferLayoutObj;
        std::shared_ptr<IndexBuffer> indexBufferObj;

        std::shared_ptr<VertexArray> vertexArrayObj;
    };
}
#endif
