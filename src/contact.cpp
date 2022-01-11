#include "contact.hpp"
#include "object.hpp"

// Default Constructor
Contact::Contact() : pos(), n(), t1(), t2(), pene(0.0f), mu(0.4f), body0(nullptr), body1(nullptr) {}

Contact::Contact(Object* _body0, Object* _body1, const Eigen::Vector3f& _pos, const Eigen::Vector3f& _n, float _pene) 
    : pos(_pos), n(_n), t1(), t2(), mu(0.4f), pene(_pene), body0(_body0), body1(_body1)
{
    J0.setZero(3, 6);
    J1.setZero(3, 6);
}

Contact::~Contact() {}


// Code taken from SIGGRAPH 2021 Friction contact course (S. Andrews & K. Erleben)
void Contact::computeJacobian()
{
    const Eigen::Vector3f r0 = pos - body0->m_Position;
    const Eigen::Vector3f r1 = pos - body1->m_Position;


    J0.setZero(3, 6);
    J1.setZero(3, 6);
    J0Minv.setZero(3, 6);
    J1Minv.setZero(3, 6);
    lambda.setZero(3);
    phi.setZero(3);
    phi(0) = pene;

    // Normal row (non-interpenetration)
    J0.block(0, 0, 1, 3) = n.transpose();
    J0.block(0, 3, 1, 3) = r0.cross(n).transpose();
    J1.block(0, 0, 1, 3) = -n.transpose();
    J1.block(0, 3, 1, 3) = -r1.cross(n).transpose();

    // tangent 1 (friction)
    J0.block(1, 0, 1, 3) = t1.transpose();
    J0.block(1, 3, 1, 3) = r0.cross(t1).transpose();
    J1.block(1, 0, 1, 3) = -t1.transpose();
    J1.block(1, 3, 1, 3) = -r1.cross(t1).transpose();

    // tangent 2 (friction)
    J0.block(2, 0, 1, 3) = t2.transpose();
    J0.block(2, 3, 1, 3) = r0.cross(t2).transpose();
    J1.block(2, 0, 1, 3) = -t2.transpose();
    J1.block(2, 3, 1, 3) = -r1.cross(t2).transpose();

    J0Minv.block(0, 0, 3, 3) = (1.0f / body0->mass) * J0.block(0, 0, 3, 3);
    J0Minv.block(0, 3, 3, 3) = J0.block(0, 3, 3, 3) * body0->Iinv;
    J1Minv.block(0, 0, 3, 3) = (1.0f / body1->mass) * J1.block(0, 0, 3, 3);
    J1Minv.block(0, 3, 3, 3) = J1.block(0, 3, 3, 3) * body1->Iinv;
}

// Code taken from SIGGRAPH 2021 Friction contact course (S. Andrews & K. Erleben)
// Generates contact frame with orthonormal basis vectors
void Contact::computeContactFrame(const Eigen::Vector3f& dir) 
{
    t1 = dir - (dir.dot(n)) * n;
    if (t1.norm() < 1e-5f) {
        // Use axis aligned direction (0,0,-1)
        t1 = -n.cross(Eigen::Vector3f(0, 0, -1));
    }
    t1.normalize();

    // Second tangent direction follows from first one
    t2 = n.cross(t1);
    t2.normalize();
}