#include "object.hpp"

Object::Object(std::string filename, glm::vec3 position, const std::array<unsigned int, 3>& res) 
    : obj(loadOBJ(filename)), mesh(filename), m_Position(position)
{
    Eigen::AlignedBox3f domain;
    domain.setEmpty();

    Discregrid::MeshDistance md(mesh);

    for (auto const& x : mesh.vertices()) {
        domain.extend(x);
    }

    domain.max() += 1.0e-3f * domain.diagonal().norm() * Eigen::Vector3f::Ones();
    domain.min() -= 1.0e-3f * domain.diagonal().norm() * Eigen::Vector3f::Ones();

    sdf = Discregrid::CubicLagrangeDiscreteGrid(domain, res);

    // Create function that returns the SD
    auto func = Discregrid::DiscreteGrid::ContinuousFunction{};
    func = [&md](Eigen::Vector3f const& xi) { return md.signedDistanceCached(xi); };
    sdf.addFunction(func, true);

    numVertices = obj.m_Vertices.size();
    translate(m_Position);
}

Object::~Object() {}

int Object::getNumVertices() {
    return numVertices;
}

void Object::loadInVertices(std::vector<glm::vec3>& vertices) {
    for (int i = 0; i < obj.m_Vertices.size(); i++) {
        vertices.push_back(obj.m_Vertices[i]);
    }
}

void Object::loadInTexturecoords(std::vector<glm::vec2> &texturecoords) {
    for (int i = 0; i < obj.m_Vertices.size(); i++) {
        texturecoords.push_back(obj.m_Texcoords[i]);
    }
}

// TODO
void Object::rotate(float angle, const glm::vec3 &axis) {
}

void Object::translate(const glm::vec3 &translation) {
    m_Position.x = translation.x;
    m_Position.y = translation.y;
    m_Position.z = translation.z;
}

// void Object::initializeIBO(int start, int end) {
//     std::vector<unsigned int> ind;
//     for (int i = start; i < end; i++)
//     {
//         ind.push_back(i);
//     }
//     unsigned int *indices = &ind[0];
//     m_IBO = std::make_unique<IndexBuffer>(indices, numVertices);
// }