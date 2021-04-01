#include "collisionprocessor.hpp"

// Naive implementation
void CollisionProcessor::detectCollision(Object a, Object b) {
    // Check Face-Vertex collisions
    for (int i=0; i<a.getNumVertices(); i++) {
        for (int j=0; j<b.getNumVertices(); j+=3) {
            // TODO: Use barycentric coords to compute if the A vertex is inside the B triangle face.
        }
    }
}