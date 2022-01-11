#pragma once

#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.hpp"
#include "math/math.hpp"

class Renderer;

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader {
    private:
        std::string m_FilePath;
        unsigned int m_RendererID;
        std::unordered_map<std::string, int> m_UniformLocationCache;

    public:
        Shader(const std::string& filename);
        ~Shader();

        void bind() const;
        void unbind() const;

        // Set uniforms
        void setUniform(const std::string& name, int value);
        void setUniform(const std::string& name, float v0, float v1, float v2, float v3);
        void setUniform(const std::string& name, float v0);
        void setUniform(const std::string& name, const glm::mat4& matrix);
        void setUniform(const std::string& name, const glm::vec3& vector);
    
    private:
        ShaderProgramSource parseShader();
        unsigned int compileShader(const std::string& source, unsigned int type);
        unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
        int getUniformLocation(const std::string& name);
};