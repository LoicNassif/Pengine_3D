#include "object.hpp"


Object::Object(std::string filename, const Eigen::Vector3f& position, BVType bvtype)
    : obj(loadOBJ(filename)), m_Position(position)
{
    // Create a bounding box for collision detection
    if (bvtype == BVType::BOX) {
        Eigen::Vector3f center_pos;
        center_pos[0] = 0;
        center_pos[1] = 0;
        center_pos[2] = 0;

        bvshape = new Box(obj.m_Vertices, center_pos);
    }

    numVertices = obj.m_Vertices.size();
    translate(m_Position);

}

Object::~Object() {}

int Object::getNumVertices() {
    return numVertices;
}

void Object::loadInVertices(std::vector<Eigen::Vector3f> &vertices)
{
    for (int i = 0; i < obj.m_Vertices.size(); i++) {
        vertices.push_back(obj.m_Vertices[i]);
    }
}

void Object::loadInTexturecoords(std::vector<Eigen::Vector2f> &texturecoords)
{
    for (int i = 0; i < obj.m_Vertices.size(); i++) {
        texturecoords.push_back(obj.m_Texcoords[i]);
    }
}

// TODO
void Object::rotate(float angle, const Eigen::Vector3f &axis) {
}

void Object::translate(const Eigen::Vector3f &translation) {
    m_Position[0] += translation[0];
    m_Position[1] += translation[1];
    m_Position[2] += translation[2];

    if (bvshape->getBVType() == BVType::BOX) {
        Box* BVbox = dynamic_cast<Box*>(bvshape);
        Eigen::Vector3f oldBVMaxPos = BVbox->getBVMaxVertex();
        Eigen::Vector3f oldBVMinPos = BVbox->getBVMinVertex();

        BVbox->setBVMaxVertex(Eigen::Vector3f(
            oldBVMaxPos.x() + translation[0],
            oldBVMaxPos.y() + translation[1],
            oldBVMaxPos.z() + translation[2]
        ));

        BVbox->setBVMinVertex(Eigen::Vector3f(
            oldBVMinPos.x() + translation[0],
            oldBVMinPos.y() + translation[1],
            oldBVMinPos.z() + translation[2]
        ));
    }
}

void Object::translate(const glm::vec3& translation) {
    m_Position[0] += translation[0];
    m_Position[1] += translation[1];
    m_Position[2] += translation[2];

    if (bvshape->getBVType() == BVType::BOX) {
        Box* BVbox = dynamic_cast<Box*>(bvshape);
        Eigen::Vector3f oldBVMaxPos = BVbox->getBVMaxVertex();
        Eigen::Vector3f oldBVMinPos = BVbox->getBVMinVertex();

        BVbox->setBVMaxVertex(Eigen::Vector3f(
            oldBVMaxPos.x() + translation[0],
            oldBVMaxPos.y() + translation[1],
            oldBVMaxPos.z() + translation[2]
        ));

        BVbox->setBVMinVertex(Eigen::Vector3f(
            oldBVMinPos.x() + translation[0],
            oldBVMinPos.y() + translation[1],
            oldBVMinPos.z() + translation[2]
        ));
    }
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