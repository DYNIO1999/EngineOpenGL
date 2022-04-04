#ifndef DENGINE_INDEXBUFFER_H
#define DENGINE_INDEXBUFFER_H

namespace DEngine {
    class IndexBuffer {
    public:
        IndexBuffer(const unsigned int *data, unsigned int count);

        ~IndexBuffer();

        void bind() const;

        void unBind() const;

        unsigned int getCount() const { return count;};
    private:
        unsigned int indexBufferID;
        unsigned int count;
    };
}
#endif