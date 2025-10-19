#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iomanip>

using namespace std;

int main() {
    vector<double> fuel_level(50);
    setlocale(LC_ALL, "rus");

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 100.0);

    for (int i = 0; i < 50; i++) {
        fuel_level[i] = dis(gen);
    }
    cout << "Всего замеров: " << fuel_level.size() << " (каждые 10 минут)" << endl;
    cout << "Период наблюдения: " << 50 * 10 << " минут (" << 50 * 10 / 60.0 << " часов)" << endl;
    cout << "Первые 10 значений: ";
    for (int i = 0; i < 10; i++) {
        cout << fixed << setprecision(1) << fuel_level[i] << "% ";
    }
    cout << "..." << endl << endl;

    // 1. Минимальный уровень топлива
    double min_fuel = *min_element(fuel_level.begin(), fuel_level.end());
    cout << "1. МИНИМАЛЬНЫЙ УРОВЕНЬ ТОПЛИВА: " << fixed << setprecision(1) << min_fuel << "%" << endl;

    // 2. Проверка, не падал ли уровень ниже 5% от максимального
    double max_fuel = *max_element(fuel_level.begin(), fuel_level.end());
    double critical_level = max_fuel * 0.05; // 5% от максимального

    bool fell_below_critical = any_of(fuel_level.begin(), fuel_level.end(),
        [critical_level](double level) {
            return level < critical_level;
        });

    cout << "2. ПРОВЕРКА КРИТИЧЕСКОГО УРОВНЯ:" << endl;
    cout << "   Максимальный уровень: " << max_fuel << "%" << endl;
    cout << "   Критический уровень (5% от макс.): " << critical_level << "%" << endl;

    if (fell_below_critical) {
        cout << " Уровень падал ниже критической отметки!" << endl;

        // Находим все значения ниже критического уровня
        vector<double> critical_values;
        copy_if(fuel_level.begin(), fuel_level.end(), back_inserter(critical_values),
            [critical_level](double level) { return level < critical_level; });

        cout << "   Критические значения: ";
        for (double val : critical_values) {
            cout << val << "% ";
        }
        cout << endl;
    }
    else {
        cout << "Уровень никогда не падал ниже критической отметки" << endl;
    }

    // 3. Среднее потребление (разность начального и конечного значений)
    double initial_fuel = fuel_level.front();
    double final_fuel = fuel_level.back();
    double total_consumption = initial_fuel - final_fuel;

    cout << "3. ПОТРЕБЛЕНИЕ ТОПЛИВА:" << endl;
    cout << "   Начальный уровень: " << initial_fuel << "%" << endl;
    cout << "   Конечный уровень: " << final_fuel << "%" << endl;
    cout << "   Общее потребление: " << total_consumption << "%" << endl;

    // Расчет среднего потребления за 10 минут и за час
    double consumption_per_10min = total_consumption / (fuel_level.size() - 1);
    double consumption_per_hour = consumption_per_10min * 6; // 6 × 10 минут = 1 час

    cout << "   Среднее потребление за 10 мин: " << fixed << setprecision(2) << consumption_per_10min << "%" << endl;
    cout << "   Среднее потребление за час: " << fixed << setprecision(2) << consumption_per_hour << "%" << endl;

    // 4. Медиана
    vector<double> sorted_fuel = fuel_level;
    sort(sorted_fuel.begin(), sorted_fuel.end());

    double median;
    if (sorted_fuel.size() % 2 == 0) {
        median = (sorted_fuel[sorted_fuel.size() / 2 - 1] + sorted_fuel[sorted_fuel.size() / 2]) / 2.0;
    }
    else {
        median = sorted_fuel[sorted_fuel.size() / 2];
    }

    cout << "4. МЕДИАНА УРОВНЯ ТОПЛИВА:" << endl;
    cout << "   Медиана: " << fixed << setprecision(1) << median << "%" << endl;

    // Дополнительная статистика
    cout << "5. ДОПОЛНИТЕЛЬНАЯ СТАТИСТИКА:" << endl;
    double average_fuel = accumulate(fuel_level.begin(), fuel_level.end(), 0.0) / fuel_level.size();
    cout << "   Средний уровень: " << fixed << setprecision(1) << average_fuel << "%" << endl;
    cout << "   Диапазон: от " << min_fuel << "% до " << max_fuel << "%" << endl;

    return 0;
}