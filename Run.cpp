
#include "Run.h"
#include <iostream>
#include "Error.h"
#include "Scanner.h"
#include "FileRead.h"

void Run::runPrompt() {
    std::cout << "Enter line by line" << std::endl;
    std::string line;
    std::getline(std::cin, line);
    if (!line.empty()) {
        run(line);
        Error::hasError = false;
    }
}

void Run::run(std::string &line) {
    Scanner scanner(line);
    std::vector<Token> tokens = scanner.scanTokens();
    for (Token token: tokens) {
        std::cout << "hello" << std::endl;
    }
}
void Run::run_file(std::string source) {
    FileRead a(source);
    a.read_file(source);
    std::string output = a.scan_file();
    run(output);
}
