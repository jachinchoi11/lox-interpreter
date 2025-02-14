

#include <iostream>
#include "Run.h"
#include "Scanner.h"
#include "Error.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        std::cout << "Incorrect number of arguments" << std::endl;
        exit(64);
    }
    else if (argc == 1) {
        Run::run_file(argv[0]);
    }
    else {
        Run::runPrompt();
        Error::hasError = false;
    }
    return 0;

}