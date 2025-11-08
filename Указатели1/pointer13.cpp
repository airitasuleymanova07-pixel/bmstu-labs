#include <iostream>

void parseTelemetry(const char* data) {
    const char* p = data;

    while (*p != '\0') {
        // пропускаем пробелы в начале параметра
        while (*p == ' ') p++;
        if (*p == '\0') break;

        // читаем имя параметра
        const char* name_start = p;
        while (*p != ':' && *p != '\0' && *p != ';') p++;
        if (*p != ':') break;

        const char* name_end = p;
        p++; // пропускаем ':'

        // читаем значение
        const char* value_start = p;
        while (*p != ';' && *p != '\0') p++;
        const char* value_end = p;

        std::cout << "Parameter: ";
        for (const char* c = name_start; c < name_end; c++) {
            std::cout << *c;
        }

        std::cout << " | Value: ";
        for (const char* c = value_start; c < value_end; c++) {
            std::cout << *c;
        }
        std::cout << std::endl;

        if (*p == ';') p++;
    }
}

int main() {
    const char* data1 = "TEMP:24.5;PRESS:101.3;HUM:55.2";
    const char* data2 = "SPEED:150.5;RPM:3000;FUEL:45.8";

    std::cout << "Parsing data 1:" << std::endl;
    parseTelemetry(data1);

    std::cout << "Parsing data 2:" << std::endl;
    parseTelemetry(data2);

    return 0;
}