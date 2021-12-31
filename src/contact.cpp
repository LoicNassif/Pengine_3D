#include "contact.hpp"

// Default Constructor
Contact::Contact() : pos(), n(), t1(), t2(), pene(0.0f), mu(0.4f), body0(nullptr), body1(nullptr) {}

Contact::Contact(Object* _body0, Object* _body1, const Eigen::Vector3f& _pos, const Eigen::Vector3f& _n, float _pene) 
    : pos(_pos), n(_n), t1(), t2(), mu(0.4f), pene(_pene), body0(_body0), body1(_body1)
{
    J0.setZero(3, 6);
    J1.setZero(3, 6);
}

Contact::~Contact() {}

// TODO
void Contact::computeJacobian()
{

}

// TODO
void Contact::computeContactFrame(const Eigen::Vector3f& dir) 
{

}