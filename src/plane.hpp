#pragma once

#include "object.hpp"

class Plane {
public:
    Plane(std::string filename, glm::vec3 position);
    ~Plane();

    Eigen::Vector3f getNormal();

private:
    Eigen::Vector3f normal;
};