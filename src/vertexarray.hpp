#pragma once

#include "vertexbuffer.hpp"

class VertexBufferLayout;

class VertexArray {
    public:
        VertexArray();
        ~VertexArray();
    
        void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

        void bind();
        void unbind();

    private:
        unsigned int m_RendererID;
};