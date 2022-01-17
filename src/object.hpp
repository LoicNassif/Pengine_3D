#pragma once
#include "box.hpp"

class Contact;

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

        void updateInertiaMatrix();

        Eigen::Vector3f m_Position;
        loadOBJ obj;

        bool fixed = false;

        BVShape* bvshape;


        // Physical properties
        float mass;                     // Mass
        Eigen::Matrix3f Iinv;           // Inverse inertia matrix
        Eigen::Quaternionf q;           // Orientation
        Eigen::Matrix3f R;              // Rotation matrix (auxiliary)
        Eigen::Vector3f xdot;           // Linear velocity.
        Eigen::Vector3f omega;          // Angular velocity.
        Eigen::Vector3f f;              // Linear force
        Eigen::Vector3f tau;            // Angular force (torque)
        Eigen::Vector3f fc;             // Linear constraint force.
        Eigen::Vector3f tauc;           // Angular constraint force

        std::vector<Contact*> contacts; // Pointer array of contact constraints involving this body.

    private : 
        int numVertices;
};