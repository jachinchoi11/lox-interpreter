
#include "Run.h"
#include <iostream>
#include "Error.h"
#include "Scanner.h"


void Run::runPrompt() {
    std::cout << "Enter line by line" << std::endl;
    std::string line;
    std::getline(std::cin, line);
    if (!line.empty()) {
        run(line);
        Error::hasError = false;
    }
}
void Run::run(std::string& line) {
    Scanner scanner(line);
}
