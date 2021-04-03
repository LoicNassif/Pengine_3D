#pragma once
#include <string>
#include "loadOBJ.hpp"
#include "indexbuffer.hpp"
#include "gtc/matrix_transform.hpp"

class Object {
    public:
        Object(std::string filename, glm::vec3 position);
        ~Object();

        int getNumVertices();
        void loadInVertices(std::vector<Eigen::Vector3f> &vertices);
        void loadInTexturecoords(std::vector<Eigen::Vector2f> &texturecoords);
        // void initializeIBO(int start, int end);
        // std::unique_ptr<IndexBuffer> m_IBO;

        void rotate(float angle, const glm::vec3& axis);
        void translate(const glm::vec3& translation);

        glm::vec3 m_Position;
        loadOBJ obj;

    private : 
        int numVertices;
};