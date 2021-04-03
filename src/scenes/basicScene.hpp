#pragma once

#include "scene.hpp"

#include <memory>
#include <list>

namespace scene {
    class BasicScene : public Scene {
    public:
        BasicScene(GLFWwindow *context);
        ~BasicScene();

        void onUpdate(float deltaTime, bool cursorEnabled) override;
        void onRender() override;
        void onImGuiRender() override;
        void processInput() override;


    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IBO_PLANE;
        std::unique_ptr<IndexBuffer> m_IBO_BOX;
        std::unique_ptr<IndexBuffer> m_IBO_CONE;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture0;
        std::unique_ptr<Texture> m_Texture1;
        std::unique_ptr<Renderer> m_Renderer;

        float m_OffsetValuex;
        float m_OffsetValuey;
        float m_OffsetValuez;

        float m_CurrentFrame = 0;
        int m_CurrentAnimationFrame = 0;
        bool m_Paused = false;

        Object* plane;
        Object* box;
        Object *cone;
        std::vector<Object*> m_objects;

        glm::mat4 m_Proj, m_View, m_Model, m_MVP;
        glm::mat4 m_ModelPausedCone, m_ModelPausedCube, m_ModelPausedPlane;

        GLFWwindow *m_Window;
        GLuint byteoffset;

        CollisionProcessor* m_CollisionProcessor;
    };
}