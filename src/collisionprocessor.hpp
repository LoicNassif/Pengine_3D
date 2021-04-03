#pragma once

#include "object.hpp"

class CollisionProcessor {
public:
    CollisionProcessor() {};
    ~CollisionProcessor() {};

    void processCollision(Object* a, Object* b);

private:
    void detectCollision(Object* a, Object* b);
};