#pragma once

#include "renderer.hpp"

class Texture {
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        unsigned char* m_LocalBuffer;
        int m_Width, m_Height, m_BPP;
        unsigned int m_texturePos;
    public:
        Texture(const std::string& path, unsigned int texturePos = GL_TEXTURE0, 
                unsigned int rendererID = 0);
        ~Texture();

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;

        inline int GetWidth() const { return m_Width; }
        inline int getHeight() const { return m_Height; }
};