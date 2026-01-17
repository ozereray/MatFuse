#ifndef MATERIAL_STATE_HPP
#define MATERIAL_STATE_HPP

/**
 * @brief Represents the physical state of a sensor material.
 * This module is part of the MatFuse core, integrating materials engineering 
 * data into autonomous perception logic.
 */
class MaterialState {
public:
    struct PhysicalParameters {
        double temperature_celsius;    // Operational temperature
        double wear_index;             // Surface degradation (0.0 to 1.0)
        double structural_integrity;    // Vibration-induced fatigue
    };

    MaterialState(double init_temp) {
        params.temperature_celsius = init_temp;
        params.wear_index = 0.0; // Brand new sensor
    }

    /**
     * @brief Calculates the dynamic noise multiplier based on physical stress.
     * Higher temperature or wear leads to increased measurement uncertainty.
     */
    double calculateNoiseMultiplier() const {
        // Engineering model: Exponential growth of noise with temperature and wear
        // This simulates the real-world degradation of sensor fidelity.
        return 1.0 + (0.05 * params.temperature_celsius) + (2.0 * params.wear_index);
    }

    void updatePhysicalState(double new_temp, double new_wear) {
        params.temperature_celsius = new_temp;
        params.wear_index = new_wear;
    }

private:
    PhysicalParameters params;
};

#endif