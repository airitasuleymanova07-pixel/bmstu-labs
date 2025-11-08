#include <iostream>
#include <vector>

void analyzePressure(const std::vector<double>& data, double& minVal, double& maxVal, double& avgVal) {
    if (data.empty()) {
        std::cout << "Empty data set!" << std::endl;
        minVal = maxVal = avgVal = 0.0;
        return;
    }

    const double* p = data.data();
    size_t size = data.size();

    std::cout << "Analyzing " << size << " pressure readings:" << std::endl;

    minVal = *p;
    maxVal = *p;
    double sum = 0.0;

    for (size_t i = 0; i < size; i++) {
        double current = *(p + i);

        std::cout << "Reading " << i + 1 << ": " << current;

        if (current < minVal) {
            minVal = current;
            std::cout << " (new min)";
        }
        if (current > maxVal) {
            maxVal = current;
            std::cout << " (new max)";
        }

        std::cout << std::endl;
        sum += current;
    }

    avgVal = sum / size;

    std::cout << "Sum: " << sum << std::endl;
}

int main() {
    std::vector<double> pressure = { 101.3, 100.8, 101.9, 100.5, 102.0 };

    double minVal, maxVal, avgVal;
    analyzePressure(pressure, minVal, maxVal, avgVal);

    std::cout << "=== FINAL RESULTS ===" << std::endl;
    std::cout << "Min pressure: " << minVal << std::endl;
    std::cout << "Max pressure: " << maxVal << std::endl;
    std::cout << "Average pressure: " << avgVal << std::endl;

    return 0;
}