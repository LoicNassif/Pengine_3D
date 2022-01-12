#pragma once

#include "solver.hpp"

// Projected Gauss-Seidel (PGS) Boxed LCP Solver
// Matrix-free implementation
class SolverBoxPGS : public Solver 
{
public:
    SolverBoxPGS(RigidBodyManager* _rigidBodyManager);

    virtual void solve(float h);
};