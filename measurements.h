// Calcualtes and analyzes the average Energy, Magentization and Heat capacity

#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

class Measurements {
private:
    double sum_E;
    double sum_E2;
    double sum_m;
    int count;
    
public:
    Measurements() : sum_E(0), sum_E2(0), sum_m(0), count(0) {}
    
    void reset() {
        sum_E = 0;
        sum_E2 = 0;
        sum_m = 0;
        count = 0;
    }
    
    void record(double energy, double magnetization) {
        sum_E += energy;
        sum_E2 += energy * energy;
        sum_m += magnetization;
        count++;
    }
    
    double average_energy() const {
        return sum_E / count;
    }
    
    double average_magnetization() const {
        return sum_m / count;
    }
    
    double specific_heat(double temperature) const {
        double avg_E = sum_E / count;
        double avg_E2 = sum_E2 / count;
        return (avg_E2 - avg_E * avg_E) / (temperature * temperature);
    }
};

#endif // MEASUREMENTS_H
