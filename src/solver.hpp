#pragma once

class RigidBodyManager;

class Solver 
{
public:
    Solver(RigidBodyManager* _rigidBodyManager) : m_rigidBodyManager(_rigidBodyManager), m_maxIter(20) {}

    // Set max iters
    // PGS: Changes number of iterations
    void setMaxIter(int _maxIter) { m_maxIter = _maxIter; }

    // Return max iters
    int getMaxIter() const { return m_maxIter; }

    virtual void solve(float h) = 0;

protected:
    RigidBodyManager* m_rigidBodyManager;
    int m_maxIter;
};