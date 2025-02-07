#include "Error.h"

void Error::error(int line, std::string message) {
    report(line, "", message);
}

void Error::report(int line, std::string location, std::string message) {
    std::cout << "Error: " << location << ":" << message << std::endl;
}

bool Error::hasError = false;

