#ifndef DENGINE_VERTEXARRAY_H
#define DENGINE_VERTEXARRAY_H
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
namespace  DEngine {
    class VertexArray {
    public:
        VertexArray();

        ~VertexArray();

        void addBuffer(VertexBuffer& vb, VertexBufferLayout& layout);

        void bind();

        void unBind();

        unsigned int getVertexCount()const {return vertexCount;}

    private:
        unsigned int vertexArrayID;
        unsigned int vertexCount;
    };
}
#endif