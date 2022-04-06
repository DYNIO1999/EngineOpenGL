#ifndef DENGINE_VERTEXBUFFER_H
#define DENGINE_VERTEXBUFFER_H
namespace DEngine {
    enum class VertexUsageTypes: int{
        STREAM_DRAW,
        STATIC_DRAW,
        DYNAMIC_DRAW
    };

    class VertexBuffer {

        public:
        VertexBuffer(const void* data, unsigned int size, VertexUsageTypes type,unsigned  int _vertexCount);
        VertexBuffer(const void* data, unsigned int size, unsigned  int _vertexCount);
        VertexBuffer(const void *data, unsigned int size, VertexUsageTypes type);
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();
        unsigned int getVertexCount()const {return vertexCount;}
        void bind();
        void unbind();

        private:
        unsigned int vertexBufferID;
        unsigned int vertexCount;
    };
}
#endif