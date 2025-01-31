
#include "Run.h"
#include <iostream>

void Run::runFile(std::string file_name) {
    std::cout << "Need to figure this out" << std::endl;
}

void Run::runPrompt() {
    std::cout << "Enter line by line" << std::endl;
    std::string line;
    std::getline(std::cin, line);
    if (!line.empty()) {
        run(line);
    }
}
void Run::run(std::string line) {
// we have to create a token class?
    // maybe we can wrap the line in a string stream and then put it in tokens, but we need to first create a token clas
}
