#pragma once

#include "object.hpp"

class CollisionProcessor {
public:
    CollisionProcessor() {};
    ~CollisionProcessor() {};

    void processCollision(const std::vector<Object *> &objs, glm::mat4 m_ModelA, glm::mat4 m_ModelB);
    // void inputObject(Object* a);

private:
    bool detectCollision(Object* a, Object* b);
    bool detectCollTriangleTriangle(Object *A, int i, Object *B, int j);

    Eigen::Matrix4f modelA;
    Eigen::Matrix4f modelB;
};