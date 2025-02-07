

#include <iostream>
#include "Run.h"
#include "Scanner.h"
#include "Error.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        std::cout << "Incorrect number of arguments" << std::endl;
        exit(64);
    }
    else {
        Run::runPrompt();
        Error::hasError = false;
    }
    Scanner scanner("ddwaui");
    scanner.scanTokens();
    return 0;
}