#pragma once
#include <string>
#include "loadOBJ.hpp"
#include "indexbuffer.hpp"
#include "gtc/matrix_transform.hpp"

enum class BVType {
    BOX,
    SPHERE
};

namespace helpers { 
    // 0: x-axis, 1: y-axis, 2: z-axis
    static float maxAxis(std::vector<Eigen::Vector3f> vertices, int axis)
    {
        float maxVal = -INT_MAX;
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i][axis] > maxVal) {
                maxVal = vertices[i][axis];
            }
        }
        return maxVal;
    }

    // 0: x-axis, 1: y-axis, 2: z-axis
    static float minAxis(std::vector<Eigen::Vector3f> vertices, int axis)
    {
        float minVal = INT_MAX;
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i][axis] < minVal) {
                minVal = vertices[i][axis];
            }
        }
        return minVal;
    }
};

class BVShape {
public:
    virtual ~BVShape() {};

    virtual BVType getBVType() = 0;
};