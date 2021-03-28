#pragma once
#include "../include/tinyobjloader/tiny_obj_loader.h"
#include <iostream>

#include "glm.hpp"

class loadOBJ {
    public:
        loadOBJ(std::string inputFile);
        ~loadOBJ();

        tinyobj::attrib_t m_Attrib;
        std::vector<tinyobj::shape_t> m_Shapes;
        std::vector<tinyobj::material_t> m_Materials;

        std::vector<glm::vec3> m_Vertices; // x, y, z
        std::vector<glm::vec3> m_Normals;  // nx, ny, nz
        std::vector<glm::vec2> m_Texcoords; // u, v
};