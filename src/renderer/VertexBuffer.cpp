#include "VertexBuffer.h"
#include "glad/glad.h"

namespace DEngine{
    template <typename T>
    VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
        glGenBuffers(1, &vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, (size*sizeof(T)), data,GL_STATIC_DRAW);
    }
    template <typename T>
    VertexBuffer::VertexBuffer(const void *data, unsigned int size, VertexUsageTypes type) {
        glGenBuffers(1, &vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
        switch (type) {
            case VertexUsageTypes::DYNAMIC_DRAW:
                glBufferData(GL_ARRAY_BUFFER, (size*sizeof(T)), data,GL_DYNAMIC_DRAW);
                break;
            case VertexUsageTypes::STATIC_DRAW:
                glBufferData(GL_ARRAY_BUFFER, (size*sizeof(T)), data,GL_STATIC_DRAW);
                break;
            case VertexUsageTypes::STREAM_DRAW:
                glBufferData(GL_ARRAY_BUFFER, (size*sizeof(T)), data,GL_STREAM_DRAW);
                break;
        }
    }
    VertexBuffer::~VertexBuffer() {
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }
    void VertexBuffer::bind() {
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    }
    void VertexBuffer::unbind() {
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }
}