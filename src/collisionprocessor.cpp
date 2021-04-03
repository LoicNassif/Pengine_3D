#include "collisionprocessor.hpp"

void CollisionProcessor::processCollision(Object* a, Object* b) {
    // Detect if a collision occured
    detectCollision(a, b);
}

// Naive implementation
void CollisionProcessor::detectCollision(Object* a, Object* b) {
    // Check Face-Vertex collisions
    for (int i=0; i<a->getNumVertices(); i++) {
        Eigen::Vector3f a0 = a->obj.m_Vertices[i];
        for (int j=0; j<b->getNumVertices(); j+=3) {
            // TODO: Use barycentric coords to compute if the A vertex is inside the B triangle face.
            Eigen::Vector3f b0 = b->obj.m_Vertices[j];
            Eigen::Vector3f b1 = b->obj.m_Vertices[j + 1];
            Eigen::Vector3f b2 = b->obj.m_Vertices[j + 2];

            // Compute the face's normal
            Eigen::Vector3f b0b1;

            // glm::vec3 b0b1 = b1 - b0;
            // glm::vec3 b0b2 = b2 - b0;
        }
    }
}