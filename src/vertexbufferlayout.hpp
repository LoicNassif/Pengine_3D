#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.hpp"

struct  VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    unsigned int offset;

    static unsigned int getSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return sizeof(float);
            case GL_UNSIGNED_INT: return sizeof(unsigned int);
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};

template<typename T>
struct identity { typedef T type; };

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

    template<typename TL>
    void push(unsigned int count, unsigned int offset, identity<TL>) {
        // static_assert(false);
    }

    void push(unsigned int count, unsigned int offset, identity<float>)
    {
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE, offset});
        m_Stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
    }

    void push(unsigned int count, unsigned int offset, identity<unsigned int>)
    {
        m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE, offset});
        m_Stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
    }

    void push(unsigned int count, unsigned int offset, identity<unsigned char>)
    {
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE, offset});
        m_Stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
    }

public:
    VertexBufferLayout() : m_Stride(0) {}
    
    template<typename TL>
    void push(unsigned int count, unsigned int offset) {
        push(count, offset, identity<TL>());
    }

    inline const std::vector<VertexBufferElement>& getElements() const { return m_Elements; }
    inline unsigned int getStride() const { return m_Stride; }
};