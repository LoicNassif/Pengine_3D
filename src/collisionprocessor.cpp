#include "collisionprocessor.hpp"

// TODO: Sphere-sphere intersection test

// TODO: Plane-point intersection test
bool CollisionProcessor::collisionPlanePoint(const Eigen::Vector3f& planePos, const Eigen::Vector3f& pointPos, const Eigen::Vector3f& planeN, float& pene) 
{
    float dp = (pointPos - planePos).dot(planeN);
    if (dp < 1e-5f) {
        pene = std::max(0.0f, -dp);
        return true;
    }
    return false;
}

// TODO: Box-Plane intersection test (using Plane-point test)
bool CollisionProcessor::collisionPlaneBox(const BVShape* plane, const BVShape* box)
{
    return false;
}

// Text (Axis Aligned Bounding) Box-Box collision
bool CollisionProcessor::collisionAABBAABB(Box* boxA, Box* boxB)
{
    Eigen::Vector3f maxA = boxA->getBVMaxVertex();
    Eigen::Vector3f minA = boxA->getBVMinVertex();
    Eigen::Vector3f maxB = boxB->getBVMaxVertex();
    Eigen::Vector3f minB = boxB->getBVMinVertex();

    if (maxA.x() < minB.x() || minA.x() > maxB.x()) return false;
    if (maxA.y() < minB.y() || minA.y() > maxB.y()) return false;
    if (maxA.z() < minB.z() || minA.z() > maxB.z()) return false;

    return true;
}

// DOESN'T WORK ATM
// Test (Oriented Bounding) Box-Box collision
bool CollisionProcessor::collisionOBBOBB(const BVShape* boxA, const BVShape* boxB)
{
    //glm::vec3 centerDistance = boxA->m_Position - boxB->m_Position;

    //// Pick any vertex to get box extents
    //for (int i = 0; i < 3; i++) {
    //    float maxA = Object::maxAxis(boxA->obj.m_Vertices, i);
    //    float maxB = Object::maxAxis(boxB->obj.m_Vertices, i);
    //    float hA = std::abs(maxA - boxA->m_Position[i]);
    //    float hB = std::abs(maxB - boxB->m_Position[i]);
    //
    //    if ((std::abs(centerDistance[i]) - (hA + hB)) > 0) {
    //        return false;
    //    }
    //}
    return true;
}

void CollisionProcessor::respondCollision()
{

}

// Naive implementation
void CollisionProcessor::processCollision(const std::vector<Object*>& objs)
{
    for (int i = 0; i < objs.size(); i++) {
        for (int j = 0; j < objs.size(); j++) {
            if (i != j)
                if (objs[i]->bvshape->getBVType() == BVType::BOX && objs[j]->bvshape->getBVType() == BVType::BOX)
                if (collisionAABBAABB(dynamic_cast<Box*>(objs[i]->bvshape), dynamic_cast<Box*>(objs[j]->bvshape)))
                {
                    // TODO: Need to return normal + pene depth of contact
                    // TODO: Call solver here

                    // This is just a temp implementation for visualization fun (and debugging)
                    if (!objs[i]->fixed) objs[i]->translate(Eigen::Vector3f(0.0f, 1.0f / 500.0f, 0.0f));
                    if (!objs[j]->fixed) objs[j]->translate(Eigen::Vector3f(0.0f, 1.0f / 500.0f, 0.0f));
                }
        }
    }
}

// TODO
void CollisionProcessor::computeContactJacobians() 
{

}