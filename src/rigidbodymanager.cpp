#include "rigidbodymanager.hpp"
#include "solverboxPGS.hpp"
#include "collisionprocessor.hpp"

namespace 
{
    static Solver* s_solvers[2];
}

RigidBodyManager::RigidBodyManager() :
    m_frame(0), m_contactStiffness(1e6f), m_contactDamping(1e5f), m_mu(0.4f), m_solverIter(20),
    m_solverType(kPGS)
{
    m_collisionDetect = std::make_unique<CollisionProcessor>(this);
    s_solvers[kPGS] = new SolverBoxPGS(this);
}

RigidBodyManager::~RigidBodyManager() 
{
    clear();
}

void RigidBodyManager::step(float _dt) 
{

}

void RigidBodyManager::clear() 
{

}

void RigidBodyManager::addBody(Object* _b) 
{

}