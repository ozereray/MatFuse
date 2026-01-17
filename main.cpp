#include <iostream>
#include <iomanip>
#include "core/materials/MaterialState.hpp"
#include "core/filters/DynamicEKF.hpp"

int main() {
    std::cout << "--- MatFuse: Materials-Informed Perception Simulation ---" << std::endl;
    
    MaterialState lidar_sensor(25.0); // Start at room temperature
    DynamicEKF fusion_engine;

    // Simulation: Driving through a high-stress environment (e.g., Mars surface)
    for (int t = 0; t < 10; ++t) {
        double current_temp = 25.0 + (t * 15.0); // Rapid heating
        double current_wear = t * 0.05;        // Incremental wear
        lidar_sensor.updatePhysicalState(current_temp, current_wear);

        // Simulated raw sensor data (constant position 10.0 for simplicity)
        double raw_measurement = 10.0;
        fusion_engine.update(raw_measurement, lidar_sensor);

        std::cout << "Time: " << t << "s | "
                  << "Temp: " << std::setw(5) << current_temp << "C | "
                  << "Uncertainty (P): " << std::fixed << std::setprecision(4) 
                  << fusion_engine.getUncertainty() << std::endl;
    }

    std::cout << "--- Simulation Finished: Integrated with VYNO Ecosystem ---" << std::endl;
    return 0;
}