#include <iostream>
#include <vector>
#include <string>

struct Command {
    std::string name;
    int value;
};

void parseCommand(const char* input, std::vector<Command>& buffer) {
    const char* p = input;

    while (*p == ' ') p++;
    if (*p == '\0') return;

    const char* name_start = p;
    while (*p != ' ' && *p != '\0') p++;
    const char* name_end = p;

    Command cmd;
    cmd.name = std::string(name_start, name_end);
    cmd.value = 0;

    while (*p == ' ') p++;

    if (*p != '\0') {
        int num = 0;
        bool negative = false;

        if (*p == '-') {
            negative = true;
            p++;
        }

        while (*p >= '0' && *p <= '9') {
            num = num * 10 + (*p - '0');
            p++;
        }

        if (negative) {
            num = -num;
        }

        cmd.value = num;
    }

    buffer.push_back(cmd);
}

int main() {
    std::vector<Command> buffer;

    parseCommand("FORWARD 10", buffer);
    parseCommand("TURN 90", buffer);
    parseCommand("STOP", buffer);
    parseCommand("BACKWARD -5", buffer);
    parseCommand("   WAIT    ", buffer);  // с пробелами

    for (const auto& cmd : buffer) {
        std::cout << "Command: " << cmd.name << ", Value: " << cmd.value << std::endl;
    }

    return 0;
}