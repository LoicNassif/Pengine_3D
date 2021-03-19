#pragma once

#include "scene.hpp"

#include <memory>

namespace scene {
    class BasicScene : public Scene {
    public:
        BasicScene(GLFWwindow *context);
        ~BasicScene();

        void onUpdate(float deltaTime, bool cursorEnabled) override;
        void onRender() override;
        void onImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture0;
        std::unique_ptr<Renderer> m_Renderer;

        float m_OffsetValuex;
        float m_OffsetValuey;
        float m_OffsetValuez;

        float m_CurrentFrame = 0;

        glm::vec3 m_CubePositions[10];
        glm::mat4 m_Proj, m_View, m_Model, m_MVP;

        GLFWwindow *m_Window;
    };
}