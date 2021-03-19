#include "vertexarray.hpp"
#include "renderer.hpp"
#include "vertexbufferlayout.hpp"

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    bind();
    vb.bind();
    const auto& elements = layout.getElements();
    for (int i=0; i<elements.size(); i++) {
        const auto& element = elements[i];
        GLCall(glVertexAttribPointer(i, element.count, element.type, 
                                    element.normalized, layout.getStride(), (const void*)element.offset));
        GLCall(glEnableVertexAttribArray(i));
    } 
}

void VertexArray::bind() {
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::unbind() {
    GLCall(glBindVertexArray(0));
}