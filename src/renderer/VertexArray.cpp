#include "VertexArray.h"


namespace DEngine{

    VertexArray::VertexArray() {
        glGenVertexArrays(1,&vertexArrayID);
    }
    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1,&vertexArrayID);
    }

    void VertexArray::bind() {

    }

    void VertexArray::unBind() {

    }

    void VertexArray::addBuffer(VertexBuffer& vb, VertexBufferLayout& layout) {
        bind();
        vb.bind();
        vertexCount = vb.getVertexCount();
        const auto& elements = layout.getElements();
        unsigned int offset =0;
        for(unsigned int i=0;i< elements.size();i++){
            const auto& element  = elements[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i,static_cast<GLint>(element.count),element.type,element.normalized,static_cast<GLint>(layout.getStride()),(const void*)offset);
            offset +=element.count * VertexBufferElement::getSizeType(element.type);
        }
    }
}