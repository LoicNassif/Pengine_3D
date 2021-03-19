#include "renderer.hpp"

bool GLLogCall(const char *function, const char *file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL ERROR]:  " << error << "\n"
                  << function << " " << file << ":" << line << "\n";
        return false;
    }
    return true;
}

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

void Renderer::clear() const {
    /* Render here */
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    // Activate the shader
    shader.bind();

    // Draw call
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, NULL));
}