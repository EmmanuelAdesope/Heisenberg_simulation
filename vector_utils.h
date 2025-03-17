#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include <array>
#include <random>
#include <cmath>

// Type definition for 3D vector
using Vector3D = std::array<double, 3>;

namespace VectorUtils {
    // Function to compute the dot product of two 3D vectors
    inline double dot(const Vector3D& a, const Vector3D& b) {
        return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    }

    // Function to generate a random unit vector
    inline Vector3D random_unit_vector(std::mt19937& gen, std::normal_distribution<double>& normal) {
        double Sx = normal(gen), Sy = normal(gen), Sz = normal(gen);
        double norm = std::sqrt(Sx * Sx + Sy * Sy + Sz * Sz);
        return {Sx / norm, Sy / norm, Sz / norm};
    }
}

// Class to handle random number generation
class RandomGenerators {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::normal_distribution<double> normal;
    std::uniform_real_distribution<double> uniform_real;

public:
    RandomGenerators() : 
        rd(),
        gen(rd()),
        normal(0.0, 1.0),
        uniform_real(0.0, 1.0) {}
    
    Vector3D random_unit_vector() {
        return VectorUtils::random_unit_vector(gen, normal);
    }
    
    double random_real() {
        return uniform_real(gen);
    }
    
    int random_int(int max) {
        std::uniform_int_distribution<int> uniform_int(0, max - 1);
        return uniform_int(gen);
    }
};

#endif // VECTOR_UTILS_H
