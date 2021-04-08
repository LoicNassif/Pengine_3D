#include "collisionprocessor.hpp"

// Debug printing function
void printVector3f(std::string name, Eigen::Vector3f v)
{
    std::cout << name << " : (" << v.x() << ", " << v.y() << ", " << v.z() << ")" << std::endl;
}

// Naive implementation
void CollisionProcessor::processCollision(const std::vector<Object *> &objs, glm::mat4 m_ModelA, glm::mat4 m_ModelB)
{
    for (int i=0; i<modelA.size(); i++) {
        for (int j=0; j<modelA.size(); j++) {
            modelA(i,j) = m_ModelA[i][j];
            modelB(i,j) = m_ModelB[i][j];
        }
    }

    // Detect if a collision occured
    for (int i=0; i<objs.size(); i++) {
        for (int j=0; j<objs.size(); j++) {
            if (i != j) {
                if (detectCollision(objs[i], objs[j]) == true) {
                    std::cout << "GATE-01: COLLISION" << std::endl;
                }
            }
        }
    }
}

// TODO: Moller's triangle-triangle collision detection
bool CollisionProcessor::detectCollTriangleTriangle(Object *A, int i, Object *B, int j)
{
    // Eigen::Vector4f A0b(A->obj.m_Vertices[i].x(), A->obj.m_Vertices[i].y(), A->obj.m_Vertices[i].z(), 1);
    // Eigen::Vector4f A1b(A->obj.m_Vertices[i+1].x(), A->obj.m_Vertices[i+1].y(), A->obj.m_Vertices[i+1].z(), 1);
    // Eigen::Vector4f A2b(A->obj.m_Vertices[i+2].x(), A->obj.m_Vertices[i+2].y(), A->obj.m_Vertices[i+2].z(), 1);

    // Eigen::Vector4f B0b(B->obj.m_Vertices[i].x(), B->obj.m_Vertices[i].y(), B->obj.m_Vertices[i].z(), 1);
    // Eigen::Vector4f B1b(B->obj.m_Vertices[i+1].x(), B->obj.m_Vertices[i+1].y(), B->obj.m_Vertices[i+1].z(), 1);
    // Eigen::Vector4f B2b(B->obj.m_Vertices[i+2].x(), B->obj.m_Vertices[i+2].y(), B->obj.m_Vertices[i+2].z(), 1);

    // // TODO FIX THE BODY TO WORLD CONVERSION
    // // Convert the vertices into world coordinates
    // Eigen::Vector4f A0 = A0b.transpose() * modelA;
    // Eigen::Vector4f A1 = A1b.transpose() * modelA;
    // Eigen::Vector4f A2 = A2b.transpose() * modelA;

    // Eigen::Vector4f B0 = B0b.transpose() * modelB;
    // Eigen::Vector4f B1 = B1b.transpose() * modelB;
    // Eigen::Vector4f B2 = B2b.transpose() * modelB;

    // // Compute the plane equation for triangle B
    // Eigen::Vector3f NB = (B1 - B0).cross(B2 - B0);
    // float dB = -NB.dot(B0);

    // // Compute the plane equation for triangle A
    // Eigen::Vector3f NA = (A1 - A0).cross(A2 - A0);
    // float dA = -NA.dot(A0);

    // // Compute the signed distances from vertices of A to plane eq. of B
    // float dA0 = NB.dot(A0) + dB;
    // float dA1 = NB.dot(A1) + dB;
    // float dA2 = NB.dot(A2) + dB;

    // // Compute the signed distances from vertices of B to plane eq. of A
    // float dB0 = NA.dot(B0) + dA;
    // float dB1 = NA.dot(B1) + dA;
    // float dB2 = NA.dot(B2) + dA;

    // // std::cout << i << ", " << j << std::endl;

    // // The intersection of both planes is a line with direction dL
    // Eigen::Vector3f dL = NA.cross(NB);

    // if (dA0 != 0 && dA1 != 0 && dA2 != 0)
    // {
    //     // std::cout << "BRUH-0" << std::endl;

    //     // A lies entirely on one side of the plane of B -> NO intersections
    //     if ((dA0 < 0 && dA1 < 0 && dA2 < 0) || (dA0 > 0 && dA1 > 0 && dA2 > 0))
    //         return false;
        
    // } else if (dB0 != 0 && dB1 != 0 && dB2 != 0) {
    //     // std::cout << "BRUH-1" << std::endl;
    //     // B lies entirely on one side of the plane of A -> NO intersections
    //     if ((dB0 < 0 && dB1 < 0 && dB2 < 0) || (dB0 > 0 && dB1 > 0 && dB2 > 0))
    //         return false;
        
    // } 

    // // Project the vertices of A onto the intersecting line
    // float pA0 = dL.dot(A0);
    // float pA1 = dL.dot(A1);
    // float pA2 = dL.dot(A2);

    // // Find the line parameter value t1 which gives the lower bound of the intersection interval
    // float t1A = pA0 + (pA1 - pA0) * dA0 / (dA0 - dA1);

    // // Find the line parameter value t2 which gives the upper bound of the intersection interval
    // float t2A = pA1 + (pA2 - pA1) * dA1 / (dA1 - dA2);

    // // Project the vertices of B onto the intersecting line
    // float pB0 = dL.dot(B0);
    // float pB1 = dL.dot(B1);
    // float pB2 = dL.dot(B2);

    // // Find the line parameter value t1 which gives the lower bound of the intersection interval
    // float t1B = pB0 + (pB1 - pB0) * dB0 / (dB0 - dB1);

    // // Find the line parameter value t2 which gives the upper bound of the intersection interval
    // float t2B = pB1 + (pB2 - pB1) * dB1 / (dB1 - dB2);

    // // Check if the intervals overlap
    // if (t2A > t1B || t2B > t1A) {
    //     printVector3f("A0", A0);
    //     printVector3f("A1", A1);
    //     printVector3f("A2", A2);
    //     std::cout << "dA: (" << dA0 << ", " << dA1 << ", " << dA2 << ")" << std::endl;
    //     std::cout << "tA: (" << t1A << ", " << t2A << ")" << std::endl;

    //     printVector3f("B0", B0);
    //     printVector3f("B1", B1);
    //     printVector3f("B2", B2);
    //     std::cout << "dB: (" << dB0 << ", " << dB1 << ", " << dB2 << ")" << std::endl;
    //     std::cout << "tB: (" << t1B << ", " << t2B << ")" << std::endl;

    //     // intersection!
    //     return true;
    // }
    
    return false;
}

