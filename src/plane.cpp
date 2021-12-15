#include "plane.hpp"


Plane::Plane(std::string filename, glm::vec3 position) {
    // Compute normal by taking two level vertices and cross product them
    //float maxHeight = maxAxis(obj.m_Vertices, 1);
    //int index1 = -1;
    //int index2 = -1;
    //for (int i = 0; i < getNumVertices(); i++) {
    //    if (obj.m_Vertices[i][1] == maxHeight) {
    //        if (index1 != -1) {
    //            index2 = i;
    //        }
    //        else {
    //            index1 = i;
    //        }
    //    }
    //}
    normal = Eigen::Vector3f(0.0f, 1.0f, 0.0f);
}

Plane::~Plane() {}

Eigen::Vector3f Plane::getNormal() 
{
    return normal;
}