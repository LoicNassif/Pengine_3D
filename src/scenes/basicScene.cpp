#include "basicScene.hpp"

namespace scene {

Camera camera(glm::vec3(1.0f, 0.5f, 1.5f));
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;
bool firstMouse = true;

bool CURSOR_ENABLED = true;

// Frame timing values
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void processInput(GLFWwindow *window);

BasicScene::BasicScene(GLFWwindow *context)
    : m_Proj(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)),
      m_Model(glm::mat4(1.0f)), m_MVP(glm::mat4(1.0f)),
      m_OffsetValuex(0), m_OffsetValuey(0), m_OffsetValuez(0),
      m_Window(context)
{

    plane = new Object("../res/objects/plane_box.obj", glm::vec3(0.0f, 0.0f, 0.0f));
    box = new Object("../res/objects/box.obj", glm::vec3(1.0f, 0.5f, 0.0f));
    cone = new Object("../res/objects/big_funnel3.obj", glm::vec3(0.0f, 1.0f, 0.0f));

    const int numVertices = plane->getNumVertices() + box->getNumVertices() + cone->getNumVertices();

    std::vector<Eigen::Vector3f> vertices;
    std::vector<Eigen::Vector2f> texturecoords;

    plane->loadInVertices(vertices);
    box->loadInVertices(vertices);
    cone->loadInVertices(vertices);

    plane->loadInTexturecoords(texturecoords);
    box->loadInTexturecoords(texturecoords);
    cone->loadInTexturecoords(texturecoords);

    float* positions;
    positions = new float[8*numVertices];

    for (int i=0; i<numVertices; i++) {
        // Positions
        positions[8 * i + 0] = vertices[i].x();
        positions[8 * i + 1] = vertices[i].y();
        positions[8 * i + 2] = vertices[i].z();

        // Colour
        positions[8 * i + 3] = 0;
        positions[8 * i + 4] = 0;
        positions[8 * i + 5] = 0;

        // Texture coords
        positions[8 * i + 6] = texturecoords[i].x();
        positions[8 * i + 7] = texturecoords[i].y();
    }

    std::vector<unsigned int> t1;
    for (int i = 0; i < plane->getNumVertices(); i++)
    {
        t1.push_back(i);
    }
    unsigned int *indicesPlane = &t1[0];

    std::vector<unsigned int> t2;
    for (int i = plane->getNumVertices(); i < plane->getNumVertices() + box->getNumVertices(); i++)
    {
        t2.push_back(i);
    }
    unsigned int* indicesBox = &t2[0];

    std::vector<unsigned int> t3;
    for (int i = plane->getNumVertices() + box->getNumVertices(); i < numVertices; i++)
    {
        t3.push_back(i);
    }
    unsigned int *indicesCone = &t3[0];

    m_objects.push_back(plane);
    m_objects.push_back(box);
    m_objects.push_back(cone);

    m_Model = glm::rotate(m_Model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    m_Proj = glm::perspective(glm::radians(camera.Fov), (float)scene::SCR_WIDTH / (float)scene::SCR_HEIGHT, 0.1f, 100.0f);

    m_VBO = std::make_unique<VertexBuffer>(positions, numVertices * 8 * sizeof(float));
    m_Shader = std::make_unique<Shader>("../res/shaders/basic.shader");
    m_VAO = std::make_unique<VertexArray>();

    VertexBufferLayout layout;
    layout.push<float>(3, 0);
    layout.push<float>(3, 3 * sizeof(float));
    layout.push<float>(2, 6 * sizeof(float));
    m_VAO->addBuffer(*m_VBO, layout);

    // plane.initializeIBO(0, plane.getNumVertices());
    // box.initializeIBO(plane.getNumVertices(), numVertices);

    m_IBO_PLANE = std::make_unique<IndexBuffer>(indicesPlane, plane->getNumVertices());
    m_IBO_BOX = std::make_unique<IndexBuffer>(indicesBox, box->getNumVertices());
    m_IBO_CONE = std::make_unique<IndexBuffer>(indicesCone, cone->getNumVertices());

    m_Texture0 = std::make_unique<Texture>("../res/textures/eggdog.jpg", GL_TEXTURE0, 0);
    m_Texture1 = std::make_unique<Texture>("../res/textures/planks_horizontal.jpg", GL_TEXTURE0, 0);
    m_Texture1->Unbind();
    m_Texture0->Unbind();

    glfwSetCursorPosCallback(m_Window, mouse_callback);
    glfwSetScrollCallback(m_Window, scroll_callback);
}

BasicScene::~BasicScene()
{
}

void BasicScene::onUpdate(float deltaTime, bool cursorEnabled)
{
    processInput();

    CURSOR_ENABLED = cursorEnabled;
}

void BasicScene::onRender()
{

            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            m_Renderer->clear();

            m_CurrentFrame = glfwGetTime();
            deltaTime = m_CurrentFrame - lastFrame;
            lastFrame = m_CurrentFrame;

            m_CollisionProcessor->processCollision(m_objects);

            if (!m_Paused)
                m_CurrentAnimationFrame++;

            // Start with Paused state
            if (m_CurrentAnimationFrame == 2) {
                m_Paused = true;
            }

            // Plane
            {
                m_View = camera.GetViewMatrix();

                if (!m_Paused) {
                    m_Model = glm::translate(glm::mat4(1.0f), plane->m_Position);
                    m_ModelPausedPlane = m_Model;
                } else {
                    m_Model = m_ModelPausedPlane;
                }
                m_Proj = glm::perspective(glm::radians(camera.Fov), (float)scene::SCR_WIDTH / (float)scene::SCR_HEIGHT, 0.1f, 100.0f);

                glm::mat4 mvp = m_Proj * m_View * m_Model;
                m_Texture1->Bind(0);
                m_Shader->bind();
                m_Shader->setUniform("u_MVP", mvp);
                m_Renderer->draw(*m_VAO, *m_IBO_PLANE, *m_Shader);
                m_Texture1->Unbind();
            }

            // Cube
            {
                m_View = camera.GetViewMatrix();

                if (!m_Paused) {
                    box->m_Position.y += (float)-1 / (float)500;

                    // box->m_Position.y += -0.5 * 9.8 * (float)m_CurrentAnimationFrame * (float)m_CurrentAnimationFrame / 1000000;
                    m_Model = glm::translate(glm::mat4(1.0f), box->m_Position);
                    // m_Model = glm::rotate(m_Model, (float)m_CurrentAnimationFrame / 50.0f + glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
                    m_ModelPausedCube = m_Model;
                } else {
                    m_Model = m_ModelPausedCube;
                }
                m_Proj = glm::perspective(glm::radians(camera.Fov), (float)scene::SCR_WIDTH / (float)scene::SCR_HEIGHT, 0.1f, 100.0f);

                glm::mat4 mvp = m_Proj * m_View * m_Model;
                m_Texture0->Bind(0);
                m_Shader->bind();
                m_Shader->setUniform("u_MVP", mvp);
                m_Renderer->draw(*m_VAO, *m_IBO_BOX, *m_Shader);
                m_Texture0->Unbind();
            }

            // Cone
            {
                m_View = camera.GetViewMatrix();

                if (!m_Paused) {
                    m_Model = glm::translate(glm::mat4(1.0f), cone->m_Position);
                    m_Model = glm::rotate(m_Model, (float)m_CurrentAnimationFrame / 50.0f + glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
                    m_ModelPausedCone = m_Model;
                } else {
                    m_Model = m_ModelPausedCone;
                }
                m_Proj = glm::perspective(glm::radians(camera.Fov), (float)scene::SCR_WIDTH / (float)scene::SCR_HEIGHT, 0.1f, 100.0f);

                glm::mat4 mvp = m_Proj * m_View * m_Model;
                m_Texture0->Bind(0);
                m_Shader->bind();
                m_Shader->setUniform("u_MVP", mvp);
                m_Renderer->draw(*m_VAO, *m_IBO_CONE, *m_Shader);
                m_Texture0->Unbind();
            }

            m_Shader->setUniform("u_Texture", 0);

            m_Shader->setUniform("offsetx", m_OffsetValuex);
            m_Shader->setUniform("offsety", m_OffsetValuey);
            m_Shader->setUniform("offsetz", m_OffsetValuez);
        
}

void BasicScene::onImGuiRender()
{
    ImGui::Text("X: %.3f \t\t Y: %.3f \t\t Z: %.3f", (double)camera.Position.x,
                (double)camera.Position.y,
                (double)camera.Position.z);
    ImGui::Text("Pitch: %.3f \t Yaw: %.3f \t FOV: %.3f", (double)camera.Pitch,
                (double)camera.Yaw,
                (double)camera.Fov);

    if(ImGui::Button("Pause")) m_Paused = !m_Paused;

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void BasicScene::processInput()
{
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);

    const float cameraSpeed = 4.0f * deltaTime;
    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_Paused = !m_Paused;
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
}