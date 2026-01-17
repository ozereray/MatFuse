#ifndef DYNAMIC_EKF_HPP
#define DYNAMIC_EKF_HPP

#include <Eigen/Dense>
#include "../materials/MaterialState.hpp"

/**
 * @brief Physics-Aware Extended Kalman Filter
 * This module integrates physical sensor degradation into the perception stack.
 * Part of the VYNO Autonomous Ecosystem.
 */
class DynamicEKF {
public:
    DynamicEKF() {
        // State: [position, velocity]
        x = Eigen::Vector2d::Zero();
        P = Eigen::Matrix2d::Identity() * 1.0; // Initial uncertainty
    }

    /**
     * @brief Measurement update step with Dynamic Covariance Scaling.
     * @param z Measurement from sensor (e.g., position)
     * @param state Real-time physical state of the material
     */
    void update(double z, const MaterialState& state) {
        // 1. Base measurement noise (Ideal conditions)
        double R_base = 0.05;

        // 2. DYNAMIC INNOVATION: Scale R based on material physics (Temp/Wear)
        // This is the core 'MatFuse' logic that differentiates your work.
        double R_dynamic = R_base * state.calculateNoiseMultiplier();
        
        // Kalman Gain Calculation: K = P / (P + R)
        double K = P(0,0) / (P(0,0) + R_dynamic);

        // State Update: x = x + K * (z - x)
        x(0) = x(0) + K * (z - x(0));

        // Covariance Update: P = (1 - K) * P
        P(0,0) = (1 - K) * P(0,0);
    }

    double getPosition() const { return x(0); }
    double getUncertainty() const { return P(0,0); }

private:
    Eigen::Vector2d x; // State estimate
    Eigen::Matrix2d P; // Estimation covariance
};

#endif