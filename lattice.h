//Lattice structure and implementation

#ifndef LATTICE_H
#define LATTICE_H

#include "vector_utils.h"
#include <vector>

class Lattice {
private:
    int L;                            // Lattice size (L x L x L)
    int N;                            // Total number of spins
    std::vector<Vector3D> spins;      // Spins as 3D vectors
    std::vector<std::array<int, 6>> neighbors; // Neighbor indices for each site

    // Function to compute the lattice index from (x, y, z) coordinates
    int index(int x, int y, int z) const {
        return x + L * y + L * L * z;
    }

public:
    Lattice(int size) : L(size), N(size * size * size) {
        spins.resize(N);
        neighbors.resize(N);
        
        // Set up neighbors with periodic boundary conditions
        for (int i = 0; i < N; i++) {
            int z = i / (L * L);
            int y = (i / L) % L;
            int x = i % L;
            neighbors[i][0] = index((x + 1) % L, y, z);        // +x
            neighbors[i][1] = index((x - 1 + L) % L, y, z);    // -x
            neighbors[i][2] = index(x, (y + 1) % L, z);        // +y
            neighbors[i][3] = index(x, (y - 1 + L) % L, z);    // -y
            neighbors[i][4] = index(x, y, (z + 1) % L);        // +z
            neighbors[i][5] = index(x, y, (z - 1 + L) % L);    // -z
        }
    }
    
    // Initialize spins with random orientations
    void initialize_random(RandomGenerators& rng) {
        for (int i = 0; i < N; i++) {
            spins[i] = rng.random_unit_vector();
        }
    }
    
    // Calculate the local field at a given site
    Vector3D calculate_local_field(int site) const {
        Vector3D h = {0, 0, 0};
        for (int dir = 0; dir < 6; dir++) {
            int j = neighbors[site][dir];
            h[0] += spins[j][0];
            h[1] += spins[j][1];
            h[2] += spins[j][2];
        }
        return h;
    }
    
    // Calculate energy change for a spin flip
    double calculate_energy_change(int site, const Vector3D& new_spin) const {
        Vector3D h = calculate_local_field(site);
        return -((new_spin[0] - spins[site][0]) * h[0] +
                (new_spin[1] - spins[site][1]) * h[1] +
                (new_spin[2] - spins[site][2]) * h[2]);
    }
    
    // Update spin at a given site
    void update_spin(int site, const Vector3D& new_spin) {
        spins[site] = new_spin;
    }
    
    // Calculate total energy of the lattice
    double calculate_energy() const {
        double E = 0;
        for (int i = 0; i < N; i++) {
            for (int dir = 0; dir < 3; dir++) { // +x, +y, +z directions
                int j = neighbors[i][2 * dir];
                E += -VectorUtils::dot(spins[i], spins[j]);
            }
        }
        return E;
    }
    
    // Calculate magnetization
    double calculate_magnetization() const {
        Vector3D M = {0, 0, 0};
        for (int i = 0; i < N; i++) {
            M[0] += spins[i][0];
            M[1] += spins[i][1];
            M[2] += spins[i][2];
        }
        return std::sqrt(M[0] * M[0] + M[1] * M[1] + M[2] * M[2]) / N;
    }
    
    int get_size() const { return N; }
};

#endif // LATTICE_H
