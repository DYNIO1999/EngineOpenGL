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
        template <typename T>
        VertexBuffer(const void* data, unsigned int size,VertexUsageTypes type);
        template <typename T>
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void bind();
        void unbind();

        private:
        unsigned int vertexBufferID;
    };
}
#endif