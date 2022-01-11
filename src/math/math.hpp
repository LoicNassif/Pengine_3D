#pragma once
#include <Eigen/Dense>
#include <iostream>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace math {
    inline void translate(Eigen::MatrixXf& initial, const Eigen::Vector3f& position) {
        initial(3, 0) = position[0];
        initial(3, 1) = position[1];
        initial(3, 2) = position[2];
    }

    inline void eigen_to_glm(glm::mat4& glm_matrix, const Eigen::MatrixXf eigen_matrix) {
        for (int i = 0; i < eigen_matrix.rows(); i++) {
            for (int j = 0; j < eigen_matrix.cols(); j++) {
                glm_matrix[i][j] = eigen_matrix(i, j);
            }
        }
    }

    inline void glm_to_eigen(Eigen::MatrixXf eigen_matrix, const glm::mat4& glm_matrix) {
        for (int i = 0; i < eigen_matrix.rows(); i++) {
            for (int j = 0; j < eigen_matrix.cols(); j++) {
                eigen_matrix(i,j) = glm_matrix[i][j];
                std::cout << glm_matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};