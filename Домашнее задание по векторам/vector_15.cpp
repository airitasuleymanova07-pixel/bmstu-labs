#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iomanip>

using namespace std;

int main() {
    vector<vector<double>> temp(5, vector<double>(30));
    vector<vector<double>> pressure(5, vector<double>(100));

    setlocale(LC_ALL, "rus");

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> temp_dis(15.0, 35.0);
    uniform_real_distribution<> pressure_dis(0.5, 5.0);

    for (auto& channel : temp) {
        for (auto& value : channel) {
            value = temp_dis(gen);
        }
    }

    for (auto& channel : pressure) {
        for (auto& value : channel) {
            value = pressure_dis(gen);
        }
    }

    vector<double> avg_temps(5);
    transform(temp.begin(), temp.end(), avg_temps.begin(),
        [](const vector<double>& channel) {
            return accumulate(channel.begin(), channel.end(), 0.0) / channel.size();
        });

    cout << "средние температуры по каналам:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "канал " << i << ": " << fixed << setprecision(2) << avg_temps[i] << "°C" << endl;
    }

    vector<pair<double, double>> pressure_minmax(5);
    transform(pressure.begin(), pressure.end(), pressure_minmax.begin(),
        [](const vector<double>& channel) {
            auto minmax = minmax_element(channel.begin(), channel.end());
            return make_pair(*minmax.first, *minmax.second);
        });

    cout << "минимальное и максимальное давление:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "канал " << i << ": min=" << fixed << setprecision(2) << pressure_minmax[i].first
            << " bar, max=" << pressure_minmax[i].second << " bar" << endl;
    }

    vector<vector<double>> temp_differences(5);
    vector<vector<double>> pressure_differences(5);

    for (int i = 0; i < 5; i++) {
        temp_differences[i].resize(temp[i].size() - 1);
        transform(temp[i].begin(), temp[i].end() - 1, temp[i].begin() + 1,
            temp_differences[i].begin(),
            [](double a, double b) { return b - a; });

        pressure_differences[i].resize(pressure[i].size() - 1);
        transform(pressure[i].begin(), pressure[i].end() - 1, pressure[i].begin() + 1,
            pressure_differences[i].begin(),
            [](double a, double b) { return b - a; });
    }

    cout << "ервые разности температур(канал 0) :" << endl;
    for (int i = 0; i < 5; i++) {
        cout << fixed << setprecision(2) << temp_differences[0][i] << " ";
    }
    cout << "..." << endl;

    vector<double> temp_variations(5);
    transform(temp.begin(), temp.end(), temp_variations.begin(),
        [](const vector<double>& channel) {
            auto minmax = minmax_element(channel.begin(), channel.end());
            return *minmax.second - *minmax.first;
        });

    auto max_var_it = max_element(temp_variations.begin(), temp_variations.end());
    int max_var_channel = distance(temp_variations.begin(), max_var_it);
    cout << "канал с наибольшей вариацией температуры: " << max_var_channel
        << " (вариация: " << fixed << setprecision(2) << *max_var_it << "°C)" << endl;

    vector<vector<double>> normalized_pressure(5);
    for (int i = 0; i < 5; i++) {
        normalized_pressure[i].resize(pressure[i].size());
        double min_val = pressure_minmax[i].first;
        double max_val = pressure_minmax[i].second;
        double range = max_val - min_val;

        transform(pressure[i].begin(), pressure[i].end(), normalized_pressure[i].begin(),
            [min_val, range](double value) {
                return (value - min_val) / range;
            });
    }

    cout << "пики давления (нормализованные > 0.9):" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "канал " << i << ": ";
        for_each(normalized_pressure[i].begin(), normalized_pressure[i].end(),
            [](double value) {
                if (value > 0.9) {
                    cout << fixed << setprecision(3) << value << " ";
                }
            });
        cout << endl;
    }

    vector<size_t> indices(5);
    iota(indices.begin(), indices.end(), 0);
    sort(indices.begin(), indices.end(),
        [&avg_temps](size_t i, size_t j) { return avg_temps[i] > avg_temps[j]; });

    cout << "\nканал с максимальной средней температурой: " << indices[0]
        << " (" << fixed << setprecision(2) << avg_temps[indices[0]] << "°C)" << endl;

    cout << "средние температуры по убыванию:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "канал " << indices[i] << ": " << avg_temps[indices[i]] << "°C" << endl;
    }

    return 0;
}