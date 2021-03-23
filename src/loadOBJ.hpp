#pragma once
#include "../include/tinyobjloader/tiny_obj_loader.h"
#include <iostream>

class loadOBJ {
    public:
        loadOBJ();
        ~loadOBJ();

    private:
        tinyobj::attrib_t m_Attrib;
        std::vector<tinyobj::shape_t> m_Shapes;
        std::vector<tinyobj::material_t> m_Materials;
};