#pragma once
#include "box.hpp"

class Object {
    public:
        Object(std::string filename, const Eigen::Vector3f& position, BVType bvtype);
        ~Object();

        int getNumVertices();
        void loadInVertices(std::vector<Eigen::Vector3f> &vertices);
        void loadInTexturecoords(std::vector<Eigen::Vector2f> &texturecoords);
        // void initializeIBO(int start, int end);
        // std::unique_ptr<IndexBuffer> m_IBO;

        void rotate(float angle, const Eigen::Vector3f& axis);
        void translate(const Eigen::Vector3f& translation);
        void translate(const glm::vec3& translation);

        Eigen::Vector3f m_Position;
        loadOBJ obj;

        bool fixed = false;

        BVShape* bvshape;



        // Physical properties
        float mass;             // Mass
        Eigen::Matrix3f Iinv;   // Inverse inertia matrix

    private : 
        int numVertices;
};