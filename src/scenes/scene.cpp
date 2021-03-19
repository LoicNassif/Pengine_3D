#include "scene.hpp"

namespace scene {
    SceneMenu::SceneMenu(Scene*& currentScenePointer, GLFWwindow* context)
        : m_CurrentScene(currentScenePointer), m_Window(context) {

    }

    void SceneMenu::onRender() {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void SceneMenu::onImGuiRender() {        
        for (auto& scene : m_Scenes) {
            if (ImGui::Button(scene.first.c_str())) {
                m_CurrentScene = scene.second(m_Window);
            }
        }
    }
}