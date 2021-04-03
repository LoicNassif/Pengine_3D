#pragma once
#include "../include/tinyobjloader/tiny_obj_loader.h"
#include <iostream>
#include <Eigen/Dense>

#include "glm.hpp"

class loadOBJ {
    public:
        loadOBJ(std::string inputFile);
        ~loadOBJ();

        tinyobj::attrib_t m_Attrib;
        std::vector<tinyobj::shape_t> m_Shapes;
        std::vector<tinyobj::material_t> m_Materials;

        // Note that a face is three vertices in a row.
        std::vector<Eigen::Vector3f> m_Vertices; // x, y, z
        std::vector<Eigen::Vector3f> m_Normals;  // nx, ny, nz
        std::vector<Eigen::Vector2f> m_Texcoords; // u, v
};