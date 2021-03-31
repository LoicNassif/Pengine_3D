#pragma once
#include <string>
#include "loadOBJ.hpp"
#include "indexbuffer.hpp"
#include "gtc/matrix_transform.hpp"

#include <Discregrid/All>

class Object {
    public:
        Object(std::string filename, glm::vec3 position, const std::array<unsigned int, 3>& res);
        ~Object();

        int getNumVertices();
        void loadInVertices(std::vector<glm::vec3>& vertices);
        void loadInTexturecoords(std::vector<glm::vec2> &texturecoords);
        // void initializeIBO(int start, int end);
        // std::unique_ptr<IndexBuffer> m_IBO;

        void rotate(float angle, const glm::vec3& axis);
        void translate(const glm::vec3& translation);

        glm::vec3 m_Position;

    private : 
        int numVertices;
        loadOBJ obj;

        Discregrid::CubicLagrangeDiscreteGrid sdf;
        Discregrid::TriangleMesh mesh;
};