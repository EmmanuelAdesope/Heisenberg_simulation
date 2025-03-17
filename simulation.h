//Monte Carlo Simulation methods

#ifndef SIMULATION_H
#define SIMULATION_H

#include "lattice.h"
#include <cmath>

class Simulation {
private:
    Lattice& lattice;
    RandomGenerators& rng;
    
public:
    Simulation(Lattice& lat, RandomGenerators& random_gen) : 
        lattice(lat), rng(random_gen) {}
    
    // Perform a single Monte Carlo step
    void monte_carlo_step(double temperature) {
        int site = rng.random_int(lattice.get_size());
        Vector3D new_spin = rng.random_unit_vector();
        
        double delta_E = lattice.calculate_energy_change(site, new_spin);
        
        // Metropolis acceptance criterion
        if (delta_E <= 0 || rng.random_real() < std::exp(-delta_E / temperature)) {
            lattice.update_spin(site, new_spin);
        }
    }
    
    // Run a specified number of Monte Carlo sweeps
    void run_sweeps(double temperature, int num_sweeps) {
        for (int sweep = 0; sweep < num_sweeps; sweep++) {
            for (int i = 0; i < lattice.get_size(); i++) {
                monte_carlo_step(temperature);
            }
        }
    }
    
    // Equilibrate the system
    void equilibrate(double temperature, int num_sweeps) {
        run_sweeps(temperature, num_sweeps);
    }
};

#endif // SIMULATION_H
