#ifndef DENGINE_VERTEXBUFFERLAYOUT_H
#define DENGINE_VERTEXBUFFERLAYOUT_H
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace DEngine{

    struct VertexBufferElement
    {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        static unsigned int getSizeType(unsigned int _type){
            switch (_type)
            {
                case GL_FLOAT: return 4;
                case GL_UNSIGNED_INT: return 4;
                case GL_UNSIGNED_BYTE: return 1;
            }
            return 0;
        }

    };

    class VertexBufferLayout{
    public:
        VertexBufferLayout():stride(0){

        }
        ~VertexBufferLayout(){
            elements.clear();
        }
        template<typename T>
        void push(unsigned int count);
        template <>
        void push<float>(unsigned int count)
        {

            elements.push_back({GL_FLOAT, count, GL_FALSE});
            stride += count * VertexBufferElement::getSizeType(GL_FLOAT);
        }
        template <>
        void push<unsigned int>(unsigned int count)
        {
            elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
            stride += count * VertexBufferElement::getSizeType(GL_UNSIGNED_INT);
        }
        template <>
        void push<unsigned char>(unsigned int count)
        {
            elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
            stride += count * VertexBufferElement::getSizeType(GL_UNSIGNED_BYTE);
        }
        const std::vector<VertexBufferElement> &getElements() const { return elements; }

        unsigned int getStride() const { return stride; }

    private:

        std::vector<VertexBufferElement> elements;
        unsigned int stride;
    };

}
#endif