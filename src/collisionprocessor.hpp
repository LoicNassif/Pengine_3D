#pragma once

#include "object.hpp"

class CollisionProcessor {
public:
    CollisionProcessor() {};
    ~CollisionProcessor() {};
    
    void detectCollision(Object a, Object b);
};