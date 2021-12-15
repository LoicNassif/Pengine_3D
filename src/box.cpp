#include "box.hpp"

// TODO: Need to be a bit more careful with these values, world space?
Box::Box(std::vector<Eigen::Vector3f> vertices, Eigen::Vector3f center_pos) {
    BVMaxVertex = Eigen::Vector3f(helpers::maxAxis(vertices, 0), helpers::maxAxis(vertices, 1), helpers::maxAxis(vertices, 2));
    BVMinVertex = Eigen::Vector3f(helpers::minAxis(vertices, 0), helpers::minAxis(vertices, 1), helpers::minAxis(vertices, 2));

    BVMaxVertex += center_pos;
    BVMinVertex += center_pos;
}

Box::~Box() {}

Eigen::Vector3f Box::getBVMaxVertex() 
{
    return BVMaxVertex;
}

Eigen::Vector3f Box::getBVMinVertex()
{
    return BVMinVertex;
}

void Box::setBVMaxVertex(Eigen::Vector3f update) 
{
    BVMaxVertex = update;
}

void Box::setBVMinVertex(Eigen::Vector3f update)
{
    BVMinVertex = update;
}

BVType Box::getBVType() 
{
    return bvtype;
}