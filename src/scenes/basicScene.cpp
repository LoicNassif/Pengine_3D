#include "basicScene.hpp"

namespace scene1
{
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    float lastX = scene::SCR_WIDTH / 2;
    float lastY = scene::SCR_HEIGHT / 2;
    bool firstMouse = true;

    bool CURSOR_ENABLED = true;

    // Frame timing values
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    void processInput(GLFWwindow *window);

    basicScene::basicScene(GLFWwindow *context)
        : m_Proj(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)),
          m_Model(glm::mat4(1.0f)), m_MVP(glm::mat4(1.0f)),
          m_Window(context)
    {
        // Position (3), Colour (3), Texture (2), Surface Normal (3)
        float positions[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
        unsigned int indices[] = {
            0, 1, 2, 3, 4, 5, 6,
            7, 8, 9, 10, 11, 12,
            13, 14, 15, 16, 17,
            18, 19, 20, 21, 22,
            23, 24, 25, 26, 27,
            28, 29, 30, 31, 32,
            33, 34, 35};

        m_CubePositions[0] = glm::vec3(0.0f, 0.0f, 0.0f);
        m_CubePositions[1] = glm::vec3(2.0f, 5.0f, -15.0f);
        m_CubePositions[2] = glm::vec3(-1.5f, -2.2f, -2.5f);
        m_CubePositions[3] = glm::vec3(-3.8f, -2.0f, -12.3f);
        m_CubePositions[4] = glm::vec3(2.4f, -0.4f, -3.5f);
        m_CubePositions[5] = glm::vec3(-1.7f, 3.0f, -7.5f);
        m_CubePositions[6] = glm::vec3(1.3f, -2.0f, -2.5f);
        m_CubePositions[7] = glm::vec3(1.5f, 2.0f, -2.5f);
        m_CubePositions[8] = glm::vec3(1.5f, 0.2f, -1.5f);
        m_CubePositions[9] = glm::vec3(-1.3f, 1.0f, -1.5f);

        m_Model = glm::rotate(m_Model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        m_Proj = glm::perspective(glm::radians(camera.Fov), 800.0f / 600.0f, 0.1f, 100.0f);

        m_VBO = std::make_unique<VertexBuffer>(positions, 36 * 11 * sizeof(float));
        m_Shader = std::make_unique<Shader>("../../res/shaders/basic.shader");
        m_Shader->bind();
        m_Shader->setUniform("material.diffuse", 0);
        m_Shader->setUniform("material.specular", 2);
        m_VAO = std::make_unique<VertexArray>();

        VertexBufferLayout layout;
        layout.push<float>(3, 0);
        layout.push<float>(3, 3 * sizeof(float));
        layout.push<float>(2, 6 * sizeof(float));
        layout.push<float>(3, 8 * sizeof(float));
        m_VAO->addBuffer(*m_VBO, layout);

        m_IBO = std::make_unique<IndexBuffer>(indices, 36);

        m_Texture0 = std::make_unique<Texture>("../../res/textures/eggdog.jpg", GL_TEXTURE0, 0);
        m_Texture0->Bind(0);
        m_Texture1 = std::make_unique<Texture>("../../res/textures/container2.png", GL_TEXTURE1, 1);
        m_Texture1->Bind(1);

        // Specular map
        m_TextureSpecular0 = std::make_unique<Texture>("../../res/textures/container2_specular.png", GL_TEXTURE2, 2);
        m_TextureSpecular0->Bind(2);

        glfwSetCursorPosCallback(m_Window, mouse_callback);
        glfwSetScrollCallback(m_Window, scroll_callback);
    }

    basicScene::~basicScene()
    {
    }

    void basicScene::onUpdate(float deltaTime, bool cursorEnabled)
    {
        CURSOR_ENABLED = cursorEnabled;
    }

    void basicScene::onRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        processInput(m_Window);
        m_Renderer->clear();

        m_CurrentFrame = glfwGetTime();
        deltaTime = m_CurrentFrame - lastFrame;
        lastFrame = m_CurrentFrame;

        m_Shader->setUniform("f_viewPos", camera.Position);

        {
            for (unsigned int i = 0; i < 10; i++)
            {
                m_View = camera.GetViewMatrix();
                m_Model = glm::translate(glm::mat4(1.0f), m_CubePositions[i]);
                if (m_AnimateFlag)
                {
                    prev_time = glfwGetTime();
                    m_Model = glm::rotate(m_Model, (float)prev_time / 5.0f + i * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
                }
                else
                    m_Model = glm::rotate(m_Model, (float)prev_time / 5.0f + i * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
                m_Proj = glm::perspective(glm::radians(camera.Fov), (float)scene::SCR_WIDTH / (float)scene::SCR_HEIGHT, 0.1f, 100.0f);

                glm::mat4 mvp = m_Proj * m_View * m_Model;
                m_Shader->setUniform("model", m_Model);
                m_Shader->setUniform("u_MVP", mvp);

                m_Shader->setUniform("rColor", glm::vec3(0.0f, 0.0f, 0.0f));

                m_Shader->setUniform("material.shininess", m_CurrentMaterial.shininess);

                m_Shader->setUniform("lightSource", false);

                m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
            }
        }

        // Light source cube
        for (int i = 0; i < 4; i++)
        {
            m_View = camera.GetViewMatrix();
            m_Model = glm::translate(glm::mat4(1.0f), m_PointLightPositions[i]);
            m_Model = glm::scale(m_Model, glm::vec3(0.2f));
            m_Proj = glm::perspective(glm::radians(camera.Fov), (float)scene::SCR_WIDTH / (float)scene::SCR_HEIGHT, 0.1f, 100.0f);

            glm::mat4 mvp = m_Proj * m_View * m_Model;
            m_Shader->setUniform("model", m_Model);
            m_Shader->setUniform("u_MVP", mvp);
            m_Shader->setUniform("rColor", glm::vec3(1.0f, 0.5f, 0.31f));
            m_Shader->setUniform("lightSource", true);

            m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
        }

        // Flashlight
        m_Shader->setUniform("flashlightFlag", m_FlashlightFlag);
        m_Shader->setUniform("spotLight.position", camera.Position);
        m_Shader->setUniform("spotLight.direction", camera.Front);
        m_Shader->setUniform("spotLight.cutOff", m_SpotLight.cutOff);
        m_Shader->setUniform("spotLight.outerCutOff", m_SpotLight.outerCutOff);
        m_Shader->setUniform("spotLight.ambient", m_SpotLight.ambient);
        m_Shader->setUniform("spotLight.diffuse", m_SpotLight.diffuse);
        m_Shader->setUniform("spotLight.specular", m_SpotLight.specular);
        m_Shader->setUniform("spotLight.constant", m_SpotLight.constant);
        m_Shader->setUniform("spotLight.linear", m_SpotLight.linear);
        m_Shader->setUniform("spotLight.quadratic", m_SpotLight.quadratic);

        // Directional Light
        m_Shader->setUniform("directionalLightFlag", m_DirectionalLightFlag);
        m_Shader->setUniform("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        m_Shader->setUniform("dirLight.ambient", glm::vec3(0.02f, 0.02f, 0.02f));
        m_Shader->setUniform("dirLight.diffuse", glm::vec3(0.3f, 0.3f, 0.3f));
        m_Shader->setUniform("dirLight.specular", glm::vec3(0.4f, 0.4f, 0.4f));

        m_Shader->setUniform("pointLightFlag", m_PointLightFlag);

        // Point Light 1
        m_Shader->setUniform("pointLights[0].position", m_PointLightPositions[0]);
        m_Shader->setUniform("pointLights[0].ambient", m_PointLightAmbient);
        m_Shader->setUniform("pointLights[0].diffuse", m_PointLightDiffuse);
        m_Shader->setUniform("pointLights[0].specular", m_PointLightSpecular);
        m_Shader->setUniform("pointLights[0].constant", m_PointLightConstant);
        m_Shader->setUniform("pointLights[0].linear", m_PointLightLinear);
        m_Shader->setUniform("pointLights[0].quadratic", m_PointLightQuadratic);

        // Point Light 2
        m_Shader->setUniform("pointLights[1].position", m_PointLightPositions[1]);
        m_Shader->setUniform("pointLights[1].ambient", m_PointLightAmbient);
        m_Shader->setUniform("pointLights[1].diffuse", m_PointLightDiffuse);
        m_Shader->setUniform("pointLights[1].specular", m_PointLightSpecular);
        m_Shader->setUniform("pointLights[1].constant", m_PointLightConstant);
        m_Shader->setUniform("pointLights[1].linear", m_PointLightLinear);
        m_Shader->setUniform("pointLights[1].quadratic", m_PointLightQuadratic);

        // Point Light 3
        m_Shader->setUniform("pointLights[2].position", m_PointLightPositions[2]);
        m_Shader->setUniform("pointLights[2].ambient", m_PointLightAmbient);
        m_Shader->setUniform("pointLights[2].diffuse", m_PointLightDiffuse);
        m_Shader->setUniform("pointLights[2].specular", m_PointLightSpecular);
        m_Shader->setUniform("pointLights[2].constant", m_PointLightConstant);
        m_Shader->setUniform("pointLights[2].linear", m_PointLightLinear);
        m_Shader->setUniform("pointLights[2].quadratic", m_PointLightQuadratic);

        // Point Light 4
        m_Shader->setUniform("pointLights[3].position", m_PointLightPositions[3]);
        m_Shader->setUniform("pointLights[3].ambient", m_PointLightAmbient);
        m_Shader->setUniform("pointLights[3].diffuse", m_PointLightDiffuse);
        m_Shader->setUniform("pointLights[3].specular", m_PointLightSpecular);
        m_Shader->setUniform("pointLights[3].constant", m_PointLightConstant);
        m_Shader->setUniform("pointLights[3].linear", m_PointLightLinear);
        m_Shader->setUniform("pointLights[3].quadratic", m_PointLightQuadratic);

        m_Shader->setUniform("u_Texture", 0);
        m_Shader->setUniform("u_Texture2", 1);
    }

    void basicScene::onImGuiRender()
    {
        ImGui::Text("X: %.3f \t\t Y: %.3f \t\t Z: %.3f", (double)camera.Position.x,
                    (double)camera.Position.y,
                    (double)camera.Position.z);
        ImGui::Text("Pitch: %.3f \t Yaw: %.3f \t FOV: %.3f", (double)camera.Pitch,
                    (double)camera.Yaw,
                    (double)camera.Fov);
        if (ImGui::Button("Toggle Animation"))
            m_AnimateFlag = !m_AnimateFlag;
        if (ImGui::Button("Toggle Flashlight"))
            m_FlashlightFlag = !m_FlashlightFlag;
        if (ImGui::Button("Toggle Directional Light"))
            m_DirectionalLightFlag = !m_DirectionalLightFlag;
        if (ImGui::Button("Toggle Point Lights"))
            m_PointLightFlag = !m_PointLightFlag;

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        const float cameraSpeed = 4.0f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
    {
        camera.ProcessMouseScroll(yoffset);
    }

    void mouse_callback(GLFWwindow *window, double xpos, double ypos)
    {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        if (!CURSOR_ENABLED)
            camera.ProcessMouseMovement(xoffset, yoffset);
    }
} // namespace scene1