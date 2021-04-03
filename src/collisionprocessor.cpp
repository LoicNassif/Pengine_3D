#include "collisionprocessor.hpp"

// Naive implementation
void CollisionProcessor::processCollision(const std::vector<Object*>& objs) {
    // Detect if a collision occured
    for (int i=0; i<objs.size(); i++) {
        for (int j=0; j<objs.size(); j++) {
            if (i != j) {
                if (detectCollision(objs[i], objs[j])) {
                    std::cout << "GATE-01: COLLISION" << std::endl;
                }
            }
        }
    }
}

// Naive implementation
bool CollisionProcessor::detectCollision(Object* a, Object* b) {
    // Check Face-Vertex collisions
    for (int i=0; i<a->getNumVertices(); i++) {
        Eigen::Vector3f a0 = a->obj.m_Vertices[i];
        for (int j=0; j<b->getNumVertices(); j+=3) {
            // Taken from the following tutorial for ray-triangle intersection:
            // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/barycentric-coordinates
            // TODO: Use barycentric coords to compute if the A vertex is inside the B triangle face.
            Eigen::Vector3f b0 = b->obj.m_Vertices[j];
            Eigen::Vector3f b1 = b->obj.m_Vertices[j + 1];
            Eigen::Vector3f b2 = b->obj.m_Vertices[j + 2];

            // Compute the face's normal
            Eigen::Vector3f b0b1 = b1 - b0;
            Eigen::Vector3f b0b2 = b2 - b0;
            Eigen::Vector3f normal = b0b1.cross(b0b2);
            float area = normal.norm() / 2;

            // Do the inside-out test
            Eigen::Vector3f C;
            
            // Edge 0
            Eigen::Vector3f e0 = b1 - b0;
            Eigen::Vector3f b0a0 = a0 - b0;
            C = e0.cross(b0a0);
            float u0 = (C.norm() / 2) / area;
            if (normal.dot(C) >= 0) return false;

            // Edge 1
            Eigen::Vector3f e1 = b2 - b1;
            Eigen::Vector3f b1a0 = a0 - b1;
            C = e1.cross(b1a0);
            float u1 = (C.norm() / 2) / area;
            if (normal.dot(C) >= 0) return false;

            // Edge 2
            Eigen::Vector3f e2 = b0 - b2;
            Eigen::Vector3f b2a0 = a0 - b2;
            C = e2.cross(b2a0);
            float u2 = (C.norm() / 2) / area;
            if (normal.dot(C) >= 0) return false;

            return true; 
        }
    }
}