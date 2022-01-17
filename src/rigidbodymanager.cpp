#include "rigidbodymanager.hpp"
#include "solverboxPGS.hpp"
#include "collisionprocessor.hpp"
#include "contact.hpp"

namespace 
{
    static Solver* s_solvers[2];
}

// Code taken from SIGGRAPH 2021 Friction contact course (S. Andrews & K. Erleben)
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

void RigidBodyManager::step(float dt) 
{
    // Init and clear contacts
    for (auto b : m_bodies) 
    {
        // Apply gravitational force
        b->f = b->mass * Eigen::Vector3f(0.0f, -9.81f, 0.0f);
        b->tau.setZero();
        b->fc.setZero();
        b->tauc.setZero();
        b->contacts.clear();
    }

    computeInertias();

    if (m_preStepFunc)
        m_preStepFunc(m_bodies);

    m_collisionDetect->processCollision(m_bodies);

    // TODO: Compute Contact Jacobians
    m_collisionDetect->computeContactJacobians();

    // Update contact stiffness and damping
    auto contacts = m_collisionDetect->getContacts();
    for (auto c : contacts) {
        c->k = m_contactStiffness;
        c->b = m_contactDamping;
        c->mu = m_mu;
    }

    for (auto b : m_bodies) 
    {
        b->fc.setZero();
        b->tauc.setZero();
    }

    calcConstraintForces(dt);

    // Perform numerical integration of each rigid body
    for (Object* b : m_bodies) 
    {
        if (!b->fixed) {
            b->xdot += dt * (1.0f / b->mass) * (b->f + b->fc);
            b->omega += dt * b->Iinv * (b->tau + b->tauc);
            b->m_Position += dt * b->xdot;
        }
        else 
        {
            b->xdot.setZero();
            b->omega.setZero();
        }
    }
    m_frame++;
}

void RigidBodyManager::clear() 
{
    if (m_resetFunc) {
        m_resetFunc();
    }
    //m_collisionDetect->clear();

    for (auto b : m_bodies) {
        delete b;
    }
    m_bodies.clear();
    m_frame = 0;
}

void RigidBodyManager::addBody(Object* _b) 
{
    // Init aux rotation matrix
    _b->R = _b->q.toRotationMatrix();

    m_bodies.push_back(_b);
}

void RigidBodyManager::computeInertias() 
{
    for (Object* b : m_bodies) 
    {
        b->R = b->q.toRotationMatrix();
        b->updateInertiaMatrix();
    }
}

void RigidBodyManager::calcConstraintForces(float dt) 
{
    // Solve for the constraint forces
    s_solvers[m_solverType]->setMaxIter(m_solverIter);
    s_solvers[m_solverType]->solve(dt);

    // Apply the constraint forces as forces and torques acting on each body
    auto contacts = m_collisionDetect->getContacts();
    for (const auto c : contacts) 
    {
        // Convert impulses in c->lambda to forces
        const Eigen::VectorXf f0 = c->J0.transpose() * c->lambda / dt;
        const Eigen::VectorXf f1 = c->J1.transpose() * c->lambda / dt;

        if (!c->body0->fixed) 
        {
            c->body0->fc += f0.head<3>();
            c->body0->tauc += f0.tail<3>();
        }
        if (!c->body1->fixed) 
        {
            c->body1->fc += f1.head<3>();
            c->body1->tauc += f1.tail<3>();
        }
    }
}