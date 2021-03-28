#define TINYOBJLOADER_IMPLEMENTATION
#include "loadOBJ.hpp"

// TAKEN FROM EXAMPLE CODE ON tinyobjloader GITHUB
loadOBJ::loadOBJ(std::string inputFile)  {
    tinyobj::ObjReaderConfig reader_config;

    tinyobj::ObjReader reader;

    // Catch Errors
    if (!reader.ParseFromFile(inputFile, reader_config)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    } 

    // Catch Warnings
    if (!reader.Warning().empty()) {
        std::cout << "TinyObjReader: " << reader.Warning();
    }

    m_Attrib = reader.GetAttrib();
    m_Shapes = reader.GetShapes();
    m_Materials = reader.GetMaterials();

    // Loop over shapes
    for (size_t s = 0; s < m_Shapes.size(); s++) {
        // Loop over faces
        size_t index_offset = 0;
        for (size_t f = 0; f < m_Shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(m_Shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face
            for (size_t v = 0; v < fv; v++) {
                // Access to vertex
                tinyobj::index_t idx = m_Shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = m_Attrib.vertices[3*size_t(idx.vertex_index)+0];
                tinyobj::real_t vy = m_Attrib.vertices[3*size_t(idx.vertex_index)+1];
                tinyobj::real_t vz = m_Attrib.vertices[3*size_t(idx.vertex_index)+2];

                m_Vertices.push_back(glm::vec3(vx, vy, vz));

                // Check if `normal_index` is zero or positive. Negative means no normal data.
                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = m_Attrib.normals[3*size_t(idx.normal_index)+0];
                    tinyobj::real_t ny = m_Attrib.normals[3*size_t(idx.normal_index)+1];
                    tinyobj::real_t nz = m_Attrib.normals[3*size_t(idx.normal_index)+2];

                    m_Normals.push_back(glm::vec3(nx, ny, nz));
                } else {
                    m_Normals.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
                }


                // Check if `texcoords_index` is zero or positive. Negative means no textcoord data.
                if (idx.texcoord_index >= 0) {
                    tinyobj::real_t tx = m_Attrib.texcoords[2*size_t(idx.texcoord_index)+0];
                    tinyobj::real_t ty = m_Attrib.texcoords[2*size_t(idx.texcoord_index)+1];

                    m_Texcoords.push_back(glm::vec2(tx, ty));
                } else {
                    m_Texcoords.push_back(glm::vec2(0.0f, 0.0f));
                }
            }
            index_offset += fv;

            // per-face material
            m_Shapes[s].mesh.material_ids[f];
        }
    }
}

loadOBJ::~loadOBJ() {

}