#pragma once


#include <vector>
#include <functional>

#include "vertexbuffer.hpp"
#include "vertexbufferlayout.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "vertexarray.hpp"
#include "camera.hpp"
#include "collisionprocessor.hpp"
#include "box.hpp"

#include "../renderer.hpp"
#include "../../thirdparty/imgui/imgui.h"
#include "../../thirdparty/imgui/imgui_impl_glfw.h"
#include "../../thirdparty/imgui/imgui_impl_opengl3.h"

namespace scene {

// General settings
const unsigned int SCR_WIDTH = 1360;
const unsigned int SCR_HEIGHT = 768;

class Material {
public:
    // glm::vec3 specular;
    glm::vec3 diffuse;
    float shininess;

    Material() 
        : diffuse(1.0f, 0.5f, 0.31f),
        shininess(64)
    {}

    ~Material() {}
};

class Light {
public:
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;

    Light()
        : position(glm::vec3(3.0f, 0.0f, -1.0f)),
        ambient(glm::vec3(0.2f, 0.2f, 0.2f)),
        diffuse(glm::vec3(0.5f, 0.5f, 0.5f))
    {}

    ~Light() {}
};

class Scene
{
public:
    Scene() {}
    virtual ~Scene() {}

    virtual void onUpdate(float deltaTime) {}
    virtual void onUpdate(float deltaTime, bool cursorEnabled) {}
    virtual void onRender() {}
    virtual void onImGuiRender() {}
    virtual void processInput() {}
    };

class SceneMenu : public Scene {
public:
    SceneMenu(Scene *&currentScenePointer, GLFWwindow *context);

    void onImGuiRender() override;
    void onRender() override;

    template<typename T>
    void registerScene(const std::string& name, GLFWwindow* window) {
        std::cout << "Registering Scene " << name << std::endl;
        m_Scenes.push_back(std::make_pair(name, [](GLFWwindow *window) { return new T(window); }));
    }

private:
    GLFWwindow* m_Window;
    Scene*& m_CurrentScene;
    CollisionProcessor* m_CollisionProcessor;

    std::vector<std::pair<std::string, std::function<Scene *(GLFWwindow *window)>>> m_Scenes;
};
}
