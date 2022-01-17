#pragma once

#include <vector>
#include <memory>
#include <functional>

class Contact;
class CollisionProcessor;
class Solver;
class Object;

enum eSolverType { kPGS };

typedef std::function<void(std::vector<Object*>&)> PreStepFunc;
typedef std::function<void()> ResetFunc;

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

    // Compute inertias
    void computeInertias();

    // Compute constraint forces
    void calcConstraintForces(float dt);

private:
    std::vector<Object*> m_bodies;
    std::unique_ptr<CollisionProcessor> m_collisionDetect;
    float m_contactStiffness;
    float m_contactDamping;
    float m_mu;
    int m_solverIter;
    eSolverType m_solverType;
    int m_frame;

    PreStepFunc m_preStepFunc;
    ResetFunc m_resetFunc;
};