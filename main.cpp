#include <iostream>
#include "core/materials/MaterialState.hpp"
#include "core/filters/DynamicEKF.hpp"

/**
 * @brief MatFuse Simulation Entry Point
 * Part of the VYNO Autonomous Ecosystem.
 */
int main() {
    std::cout << "--- MatFuse: Starting Autonomous Perception Simulation ---" << std::endl;

    MaterialState lidar_sensor(25.0); // Starting at 25 Celsius
    
    for (int t = 0; t < 5; ++t) {
        double temp = 25.0 + (t * 10.0);
        lidar_sensor.updatePhysicalState(temp, t * 0.01);
        std::cout << "[Time " << t << "s] Sensor Temp: " << temp 
                  << "C | Noise Multiplier: " << lidar_sensor.calculateNoiseMultiplier() << "x" << std::endl;
    }

    std::cout << "--- Simulation Successful ---" << std::endl;
    return 0;
}