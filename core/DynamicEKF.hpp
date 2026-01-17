#ifndef DYNAMIC_EKF_HPP
#define DYNAMIC_EKF_HPP

#include <Eigen/Dense>
#include "../materials/MaterialState.hpp"

/**
 * @brief Dynamic Extended Kalman Filter that incorporates material physics.
 * This is a core component of the VYNO Autonomous Stack.
 */
class DynamicEKF {
public:
    DynamicEKF() {
        // State vector: [position, velocity, acceleration]
        x = Eigen::VectorXd::Zero(3);
        P = Eigen::MatrixXd::Identity(3, 3);
    }

    /**
     * @brief Measurement update step with material-informed noise scaling.
     * @param z Current sensor measurement.
     * @param state The physical state of the sensor material.
     */
    void update(const Eigen::VectorXd& z, const MaterialState& state) {
        // Standard noise covariance (R)
        double base_noise = 0.1;
        
        // DYNAMIC INNOVATION: Scale R based on material physics (Temp, Wear)
        double dynamic_R_val = base_noise * state.calculateNoiseMultiplier();
        Eigen::MatrixXd R = Eigen::MatrixXd::Identity(1, 1) * dynamic_R_val;

        // Kalman Gain calculation with dynamic R
        // K = P * H' * (H * P * H' + R)^-1
        // (Standard EKF math goes here, but with our dynamic R)
    }

private:
    Eigen::VectorXd x; // State estimate
    Eigen::MatrixXd P; // Estimate covariance
};

#endif