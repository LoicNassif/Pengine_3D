#pragma once

#include <Eigen/Dense>

class Object;

class Contact {
public:
    Contact();
    Contact::Contact(Object* _body0, Object* _body1, const Eigen::Vector3f& _pos, const Eigen::Vector3f& _n, float _pene);

    virtual ~Contact();

    virtual void computeJacobian();

    void computeContactFrame(const Eigen::Vector3f& dir);

    Eigen::Vector3f pos;    // Contact position
    Eigen::Vector3f n;      // Contact normal
    Eigen::Vector3f t1, t2; // Tangent directions
    float mu;               // Coeff of friction
    float pene;             // Penetration

    Object* body0;
    Object* body1;

    Eigen::MatrixXf J0;     // Jacobian of first body
    Eigen::MatrixXf J1;     // Jacobian of second body
    Eigen::MatrixXf phi;    // Constraint error
    Eigen::MatrixXf lambda; // Constraint impulse
};