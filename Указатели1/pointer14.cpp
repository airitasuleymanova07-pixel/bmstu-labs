#include <iostream>
#include <vector>
#include <cmath>

double computeRMS(const std::vector<double>& signal) {
    if (signal.empty()) {
        return 0.0;
    }

    const double* p = signal.data();
    size_t N = signal.size();
    double sum_of_squares = 0.0;

    for (size_t i = 0; i < N; i++) {
        double value = *(p + i);
        sum_of_squares += value * value;
    }

    return std::sqrt(sum_of_squares / N);
}

int main() {
    std::vector<double> signal = { 2.0, 3.0, 1.0, 4.0, 3.0 };
    double rms = computeRMS(signal);

    std::cout << "RMS value: " << rms << std::endl;

    std::vector<double> signal2 = { 1.0, 1.0, 1.0, 1.0, 1.0 };
    std::vector<double> signal3 = { 0.0, 0.0, 0.0 };
    std::vector<double> signal4 = { -2.0, -3.0, -1.0, -4.0, -3.0 };

    std::cout << "RMS of {1,1,1,1,1}: " << computeRMS(signal2) << std::endl;
    std::cout << "RMS of {0,0,0}: " << computeRMS(signal3) << std::endl;
    std::cout << "RMS of {-2,-3,-1,-4,-3}: " << computeRMS(signal4) << std::endl;

    return 0;
}