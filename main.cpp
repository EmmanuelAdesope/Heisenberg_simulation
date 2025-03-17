#include "lattice.h"
#include "simulation.h"
#include "measurements.h"
#include <iostream>

// Constants
const int L = 10;                // Lattice size (L x L x L)
const int N = L * L * L;         // Total number of spins
const double T_max = 3.0;        // Maximum temperature
const double T_min = 0.5;        // Minimum temperature
const double dT = 0.1;           // Temperature step
const int num_sweeps_equil = 1000;    // Number of equilibration sweeps
const int num_measurements = 1000;    // Number of measurement points
const int sweeps_between_meas = 10;   // Sweeps between measurements

int main() {
    // Initialize random number generators
    RandomGenerators rng;
    
    // Create and initialize the lattice
    Lattice lattice(L);
    lattice.initialize_random(rng);
    
    // Initialize simulation
    Simulation simulation(lattice, rng);
    
    // Initialize measurements
    Measurements measurements;
    
    // Temperature loop from T_max to T_min
    for (double T = T_max; T >= T_min - dT / 2; T -= dT) { // Adjust for floating-point precision
        // Equilibration phase
        simulation.equilibrate(T, num_sweeps_equil);
        
        // Measurement phase
        measurements.reset();
        
        for (int meas = 0; meas < num_measurements; meas++) {
            // Perform Monte Carlo sweeps between measurements
            simulation.run_sweeps(T, sweeps_between_meas);
            
            // Take measurements
            double energy = lattice.calculate_energy();
            double magnetization = lattice.calculate_magnetization();
            
            // Record measurements
            measurements.record(energy, magnetization);
        }
        
        // Calculate and output results
        double avg_energy = measurements.average_energy() / N;
        double avg_magnetization = measurements.average_magnetization();
        double specific_heat = measurements.specific_heat(T) / N;
        
        // Output results
        std::cout << T << " " << avg_energy << " " << avg_magnetization << " " << specific_heat << std::endl;
    }

    return 0;
}
