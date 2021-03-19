#pragma once

#include "scene.hpp"

namespace scene1
{
    class basicScene : public scene::Scene
    {
    public:
        basicScene(GLFWwindow *context);
        ~basicScene();

        void onUpdate(float deltaTime, bool cursorEnabled) override;
        void onRender() override;
        void onImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture0;
        std::unique_ptr<Texture> m_Texture1;
        std::unique_ptr<Texture> m_TextureSpecular0;
        std::unique_ptr<Renderer> m_Renderer;

        bool m_AnimateFlag = true;
        bool m_FlashlightFlag = true;
        bool m_PointLightFlag = true;
        bool m_DirectionalLightFlag = true;

        double prev_time = glfwGetTime();

        glm::vec3 m_CubePositions[10];

        scene::Material m_CurrentMaterial = scene::Material();
        scene::SpotLight m_SpotLight = scene::SpotLight();

        float m_CurrentFrame = 0;

        glm::mat4 m_Proj, m_View, m_Model, m_MVP;

        GLFWwindow *m_Window;

        glm::vec3 m_PointLightAmbient = glm::vec3(0.05f, 0.05f, 0.05f);
        glm::vec3 m_PointLightDiffuse = glm::vec3(0.6f, 0.6f, 0.6f);
        glm::vec3 m_PointLightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);

        float m_PointLightConstant = 1.0f;
        float m_PointLightLinear = 0.09f;
        float m_PointLightQuadratic = 0.032f;

        glm::vec3 m_PointLightPositions[4] = {
            glm::vec3(0.7f, 0.2f, 2.0f),
            glm::vec3(2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f, 2.0f, -12.0f),
            glm::vec3(0.0f, 0.0f, -3.0f)};
    };
} // namespace scene1