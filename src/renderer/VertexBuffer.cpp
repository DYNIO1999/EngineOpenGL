#include "VertexBuffer.h"
#include "Renderer.h"

namespace DEngine{
    VertexBuffer::VertexBuffer(const void* data, unsigned int size, VertexUsageTypes type,unsigned  int _vertexCount){
        glGenBuffers(1, &vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
        switch (type) {
            case VertexUsageTypes::DYNAMIC_DRAW:
                glBufferData(GL_ARRAY_BUFFER, size , data, GL_DYNAMIC_DRAW);
                break;
            case VertexUsageTypes::STATIC_DRAW:
                glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW);
                break;
            case VertexUsageTypes::STREAM_DRAW:
                glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);
                break;
        }
        vertexCount = _vertexCount;
    }
    VertexBuffer::VertexBuffer(const void *data, unsigned int size, unsigned int _vertexCount) {
        glGenBuffers(1, &vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, size,data,GL_STATIC_DRAW);
        vertexCount = _vertexCount;

    }
    VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
        glGenBuffers(1, &vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, size,data,GL_STATIC_DRAW);
        vertexCount = 0;
    }

    VertexBuffer::VertexBuffer(const void *data, unsigned int size, VertexUsageTypes type) {
        glGenBuffers(1, &vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
        switch (type) {
            case VertexUsageTypes::DYNAMIC_DRAW:
                glBufferData(GL_ARRAY_BUFFER, size , data, GL_DYNAMIC_DRAW);
                break;
            case VertexUsageTypes::STATIC_DRAW:
                glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW);
                break;
            case VertexUsageTypes::STREAM_DRAW:
                glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);
                break;
        }
        vertexCount = 0;
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