bool CollisionProcessor::detectCollision(Object* a, Object* b) {
    for (int i=0; i<a->getNumVertices(); i+=3) {
        for (int j=0; j<a->getNumVertices(); j+=3) {
            bool val = detectCollTriangleTriangle(a, i, b, j);
            // std::cout << val << std::endl;   
            if (val == true) {
                std::cout << i << ", " << j << std::endl;
                std::cout << "GATE-02" << std::endl;
                return true;
            }
        }
    }
    return false;
}



// bool detectCollPointTriangle(const Eigen::Vector3f &a0, Object *b, int index)
// {
//     // Taken from the following tutorial for ray-triangle intersection:
//     // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/barycentric-coordinates
//     // TODO: Use barycentric coords to compute if the A vertex is inside the B triangle face.
//     Eigen::Vector3f b0 = b->obj.m_Vertices[index];
//     Eigen::Vector3f b1 = b->obj.m_Vertices[index + 1];
//     Eigen::Vector3f b2 = b->obj.m_Vertices[index + 2];


//     // Compute the face's normal
//     Eigen::Vector3f b0b1 = b1 - b0;
//     Eigen::Vector3f b0b2 = b2 - b0;
//     Eigen::Vector3f normal = b0b1.cross(b0b2);
//     float area = normal.norm() / 2;
//     normal.normalize();

//     // Do the inside-out test
//     Eigen::Vector3f C;

//     if (index == 0)
//     {
//         std::cout << "b0: (" << b0.x() << ", " << b0.y() << ", " << b0.z() << ")" << std::endl;
//         std::cout << "b1: (" << b1.x() << ", " << b1.y() << ", " << b1.z() << ")" << std::endl;
//         std::cout << "b2: (" << b2.x() << ", " << b2.y() << ", " << b2.z() << ")" << std::endl;
//         printVector3f("N", normal);
//     }

//     // Edge 0
//     Eigen::Vector3f e0 = b1 - b0;
//     Eigen::Vector3f b0a0 = a0 - b0;
//     C = e0.cross(b0a0);
//     float u0 = (C.norm() / 2) / area;
//     if (index == 0) {
//         std::cout << "EDGE-0" << std::endl;
//         printVector3f("C", C);
//     }
//     if (normal.dot(C) < 0)
//         return false;

//     // Edge 1
//     Eigen::Vector3f e1 = b2 - b1;
//     Eigen::Vector3f b1a0 = a0 - b1;
//     C = e1.cross(b1a0);
//     float u1 = (C.norm() / 2) / area;
//     if (index == 0) {
//         std::cout << "EDGE-1" << std::endl;
//         printVector3f("C", C); 
//     }

//     if (normal.dot(C) < 0)
//         return false;

//     // Edge 2
//     Eigen::Vector3f e2 = b0 - b2;
//     Eigen::Vector3f b2a0 = a0 - b2;
//     C = e2.cross(b2a0);
//     float u2 = (C.norm() / 2) / area;
//     if (index == 0)
//     {
//         std::cout << "EDGE-2" << std::endl;
//         printVector3f("C", C);
//         std::cout << "-------------------------------" << std::endl;
//     }
//     if (normal.dot(C) < 0)
//         return false;


//     return true;
// }

// // Naive implementation
// bool CollisionProcessor::detectCollision(Object* a, Object* b) {
//     // Check Face-Vertex collisions
//     for (int i=0; i<a->getNumVertices(); i++) {
//         Eigen::Vector3f a0 = a->obj.m_Vertices[i];
//         std::cout << i << std::endl;
//         std::cout << "a0: (" << a0.x() << ", " << a0.y() << ", " << a0.z() << ")" << std::endl;
//         std::cout << "======================================" << std::endl;
    
//         for (int j=0; j <b->getNumVertices(); j+=3) {
//             if (detectCollPointTriangle(a0, b, j)) {
//                 return true;
//             }
//         }
//     }
//     return false;
// }