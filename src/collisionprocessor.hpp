#pragma once

#include "object.hpp"

class CollisionProcessor {
public:
    CollisionProcessor() {};
    ~CollisionProcessor() {};

    void processCollision(const std::vector<Object *> &objs);
    // void inputObject(Object* a);

private:
    bool detectCollision(Object* a, Object* b);
};