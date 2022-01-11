#pragma once

class Contact;
class CollisionDetect;
class Solver;
class Object;

// Code taken from SIGGRAPH 2021 Friction contact course (S. Andrews & K. Erleben)
class RigidBodyManager 
{
public:
    RigidBodyManager();
    virtual ~RigidBodyManager();

    // Time step
    void step(float _dt);

    // Remove all bodies and clear memory
    void clear();

    // Add body to the system
    void addBody(Object* _b);
};