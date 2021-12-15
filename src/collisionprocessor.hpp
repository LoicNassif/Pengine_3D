#pragma once

#include "object.hpp"

class CollisionProcessor {
public:
    CollisionProcessor() {};
    ~CollisionProcessor() {};

    void processCollision(const std::vector<Object *> &objs);

private:
    bool collisionOBBOBB(const BVShape* boxA, const BVShape* boxB);
    bool collisionPlanePoint(const Eigen::Vector3f& planePos, const Eigen::Vector3f& pointPos, const Eigen::Vector3f& planeN, float& pene);
    bool collisionPlaneBox(const BVShape* plane, const BVShape* box);
    bool collisionAABBAABB(Box* boxA, Box* boxB);
};