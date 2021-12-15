#pragma once

#include "bvshape.hpp"

class Box : public BVShape {
public:
    Box(std::vector<Eigen::Vector3f> vertices, Eigen::Vector3f center_pos);
    ~Box();

    Eigen::Vector3f getBVMaxVertex();
    Eigen::Vector3f getBVMinVertex();

    void setBVMaxVertex(Eigen::Vector3f update);
    void setBVMinVertex(Eigen::Vector3f update);

    BVType getBVType();

private:
    Eigen::Vector3f BVMaxVertex;
    Eigen::Vector3f BVMinVertex;
    BVType bvtype = BVType::BOX;
};