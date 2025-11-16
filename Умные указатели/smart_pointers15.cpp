#include <iostream>
#include <memory>
#include <vector>
#include <locale>
#include <algorithm>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    vector<string> routes = {
        "Moscow-Berlin",
        "Berlin-Paris",
        "Paris-Rome",
        "Rome-Moscow"
    };

    // Создание shared_ptr
    auto ptrRoutes = make_shared<vector<string>>(routes);

    // Лямбда-функции
    auto countCity = [](shared_ptr<vector<string>> routes,
        const string& city) -> int {
            int count = 0;
            for (const auto& route : *routes) {
                if (route.find(city) != string::npos) {
                    count++;
                }
            }
            return count;
        };

    auto sortByLength = [](shared_ptr<vector<string>> routes) {
        sort(routes->begin(), routes->end(),
            [](const string& a, const string& b) {
                return a.length() > b.length();
            });
        };

    auto concat = [](shared_ptr<vector<string>> routes) -> string {
        string result;
        for (size_t i = 0; i < routes->size(); i++) {
            result += (*routes)[i];
            if (i < routes->size() - 1) {
                result += " -> ";
            }
        }
        return result;
        };

    // Выполнение операций
    int parisCount = countCity(ptrRoutes, "Paris");
    cout << "Количество маршрутов с \"Paris\": " << parisCount << endl;

    sortByLength(ptrRoutes);
    cout << "Отсортированные маршруты:" << endl;
    for (const auto& route : *ptrRoutes) {
        cout << route << endl;
    }

    string combined = concat(ptrRoutes);
    cout << "\nОбщий маршрут:\n" << combined << endl;

    return 0;
}