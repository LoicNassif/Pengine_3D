#include "basicScene.hpp"

namespace scene {

constexpr int n(const int numVertices)
{
    return numVertices;
}

Camera camera(glm::vec3(0.0f, 1.0f, 2.0f));
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

    loadOBJ boxObj = loadOBJ("../res/objects/plane_box.obj");
    loadOBJ boxObj2 = loadOBJ("../res/objects/box.obj");

    const int numVertices = boxObj.m_Vertices.size() + boxObj2.m_Vertices.size();

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texturecoords;

    for (int i=0; i < boxObj.m_Vertices.size(); i++)
    {
        vertices.push_back(boxObj.m_Vertices[i]);
    }
    for (int i=0; i < boxObj2.m_Vertices.size(); i++)
    {
        vertices.push_back(boxObj2.m_Vertices[i]);
    }

    for (int i = 0; i < boxObj.m_Vertices.size(); i++)
    {
        texturecoords.push_back(boxObj.m_Texcoords[i]);
    }
    for (int i = 0; i < boxObj2.m_Vertices.size(); i++)
    {
        texturecoords.push_back(boxObj2.m_Texcoords[i]);
    }

    float* positions;
    positions = new float[8*numVertices];

    for (int i=0; i<numVertices; i++) {
        // Positions
        positions[8 * i + 0] = vertices[i].x;
        positions[8 * i + 1] = vertices[i].y;
        positions[8 * i + 2] = vertices[i].z;

        // Colour
        positions[8 * i + 3] = 0;
        positions[8 * i + 4] = 0;
        positions[8 * i + 5] = 0;

        // Texture coords
        positions[8 * i + 6] = texturecoords[i].x;
        positions[8 * i + 7] = texturecoords[i].y;
    }
    
    std::vector<unsigned int> test;
    for (int i = boxObj.m_Vertices.size(); i < numVertices; i++)
    {
        test.push_back(i);
    }
    unsigned int* indicesBox = &test[0];

    std::vector<unsigned int> test2;
    for (int i = 0; i < boxObj.m_Vertices.size(); i++)
    {
        test2.push_back(i);
    }
    unsigned int *indicesPlane = &test2[0];

    m_PlanePosition = glm::vec3(0.0f, 0.0f, 0.0f);
    m_CubePosition = glm::vec3(0.0f, 1.0f, 0.0f);

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

    m_IBO_PLANE = std::make_unique<IndexBuffer>(indicesPlane, boxObj.m_Vertices.size());
    m_IBO_BOX = std::make_unique<IndexBuffer>(indicesBox, boxObj2.m_Vertices.size());

    m_Texture0 = std::make_unique<Texture>("../res/textures/eggdog.jpg", GL_TEXTURE0, 0);
    m_Texture0->Bind(0);

    glfwSetCursorPosCallback(m_Window, mouse_callback);
    glfwSetScrollCallback(m_Window, scroll_callback);
}

BasicScene::~BasicScene()
{
}

void BasicScene::onUpdate(float deltaTime, bool cursorEnabled)
{
    CURSOR_ENABLED = cursorEnabled;
}

void BasicScene::onRender()
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    processInput(m_Window);
    m_Renderer->clear();

    m_CurrentFrame = glfwGetTime();
    deltaTime = m_CurrentFrame - lastFrame;
    lastFrame = m_CurrentFrame;

    // Plane
    {
        m_View = camera.GetViewMatrix();

        m_Model = glm::translate(glm::mat4(1.0f), m_PlanePosition);
        m_Proj = glm::perspective(glm::radians(camera.Fov), (float)scene::SCR_WIDTH / (float)scene::SCR_HEIGHT, 0.1f, 100.0f);

        glm::mat4 mvp = m_Proj * m_View * m_Model;
        m_Shader->bind();
        m_Shader->setUniform("u_MVP", mvp);
        m_Renderer->draw(*m_VAO, *m_IBO_PLANE, *m_Shader);

    }

    // Cube
    {
        m_View = camera.GetViewMatrix();
        // m_CubePosition.y += -0.5 * 9.8 * (float)glfwGetTime() * (float)glfwGetTime() / 1000;

        m_Model = glm::translate(glm::mat4(1.0f), m_CubePosition);
        m_Model = glm::rotate(m_Model, (float)glfwGetTime() / 5.0f + glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        m_Proj = glm::perspective(glm::radians(camera.Fov), (float)scene::SCR_WIDTH / (float)scene::SCR_HEIGHT, 0.1f, 100.0f);

        glm::mat4 mvp = m_Proj * m_View * m_Model;
        m_Shader->bind();
        m_Shader->setUniform("u_MVP", mvp);
        m_Renderer->draw(*m_VAO, *m_IBO_BOX, *m_Shader);
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
}